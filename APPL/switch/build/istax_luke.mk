#/************************************************************************/
#/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
#/*                      ALL RIGHTS RESERVED                             */
#/************************************************************************/
#
include $(BUILD)/make/templates/linuxSwitch.in
include $(BUILD)/make/ver_info.in

#include $(BUILD)/major.in
#include $(BUILD)/device.in
#include $(BUILD)/bsp.in
#include $(BUILD)/revision.in

# 指定新增构建模块
Custom/AddModules := vrrp tcpdump frr_irdp track frr_pim selftest frr_igmp status_manager

# 指定不构建模块
Custom/OmitModules := tsn tsn_frer poe redbox fan

#Custom/version := $(major_no).$(product).$(bsp).$(revision)
# 指定编译镜像文件名称
Custom/ImageName := centauri-luke-master-$(Verinfo)

# 指定编译路径：在 make/module_vtss_api.in 文件中，将其赋值给 CUSTOM_MEBA_DIR ， 在 vtss_api/meba/CMakeLists.txt 文件中，指定meba编译文件夹
Custom/Meba_Multi += luke
Custom/SDK_SUB_VERSION ?= master-20240816
# DefineTargetByPackage($1, $2)
# $1: package name
# $2: profile name
# Build all listed profiles
$(eval $(call DefineTargetByPackage,centauri,luke))

# Normal boilerplate
$(eval $(call linuxSwitch/Jaguar2c,ISTAX,BOARD_JAGUAR2_REF,JAGUAR_2,brsdk,mipsel))
$(eval $(call linuxSwitch/Build))
