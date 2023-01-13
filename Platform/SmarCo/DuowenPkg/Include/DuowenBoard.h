/** @file
 *  Duowen board definitions
 *
 *  Copyright (c) 2022-2023, SmarCo Limited. All rights reserved.
 *  Author: Lv Zheng <zhenglv@smart-core.cn>
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/

#ifndef __DUOWEN_BOARD_H__
#define __DUOWEN_BOARD_H__

#include <Include/SdfirmGeneric.h>

#define SOC_BASE                0

/* Local fabric */
#define LCSR_BASE               ULL(0xFF91000000)
#define DEBUG_BASE              ULL(0xFF90000000)
#define SFAB_ROM_BASE           ULL(0xFF8F000000) /* Boot ROM */
#define SFAB_ROM_SIZE           0x100000
#define FLASH_BASE              ULL(0xFF88000000)
/* The SPINOR model uses 24-bit addressing, however some of the addresses
 * are overlapped with controller own registers, so it can only access
 * <16MB address space, say 15M here
 */
#define FLASH_SIZE              0x1E00000
#define SFAB_RAM_BASE           ULL(0xFF80000000) /* Sys Mem */
#define SFAB_RAM_SIZE           0x100000

/* System fabric */
#define __CRCNTL_BASE           ULL(0xFF60000000)
#define __SCSR_BASE             ULL(0xFF60100000)
#define __TLMM_BASE             ULL(0xFF60200000)
#define __GPIO0_BASE            ULL(0xFF61000000)
#define __GPIO1_BASE            ULL(0xFF61100000)
#define __GPIO2_BASE            ULL(0xFF61200000)
#define __XGMAC_BASE            ULL(0xFF6A000000)
#define __ETH_PLL_BASE          ULL(0xFF6A100000)
#define __XPCS_BASE             ULL(0xFF6A200000)
#define __PLIC_BASE             ULL(0xFF70000000)

#define CRCNTL_BASE             (SOC_BASE + __CRCNTL_BASE)
#define SCSR_BASE               (SOC_BASE + __SCSR_BASE)
#define TLMM_BASE               (SOC_BASE + __TLMM_BASE)
#define IMC_BASE                (SOC_BASE + ULL(0xFF60600000))
#define GPIO0_BASE              (SOC_BASE + __GPIO0_BASE)
#define GPIO1_BASE              (SOC_BASE + __GPIO1_BASE)
#define GPIO2_BASE              (SOC_BASE + __GPIO2_BASE)
#define SPI0_BASE               (SOC_BASE + ULL(0xFF62000000))
#define SPI1_BASE               (SOC_BASE + ULL(0xFF62100000))
#define SPI2_BASE               (SOC_BASE + ULL(0xFF62200000))
#define SPI3_BASE               (SOC_BASE + ULL(0xFF62300000))
#define SPISLV_BASE             (SOC_BASE + ULL(0xFF62400000))
#define UART0_BASE              (SOC_BASE + ULL(0xFF63000000))
#define UART1_BASE              (SOC_BASE + ULL(0xFF63100000))
#define UART2_BASE              (SOC_BASE + ULL(0xFF63200000))
#define UART3_BASE              (SOC_BASE + ULL(0xFF63300000))
#define I2C0_BASE               (SOC_BASE + ULL(0xFF64000000))
#define I2C1_BASE               (SOC_BASE + ULL(0xFF64100000))
#define I2C2_BASE               (SOC_BASE + ULL(0xFF64200000))
#define I2C3_BASE               (SOC_BASE + ULL(0xFF64300000))
#define I2C4_BASE               (SOC_BASE + ULL(0xFF64400000))
#define I2C5_BASE               (SOC_BASE + ULL(0xFF64500000))
#define I2C6_BASE               (SOC_BASE + ULL(0xFF64600000))
#define I2C7_BASE               (SOC_BASE + ULL(0xFF64700000))
#define I2CSLV0_BASE            (SOC_BASE + ULL(0xFF64800000))
#define I2CSLV1_BASE            (SOC_BASE + ULL(0xFF64900000))
#define I2CSLV2_BASE            (SOC_BASE + ULL(0xFF64A00000))
#define I2CSLV3_BASE            (SOC_BASE + ULL(0xFF64B00000))
#define WDT0_BASE               (SOC_BASE + ULL(0xFF65000000))
#define WDT1_BASE               (SOC_BASE + ULL(0xFF65100000))
#define TIMER0_BASE             (SOC_BASE + ULL(0xFF66000000))
#define TIMER1_BASE             (SOC_BASE + ULL(0xFF66100000))
#define TIMER2_BASE             (SOC_BASE + ULL(0xFF66200000))
#define TIMER3_BASE             (SOC_BASE + ULL(0xFF66300000))
#define SD_BASE	                (SOC_BASE + ULL(0xFF67000000))
#define XGMAC_BASE              (SOC_BASE + __XGMAC_BASE)
#define ETH_PLL_BASE            (SOC_BASE + __ETH_PLL_BASE)
#define XPCS_BASE               (SOC_BASE + __XPCS_BASE)
#define IRQC_BASE               (SOC_BASE + __PLIC_BASE)

/* Config fabric */
#define __CLUSTER0_BASE	        ULL(0xFF01000000)
#define __CLUSTER1_BASE         ULL(0xFF01100000)
#define __CLUSTER2_BASE         ULL(0xFF01200000)
#define __CLUSTER3_BASE         ULL(0xFF01300000)
#define __COHFAB_PLL_BASE       ULL(0xFF02100000)
#define __DMA_SMMU_BASE         ULL(0xFF08000000)

#define CLINT_BASE              (SOC_BASE + ULL(0xFF010F0000))
#define CLUSTER0_BASE           (SOC_BASE + __CLUSTER0_BASE)
#define CLUSTER1_BASE           (SOC_BASE + __CLUSTER1_BASE)
#define CLUSTER2_BASE           (SOC_BASE + __CLUSTER2_BASE)
#define CLUSTER3_BASE           (SOC_BASE + __CLUSTER3_BASE)
#define COHFAB_BASE             (SOC_BASE + ULL(0xFF02000000))
#define COHFAB_PLL_BASE         (SOC_BASE + __COHFAB_PLL_BASE)
#define DMA_BASE                (SOC_BASE + ULL(0xFF03000000))
#define DDR0_CTRL_BASE          (SOC_BASE + ULL(0xFF04000000))
#define DDR0_PHY_BASE           (SOC_BASE + ULL(0xFF05000000))
#define DDR1_CTRL_BASE          (SOC_BASE + ULL(0xFF06000000))
#define DDR1_PHY_BASE           (SOC_BASE + ULL(0xFF07000000))
#define DMA_SMMU_BASE           (SOC_BASE + __DMA_SMMU_BASE)
#define PCIE_SMMU_BASE          (SOC_BASE + ULL(0xFF08400000))
#define PCIE_SUB_CUST_BASE      (SOC_BASE + ULL(0xFF09000000))
#define PCIE0_CUST_BASE         (SOC_BASE + ULL(0xFF09001000))
#define PCIE1_CUST_BASE         (SOC_BASE + ULL(0xFF09002000))
#define PCIE2_CUST_BASE         (SOC_BASE + ULL(0xFF09003000))
#define PCIE3_CUST_BASE         (SOC_BASE + ULL(0xFF09004000))
#define PCIE0_CTRL_BASE         (SOC_BASE + ULL(0xFF09100000))
#define PCIE0_PHY_BASE          (SOC_BASE + ULL(0xFF09180000))
#define PCIE1_CTRL_BASE         (SOC_BASE + ULL(0xFF09200000))
#define PCIE1_PHY_BASE          (SOC_BASE + ULL(0xFF09280000))
#define PCIE2_CTRL_BASE         (SOC_BASE + ULL(0xFF09300000))
#define PCIE2_PHY_BASE          (SOC_BASE + ULL(0xFF09380000))
#define PCIE3_CTRL_BASE         (SOC_BASE + ULL(0xFF09400000))
#define PCIE3_PHY_BASE          (SOC_BASE + ULL(0xFF09480000))
#define TSENSOR_BASE            (SOC_BASE + ULL(0xFF0A000000))

#define MSG_BASE                (SOC_BASE + ULL(0xFF601FFF00))

#define __DEV_BASE              ULL(0xFF00000000)
#define DEV_BASE                (SOC_BASE + __DEV_BASE)
#define DEV_SIZE                ULL(0x0100000000)

/* DDR memory region */
#define __DDR_BASE              ULL(0x0000000000)
#define DDR_BASE                (SOC_BASE + __DDR_BASE)
#define __DDR_SIZE              SZ_512G
#define DDR_SIZE		PcdGet64(PcdDdrMemorySize)

/* PCIe memory region */
#define __PCIE_BASE             ULL(0x40000000000)
#define PCIE_BASE               (SOC_BASE + __PCIE_BASE)
#define PCIE_SIZE               SZ_2T

/* PLL frequencies */
#define XO_CLK_FREQ             25000000 /* 25MHz */
#define SOC_PLL_FREQ            PcdGet32(PcdSocPllFreq)
#define DDR_BUS_PLL_FREQ        PcdGet32(PcdDdrBusPllFreq)
#define DDR_PLL_FREQ            PcdGet32(PcdDdrPllFreq)
#define CFAB_PLL_FREQ           PcdGet32(PcdCfabPllFreq)
#define CL_PLL_FREQ             PcdGet32(PcdClPllFreq)
#define ETH_PLL_FREQ            PcdGet32(PcdEthPllFreq)
#define SFAB_PLL_FREQ           PcdGet32(PcdSfabPllFreq)
#define SGMII_PLL_FREQ          PcdGet32(PcdSgmiiPllFreq)

#define SOC_CLK_FREQ            SOC_PLL_FREQ
#define IMC_CLK_FREQ            (SOC_CLK_FREQ/2)
#define APC_CLK_FREQ            CL_PLL_FREQ
#define SFAB_CLK_FREQ           SFAB_PLL_FREQ
#define CFAB_CLK_FREQ           CFAB_PLL_FREQ
#define APB_CLK_FREQ            SFAB_CLK_FREQ
#define AHB_CLK_FREQ            SFAB_CLK_FREQ

/* UART serial port */
#define UART_CON_ID             FixedPcdGet8(PcdUartPortId)
#define DUOWEN_UART_BASE        (UART0_BASE + (UART_CON_ID << 20))
#define DW_UART_REG(n, offset)  (DUOWEN_UART_BASE + (offset))
#define UART_CURRENT_SPEED      PcdGet32(PcdUartBaudRate)

#endif
