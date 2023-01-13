/** @file
 *  RISC-V Timer Architectural definition for DUOWEN platform.
 *
 *  Copyright (c) 2022-2023, SmarCo Limited. All rights reserved.<BR>
 *  Author: Lv Zheng <zhenglv@smart-core.cn>
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/
#ifndef __DUOWEN_CLINT_H__
#define __DUOWEN_CLINT_H__

#define CLINT_REG_BASE_ADDR         0xFF010F0000
    #define CLINT_REG_MTIME         0xFF010FBFF8
    #define CLINT_REG_MTIMECMP0     0xFF010F4000
    #define CLINT_REG_MTIMECMP1     0xFF010F4008
    #define CLINT_REG_MTIMECMP2     0xFF010F4010
    #define CLINT_REG_MTIMECMP3     0xFF010F4018
    #define CLINT_REG_MTIMECMP4     0xFF010F4020
    #define CLINT_REG_MTIMECMP5     0xFF010F4028
    #define CLINT_REG_MTIMECMP6     0xFF010F4030
    #define CLINT_REG_MTIMECMP7     0xFF010F4038
    #define CLINT_REG_MTIMECMP8     0xFF010F4040
    #define CLINT_REG_MTIMECMP9     0xFF010F4048
    #define CLINT_REG_MTIMECMP10    0xFF010F4050
    #define CLINT_REG_MTIMECMP11    0xFF010F4058
    #define CLINT_REG_MTIMECMP12    0xFF010F4060
    #define CLINT_REG_MTIMECMP13    0xFF010F4068
    #define CLINT_REG_MTIMECMP14    0xFF010F4070
    #define CLINT_REG_MTIMECMP15    0xFF010F4078

#endif
