/** @file
*  UART Serial Port library definitions
*
*  Copyright (c) 2022-2023, SmarCo Limited. All rights reserved.
*  Author: Lv Zheng <zhenglv@smart-core.cn>
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#ifndef __DWC_UART_SERIALPORTLIB_H__
#define __DWC_UART_SERIALPORTLIB_H__

#include <Include/DuowenBoard.h>

/* Generic sdfirm UART */
#define UART_BITS_MASK          0x0F
#define UART_PARITY_MASK        0x30
#define UART_STOPB_MASK         0x40
#define uart_bits(p)            ((p)&UART_BITS_MASK)
#define uart_parity(p)          ((p)&UART_PARITY_MASK)
#define uart_stopb(p)           ((p)&UART_STOPB_MASK)

#define UART_PARITY_NONE        0x00
#define UART_PARITY_ODD         0x10
#define UART_PARITY_EVEN        0x20

#define UART_STOPB_ONE          0x00
#define UART_STOPB_TWO          0x40

#define UART_DEF_PARAMS         (8 | UART_PARITY_NONE | UART_STOPB_ONE)
#define UART_CON_BAUDRATE       UART_CURRENT_SPEED

/* DWC_uart specific */
#define DW_UART_FIFO_MODE       FixedPcdGet16(PcdUartFifoDepth)

#define UART_RBR(n)             DW_UART_REG(n, 0x00)
#define UART_DLL(n)             DW_UART_REG(n, 0x00)
#define UART_THR(n)             DW_UART_REG(n, 0x00)
#define UART_DLH(n)             DW_UART_REG(n, 0x04)
#define UART_IER(n)             DW_UART_REG(n, 0x04)
#define UART_IIR(n)             DW_UART_REG(n, 0x08)
#define UART_LCR(n)             DW_UART_REG(n, 0x0C)
#define UART_MCR(n)             DW_UART_REG(n, 0x10)
#define UART_LSR(n)             DW_UART_REG(n, 0x14)
#define UART_MSR(n)             DW_UART_REG(n, 0x18)
#define UART_FAR(n)             DW_UART_REG(n, 0x70)
#define UART_SCR(n)             DW_UART_REG(n, 0x1C)
#define UART_USR(n)             DW_UART_REG(n, 0x7C)
#define UART_HTX(n)             DW_UART_REG(n, 0xA4)
#define UART_DMASA(n)           DW_UART_REG(n, 0xA8)

#define UART_FCR(n)             DW_UART_REG(n, 0x08)
#define UART_SDMAM(n)           DW_UART_REG(n, 0x94)
#define UART_SFE(n)             DW_UART_REG(n, 0x98)
#define UART_SRT(n)             DW_UART_REG(n, 0x9C)
#define UART_STET(n)            DW_UART_REG(n, 0xA0)

/* FIFO Control Register - FCR */
#define FCR_RT_OFFSET           6
#define FCR_RT_MASK             REG_2BIT_MASK
#define FCR_RT(value)           _SET_FV(FCR_RT, value)
#define FCR_RT_CHAR_1           0
#define FCR_RT_QUARTER_FULL     1
#define FCR_RT_HAFL_FULL        2
#define FCR_RT_2                3
#define FCR_TET_OFFSET          4
#define FCR_TET_MASK            REG_2BIT_MASK
#define FCR_TET(value)          _SET_FV(FCR_TET, value)
#define FCR_TET_EMPTY           0
#define FCR_TET_CHAR_2          1
#define FCR_TET_QUARTER_FULL    2
#define FCR_TET_HALF_FULL       3
#define FCR_DMAM                _BV(3)
#define FCR_XFIFOR              _BV(2)
#define FCR_RFIFOR              _BV(1)
#define FCR_FIFOE               _BV(0)
#define FCR_RESET_MASK          (FCR_XFIFOR | FCR_RFIFOR)

/* Interrupt Enable Register - IER */
#define IER_PTIME               _BV(7)
#define IER_ELCOLR              _BV(4)
#define IER_EDSSI               _BV(3)
#define IER_ELSI                _BV(2)
#define IER_ETBEI               _BV(1)
#define IER_ERBFI               _BV(0)

/* Interrupt Identification Register - IIR */
#define IIR_FIFOSE_OFFSET       6
#define IIR_FIFOSE_MASK         REG_2BIT_MASK
#define IIR_FIFOSE(value)       _GET_FV(IIR_FIFOSE, value)
#define IIR_IID_OFFSET          0
#define IIR_IID_MASK            REG_4BIT_MASK
#define IIR_IID(value)          _GET_FV(IIR_IID, value)
#define UART_IRQ_DSSI           0  /* Modem status */
#define UART_IRQ_NONE           1  /* No IRQ pending */
#define UART_IRQ_TBEI           2  /* THR empty */
#define UART_IRQ_RBFI           4  /* RBR full */
#define UART_IRQ_LSI            6  /* Receiver line status */
#define UART_IRQ_BUSY           7  /* Busy detet */
#define UART_IRQ_TIMEOUT        12 /* Character timeout */

/* Modem Control Register - MCR */
#define MCR_SIRE                _BV(6)
#define MCR_AFCE                _BV(5)
#define MCR_LOOPBACK            _BV(4)
#define MCR_OUT2                _BV(3)
#define MCR_OUT1                _BV(2)
#define MCR_RTS                 _BV(1)
#define MCR_DTR                 _BV(0)
/* Line Control Register - LCR */
#define LCR_DLAB                _BV(7) /* Divisor access latch */
#define LCR_BC                  _BV(6) /* Break control */
#define LCR_SP                  _BV(5) /* Stick parity */
#define LCR_EPS                 _BV(4) /* Even parity select */
#define LCR_PEN                 _BV(3) /* Parity enable */
/* 0: 1 stop bit
 *  * 1: 1.5 stop bit if 5 data bits, otherwise 2 stop bit
 *   */
#define LCR_STOP                _BV(2) /* Stop bit */
#define LCR_DLS_OFFSET          0
#define LCR_DLS_MASK            REG_2BIT_MASK
#define LCR_DLS(value)          _SET_FV(LCR_DLS, value)
#define LCR_DLS_CHAR_BITS(bit)  ((bit) - 5)
/* Line Status Register - LSR */
#define LSR_RFE                 _BV(7)
#define LSR_TEMT                _BV(6)
#define LSR_THRE                _BV(5)
#define LSR_BI                  _BV(4)
#define LSR_FE                  _BV(3)
#define LSR_PE                  _BV(2)
#define LSR_OE                  _BV(1)
#define LSR_DR                  _BV(0)

#define MCR_MODEM_MASK          (MCR_RTS | MCR_DTR)

#define dw_uart_config_fifo(n)                  \
    do {                                        \
        MmioWrite32(UART_FCR(n),                \
                    FCR_FIFOE |                 \
                    FCR_RT(FCR_RT_CHAR_1) |     \
                    FCR_TET(FCR_TET_EMPTY) |    \
                    FCR_RESET_MASK);            \
    } while (0)
#define dw_uart_irda_enable(n)
#define dw_uart_irda_disable(n)
#define dw_uart_16750_enable(n)                 \
    MmioOr32(UART_MCR(n), MCR_AFCE)
#define dw_uart_16750_disable(n)                \
    MmioAnd32(UART_MCR(n), ~MCR_AFCE)
#define dw_uart_loopback_enable(n)              \
    MmioOr32(UART_MCR(n), MCR_LOOPBACK)
#define dw_uart_loopback_disable(n)             \
    MmioAnd32(UART_MCR(n), MCR_LOOPBACK)
#define dw_uart_modem_enable(n)                 \
    MmioAndThenOr32(UART_MCR(n), ~MCR_MODEM_MASK, MCR_MODEM_MASK)
#define dw_uart_modem_disable(n)                \
    MmioAndThenOr32(UART_MCR(n), ~MCR_MODEM_MASK, 0)
#define dw_uart_is_baud(n)                      \
    (MmioRead32(UART_LCR(n)) & LCR_DLAB)
#define dw_uart_is_busy(n)                      \
    (MmioRead32(UART_USR(n)) & USR_BUSY)
#define dw_uart_write_poll(n)                   \
    (!!(MmioRead32(UART_LSR(n)) & LSR_THRE))
#define dw_uart_read_poll(n)                    \
    (!!(MmioRead32(UART_LSR(n)) & LSR_DR))
#define dw_uart_read_byte(n)                    \
    MmioRead32(UART_RBR(n))
#define dw_uart_write_byte(n, byte)             \
    do {                                        \
        while (dw_uart_is_baud(n));             \
        MmioWrite32(UART_THR(n), (byte));       \
    } while (0)

#define dw_uart_disable_all_irqs(n)             \
    MmioWrite32(UART_IER(n), 0)
#define dw_uart_enable_irq(n, irq)              \
    MmioOr32(UART_IER(n), irq)
#define dw_uart_disable_irq(n, irq)             \
    MmioAnd32(UART_IER(n), ~irq)

#endif
