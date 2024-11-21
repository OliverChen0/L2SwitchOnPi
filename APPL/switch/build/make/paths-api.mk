#/************************************************************************/
#/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
#/*                      ALL RIGHTS RESERVED                             */
#/************************************************************************/

MESA_API_VERSION       ?= v2023.12-SOAK-8-gbca066f
MESA_API_BRANCH        ?= 2023.12-soak
MESA_API_NAME          ?= mesa-$(MESA_API_VERSION)@$(MESA_API_BRANCH)
MESA_API_BASE          ?= /opt/mscc/$(MESA_API_NAME)
MESA_API_INSTALL       ?= /usr/local/bin/mscc-install-pkg

ifneq ("$(wildcard $(TOP)/vtss_api)","")
API_PATH := $(TOP)/vtss_api
API_ABS_PATH := $(TOPABS)/vtss_api
ifneq ("$(wildcard $(API_PATH)/bin)","")
API_BUILD_PATH := $(API_PATH)/bin/${MRDC_SDK_ARCH}
else
API_BUILD_PATH := ./build_api
endif
else
API_PATH := $(MESA_API_BASE)
API_ABS_PATH := $(API_PATH)
API_BUILD_PATH := $(API_PATH)/bin/${MRDC_SDK_ARCH}
endif

export MESA_API_BRANCH
export MESA_API_VERSION
export MESA_API_NAME
export MESA_API_BASE
export MESA_API_INSTALL
export API_PATH
export API_BUILD_PATH

# BCM SDK
BCM_SDK_VERSION ?= 6.5.29
BCM_SDK_DIR := $(TOPABS)/bcm_sdk/sdk-xgs-$(BCM_SDK_VERSION)
BCM_BUILD_PATH := $(BCM_SDK_DIR)/systems/linux/user/iproc
BCM_LIB_PATH := $(BCM_SDK_DIR)/build/unix-user/iproc

export BCM_SDK_DIR BCM_BUILD_PATH BCM_LIB_PATH

# CTC SDK
CTC_SDK_DIR := $(TOPABS)/ctc_sdk/ctcsdk-V5.7.5RC
CTC_OBJ_DIR := $(CTC_SDK_DIR)/build.arm-cortex-a7.d
CTC_LIB_DIR := $(CTC_OBJ_DIR)/lib.linux-board
CTC_BIN_DIR := $(CTC_OBJ_DIR)/bin.linux-board

export CTC_SDK_DIR CTC_OBJ_DIR CTC_LIB_DIR CTC_BIN_DIR