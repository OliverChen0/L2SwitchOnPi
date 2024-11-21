#!/usr/bin/env ruby

require 'slop'
require 'pathname'
require 'tempfile'

#################################################################
# Shell helper
#################################################################

def sys(cmd)
    return %x(#{cmd})
end

def syscmd(cmd)
    puts "Running #{cmd}" if $options[:debug]
    response = %x(#{cmd})
    if $? != 0
        raise "Running '#{cmd}' failed"
    end
    return response
end

module Slop
    class PathOption < Option
        def call(value)
            Pathname.new(value).to_s
        end
    end
end

def arguments
    opts = Slop::Options.new
    opts.banner =  "Usage: fit_file_builder.rb parse [options]"
    opts.separator ""
    opts.separator "Most used options:"
    opts.string    "-a", "--arch", "Target build architecture", default: "arm64"
    opts.array     "-b", "--board", "Target board(s) (list of DTBs)", required: true, delimiter: ':'
    opts.string    "-k", "--kernel-file", "Path to kernel image", required: true
    opts.string    "-m", "--machine", "Target machine", required: true
    opts.string    "-o", "--output", "Output file", required: true
    opts.string    "-r", "--dtb-path", "Path to Device tree files", required: true
    opts.string    "-O", "--dtb-overlay", "Device tree overlay file (optional)"
    opts.string    "-V", "--version-string", "Software version string (optional)"
    opts.string    "-S", "--sdk-string", "Software sdk version string (optional)"
    opts.string    "-D", "--date-string", "Software build date (optional)"
    opts.string    "-R", "--rev-string", "Software revision (optional)"
    opts.separator ""
    opts.separator "Extra options:"
    opts.string    "--rootfs", "Path to rootfs file (squashfs or similar)"
    opts.string    "--uboot-path", "Path to U-Boot binary"
    opts.bool      "-d", "--debug", "Show values of options"
    opts.on        "-h", "--help", "Show this message" do
        puts opts
        exit
    end
    opts
end

def parse_arguments(command_line_options=ARGV, parser)
    begin
        result = parser.parse command_line_options
    rescue Slop::Error => e
        # print help
        puts "Rescued: #{e.inspect}"
        puts arguments
        exit
    end
end

# Create an argument parser
parser = Slop::Parser.new(arguments)
# Parse arguments and store them into the $options hash
$options = parse_arguments(ARGV, parser).to_hash
# Populate the $options hash with additional
# key, value pairs that are not directly derived
# from the script's arguments.

if $options[:debug]
    $options.each do |key, value|
        puts " -- #{key} = #{value}"
    end
end

def create_its_file()
    $name = "#{$options[:workarea]}/fitimage.its"
    $src_file = File.new($name, "w")
    #...
    $src_file.puts("/dts-v1/;")
    $src_file.puts("/ {")
    $src_file.printf("        description = \"FIT image file on %s", $options[:machine])
    if $options[:version_string]
      $src_file.printf("\n                       @(#)Version: %s", $options[:version_string])
    end
    if $options[:date_string]
      $src_file.printf("\n                       @(#)Date   : %s", $options[:date_string])
    end
    if $options[:rev_string]
      $src_file.printf("\n                       @(#)Rev    : %s", $options[:rev_string])
    end
    if $options[:sdk_string]
      $src_file.printf("\n                       @(#)SDK    : %s", $options[:sdk_string])
    end
    $src_file.printf("\";\n")

    kernel_in  = "#{$options[:kernel_file]}"
    kernel_out = "#{$options[:workarea]}/zImage"
    FileUtils.cp(kernel_in, kernel_out)

    $src_file.puts("        images {")
    $src_file.puts("                kernel_iproc {")
    $src_file.puts("                        description = \"Linux kernel\";")
    $src_file.puts("                        data = /incbin/(\"#{kernel_out}\");")
    $src_file.puts("                        type = \"kernel\";")
    $src_file.puts("                        arch = \"#{$options[:arch]}\";")
    $src_file.puts("                        os = \"linux\";")
    $src_file.puts("                        compression = \"none\";")
    $src_file.puts("                        load = <0x61008000>;")
    $src_file.puts("                        entry = <0x61008000>;")
#    $src_file.puts("                        hash@1 {")
#    $src_file.puts("                                algo = \"crc32\";")
#    $src_file.puts("                        };")
    $src_file.puts("                };")

    if $options[:rootfs]
        rootpath = File.realpath($options[:rootfs])
        $src_file.puts("                ramdisk {")
        $src_file.puts("                        description = \"ramdisk\";")
        $src_file.puts("                        data = /incbin/(\"#{rootpath}\");")
        $src_file.puts("                        type = \"ramdisk\";")
        $src_file.puts("                        arch = \"#{$options[:arch]}\";")
        $src_file.puts("                        os = \"linux\";")
        $src_file.puts("                        compression = \"none\";")
#        $src_file.puts("                        hash@1 {")
#        $src_file.puts("                                algo = \"crc32\";")
#        $src_file.puts("                        };")
        $src_file.puts("                };")
    end

    $options[:board].each do |pcb|
        fdt_in  = "#{$options[:dtb_path]}/#{pcb}.dtb"
        fdt_out = "#{$options[:workarea]}/#{pcb}.dtb"
        FileUtils.cp(fdt_in, fdt_out)

        $src_file.puts("                fdt_#{pcb} {")
        $src_file.puts("                        description = \"Flattened Device Tree blob\";")
        $src_file.puts("                        data = /incbin/(\"#{fdt_out}\");")
        $src_file.puts("                        type = \"flat_dt\";")
        $src_file.puts("                        arch = \"#{$options[:arch]}\";")
        $src_file.puts("                        compression = \"none\";")
#        $src_file.puts("                        hash@1 {")
#        $src_file.puts("                                algo = \"crc32\";")
#        $src_file.puts("                        };")
        $src_file.puts("                };")
    end
    $src_file.puts("        };")
    $src_file.puts("")

    $options[:board].each_with_index do |pcb, ix|
        $src_file.puts("        configurations {")
        label = "wh2"
        puts "label = #{label}\n"

        $src_file.printf("		default = \"%s\";\n", label) if ix == 0
        $src_file.puts("                #{label} {")
        $src_file.puts("                        description = \"Boot Linux kernel with DT for #{pcb}\";")
        $src_file.puts("                        kernel = \"kernel_iproc\";")
        $src_file.puts("                        fdt = \"fdt_#{pcb}\";")
        if $options[:rootfs]
            $src_file.puts("                        ramdisk = \"ramdisk\";")
        end
        $src_file.puts("                };")
    end

    $src_file.puts("        };")
    $src_file.puts("};")
    $src_file.puts("")
    #...
    $src_file.close
end

def make_fit_file()
    syscmd("mkimage -f #{$options[:workarea]}/fitimage.its #{$options[:output]}")
end

def create_fit_file()
    Dir.mktmpdir('fitbuild') do |dir|
        $options[:workarea] = dir

        create_its_file()
        make_fit_file()
    end
end

create_fit_file()
