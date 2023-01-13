## @file
#  Definitions of Flash definition file on SmarCo DUOWEN RISC-V platform
#
#  Copyright (c) 2022-2023, SmarCo Limited. All rights reserved.<BR>
#  Author: Lv Zheng <zhenglv@smart-core.cn>
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##
[Defines]
DEFINE BLOCK_SIZE        = 0x1000

DEFINE FW_BASE_ADDRESS   = 0x00000000
DEFINE FW_SIZE           = 0x00900000
DEFINE FW_BLOCKS         = 0x900

#
# 0x000000-0x7DFFFF code
# 0x7E0000-0x800000 variables
#
DEFINE CODE_BASE_ADDRESS = 0x00000000
DEFINE CODE_SIZE         = 0x00800000
DEFINE CODE_BLOCKS       = 0x800
DEFINE VARS_BLOCKS       = 0x20

#
# SEC + opensbi library is the root FW domain.
# The base address must be round up to log2.
#
DEFINE SECFV_OFFSET        = 0x00000000
DEFINE SECFV_SIZE          = 0x00040000
DEFINE ROOT_FW_DOMAIN_SIZE = $(SECFV_SIZE)

#
# Other FV regions are in the second FW domain.
# The size of memory region must be power of 2.
# The base address must be aligned with the size.
#
# FW memory region
#
DEFINE PEIFV_OFFSET                  = 0x00400000
DEFINE PEIFV_SIZE                    = 0x00180000
DEFINE FVMAIN_OFFSET                 = 0x00580000
DEFINE FVMAIN_SIZE                   = 0x00280000

#
# EFI Variable memory region.
# The total size of EFI Variable FD must include
# all of sub regions of EFI Variable
#
DEFINE VARS_OFFSET                   = 0x00800000
DEFINE VARS_SIZE                     = 0x00007000
DEFINE VARS_FTW_WORKING_OFFSET       = 0x00807000
DEFINE VARS_FTW_WORKING_SIZE         = 0x00001000
DEFINE VARS_FTW_SPARE_OFFSET         = 0x00808000
DEFINE VARS_FTW_SPARE_SIZE           = 0x00018000

#
# Device Tree memory region
#
DEFINE DTB_OFFSET                    = 0x00840000
DEFINE DTB_SIZE                      = 0x00002000

#
# Scratch area memory region
#
DEFINE SCRATCH_OFFSET                = 0x00880000
DEFINE SCRATCH_SIZE                  = 0x00010000


DEFINE FW_DOMAIN_SIZE    = $(FVMAIN_OFFSET) + $(FVMAIN_SIZE) - $(PEIFV_OFFSET)
DEFINE VARIABLE_FW_SIZE  = $(VARS_FTW_SPARE_OFFSET) + $(VARS_FTW_SPARE_SIZE) - $(VARS_OFFSET)

SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdRootFirmwareDomainBaseAddress = $(CODE_BASE_ADDRESS) + $(SECFV_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdRootFirmwareDomainSize        = $(ROOT_FW_DOMAIN_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdFirmwareDomainBaseAddress     = $(CODE_BASE_ADDRESS) + $(PEIFV_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdFirmwareDomainSize            = $(FW_DOMAIN_SIZE)

SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFdBaseAddress = $(FW_BASE_ADDRESS) + $(VARS_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFdSize        = $(VARS_SIZE) + $(VARS_FTW_WORKING_SIZE) + $(VARS_FTW_SPARE_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFdBlockSize   = $(BLOCK_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFirmwareRegionBaseAddress = $(CODE_BASE_ADDRESS) + $(VARS_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdVariableFirmwareRegionSize        = $(VARIABLE_FW_SIZE)

SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdOpenSbiStackSize = 8192
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdScratchRamBase   = $(CODE_BASE_ADDRESS) + $(SCRATCH_OFFSET)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdScratchRamSize   = $(SCRATCH_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdTemporaryRamBase = $(CODE_BASE_ADDRESS) + $(FW_SIZE)
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdTemporaryRamSize = 0x10000


SET gUefiRiscVPkgTokenSpaceGuid.PcdRiscVMachineTimerFrequencyInHerz    = 1000000
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdSocPllFreq              = 800000000  # 800MHz soc_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdDdrBusPllFreq           = 800000000  # 800MHz ddr_bus_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdDdrPllFreq              = 800000000  # 800MHz ddr_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdClPllFreq               = 1500000000 # 1.5GHz cl_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdCfabPllFreq             = 1000000000 # 1GHz cfab_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdSfabPllFreq             = 100000000  # 100MHz sfab_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdEthPllFreq              = 78125000   # 78.125MHz eth_pll
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdSgmiiPllFreq            = 125000000  # 125MHz sgmii_pll

SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdBootHartId                  = 0          # Boot hart ID
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdBootableHartNumber          = 16         # Bootable hard number the platform would like to use during boot
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdDdrMemorySize           = 0x10000000 # DDR memory size (default to 256MHz)
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdUartPortId              = 0          # Serial port ID
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdUartFifoDepth           = 64         # SoC designed FIFO depth
SET gSmarCoDuowenPlatformsPkgTokenSpaceGuid.PcdUartBaudRate            = 115200     # Serial port baud rate
SET gUefiRiscVPlatformPkgTokenSpaceGuid.PcdPeiCorePrivilegeMode        = 1          # Set PeiCore to S-Mode
