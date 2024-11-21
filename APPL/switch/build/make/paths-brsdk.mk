#/************************************************************************/
#/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
#/*                      ALL RIGHTS RESERVED                             */
#/************************************************************************/

MSCC_SDK_VERSION       ?= 2023.12
MSCC_SDK_STEM          ?= mscc-brsdk
MSCC_SDK_BRANCH        ?=

BCM_BRSDK_VERSION      ?= 6.0.1
BCM_BRSDK_STEM         ?= bcm-brsdk

CTC_BRSDK_VERSION      ?= 2024.06
CTC_BRSDK_STEM         ?= ctc-brsdk

ifeq ($(MSCC_SDK_BRANCH),brsdk)
    MSCC_SDK_NAME          = $(MSCC_SDK_STEM)-$(MRDC_SDK_ARCH)-$(MSCC_SDK_VERSION)
else ifeq ($(MSCC_SDK_BRANCH),)
    MSCC_SDK_NAME          = $(MSCC_SDK_STEM)-$(MRDC_SDK_ARCH)-$(MSCC_SDK_VERSION)-$(Custom/SDK_SUB_VERSION)
else
    MSCC_SDK_NAME          = $(MSCC_SDK_STEM)-$(MRDC_SDK_ARCH)-$(MSCC_SDK_VERSION)-$(MSCC_SDK_BRANCH)
endif

MSCC_SDK_BASE          = /opt/mscc/$(MSCC_SDK_NAME)

ifeq ($(BCM_DEFINE), 1)
    MSCC_SDK_NAME          = $(BCM_BRSDK_STEM)-$(MRDC_SDK_ARCH)-$(BCM_BRSDK_VERSION)-$(Custom/SDK_SUB_VERSION)
    MSCC_SDK_BASE          = /opt/bcm/$(MSCC_SDK_NAME)
else ifeq ($(CTC_DEFINE), 1)
    MSCC_SDK_NAME          = $(CTC_BRSDK_STEM)-$(MRDC_SDK_ARCH)-$(CTC_BRSDK_VERSION)-$(Custom/SDK_SUB_VERSION)
    MSCC_SDK_BASE          = /opt/ctc/$(MSCC_SDK_NAME)
endif

ifeq ($(MRDC_SDK_ARCH),arm64)
    MSCC_SDK_GNU           = $(MSCC_SDK_BASE)/$(MSCC_SDK_TARGET)
    MSCC_SDK_UCLIBC        = $(MSCC_SDK_BASE)/$(MSCC_SDK_TARGET)
    MSCC_SDK_ROOTFS	       = $(MSCC_SDK_GNU)/xstax/release/rootfs.tar
else ifeq ($(MRDC_SDK_ARCH),arm)
    MSCC_SDK_GNU           = $(MSCC_SDK_BASE)/$(MSCC_SDK_TARGET)
    MSCC_SDK_UCLIBC        = $(MSCC_SDK_BASE)/$(MSCC_SDK_TARGET)
    MSCC_SDK_ROOTFS	       = $(MSCC_SDK_GNU)/xstax/release/rootfs.tar
else
    MSCC_SDK_GNU           = $(MSCC_SDK_BASE)/$(MSCC_SDK_TARGET)
    MSCC_SDK_UCLIBC        = $(MSCC_SDK_BASE)/mipsel-mips32r2-linux-uclibc
    MSCC_SDK_ROOTFS	       = $(MSCC_SDK_GNU)/xstax/release/rootfs.tar
endif

ifeq ($(BCM_DEFINE), 1)
    MSCC_SDK_ROOTFS        = $(MSCC_SDK_BASE)/release/rootfs.tar
else ifeq ($(CTC_DEFINE), 1)
    MSCC_SDK_ROOTFS        = $(MSCC_SDK_BASE)/release/rootfs.tar
endif

MSCC_SDK_INSTALL       ?= /usr/local/bin/mscc-install-pkg

MSCC_SDK_CMAKE_TC_PATH ?= $(MSCC_SDK_PATH)/usr/share/buildroot/toolchainfile.cmake
MSCC_SDK_CMAKE_TC ?= -DCMAKE_TOOLCHAIN_FILE=$(MSCC_SDK_CMAKE_TC_PATH)

include $(TOPABS)/build/make/paths-api.mk

init::
	$(call what, "Using brsdk:       $(MSCC_SDK_BASE) - $(MSCC_SDK_NAME) - $(MSCC_SDK_FLAVOR)")
	$(call what, "Using toolchain:   $(MRDC_TOOLCHAIN_BASE)")


# Unconditionally check (and possibly install) both toolchain and sdk. We need
# to do this unconditionally as the sdk may be installed and the toolchain may
# not be installed, and we cannot do the "same" trick as we do below, as the
# toolchain version depends on the sdk...
-include dummy
.PHONY: dummy
dummy:
	@MSCC_SDK_INSTALL=$(MSCC_SDK_INSTALL) \
	MSCC_SDK_NAME=$(MSCC_SDK_NAME) \
	MSCC_SDK_BRANCH=$(MSCC_SDK_BRANCH) \
	MSCC_SDK_VERSION=$(MSCC_SDK_VERSION) \
	MSCC_SDK_BASE=$(MSCC_SDK_BASE) \
	MSCC_SDK_SETUP=$(MSCC_SDK_BASE)/sdk-setup.mk \
	$(TOPABS)/build/make/install-sdk.rb

# Install the brsdk and toolchain if the $(MSCC_SDK_BASE)/sdk-setup.mk file is
# missing. This turns out to be needed to force the installation to take place
# before the '$(MSCC_SDK_BASE)/sdk-setup.mk' is loaded (if we only relay on the
# mechanism above then the sdk-setup.mk is not installed before including).
$(MSCC_SDK_BASE)/sdk-setup.mk:
	@MSCC_SDK_INSTALL=$(MSCC_SDK_INSTALL) \
	MSCC_SDK_NAME=$(MSCC_SDK_NAME) \
	MSCC_SDK_BRANCH=$(MSCC_SDK_BRANCH) \
	MSCC_SDK_VERSION=$(MSCC_SDK_VERSION) \
	MSCC_SDK_BASE=$(MSCC_SDK_BASE) \
	MSCC_SDK_SETUP=$(MSCC_SDK_BASE)/sdk-setup.mk \
	$(TOPABS)/build/make/install-sdk.rb
-include $(MSCC_SDK_BASE)/sdk-setup.mk

ifeq ($(BCM_DEFINE), 1)
MRDC_TOOLCHAIN_BASE    ?= /opt/bcm/bcm-toolchain-bin
else ifeq ($(CTC_DEFINE), 1)
MRDC_TOOLCHAIN_BASE    ?= /opt/ctc/ctc-toolchain-bin
else
MRDC_TOOLCHAIN_BASE    ?= /opt/mscc/mscc-toolchain-bin-${MSCC_TOOLCHAIN_FILE}
endif


MRDC_EXTERNAL_BUILD_ENV_TOP := $(MSCC_SDK_BASE)
export MRDC_EXTERNAL_BUILD_ENV_TOP
export MSCC_SDK_TARGET
export MSCC_SDK_SYSROOT
export MSCC_SDK_PATH
export MRDC_TOOLCHAIN_BASE

PATH := $(MSCC_SDK_PATH)/bin:$(MSCC_SDK_PATH)/sbin:$(MRDC_TOOLCHAIN_BASE)/bin:$(PATH)

