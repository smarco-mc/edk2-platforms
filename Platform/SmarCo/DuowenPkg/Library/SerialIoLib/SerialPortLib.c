/** @file
*  UART Serial Port library functions
*
*  Copyright (c) 2022-2023, SmarCo Limited. All rights reserved.<BR>
*  Author: Lv Zheng <zhenglv@smart-core.cn>
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/SerialPortLib.h>
#include <Include/DuowenUart.h>

#ifdef CONFIG_DW_UART_DLF
#define dw_uart_convert_baudrate(freq, baud, div, frac) \
  do {                                                  \
    div = 0; frac = 0;                                  \
  } while (0)
#define dw_uart_config_frac(n, frac)                    \
  MmioWrite32(UART_DLF(n), frac)
#else
#define dw_uart_convert_baudrate(freq, baud, div, frac) \
  do {                                                  \
    div = (UINT16)((freq) / ((baud) << 4));             \
    frac = 0;                                           \
  } while (0)
#define dw_uart_config_frac(n, frac)
#endif

BOOLEAN Initiated = TRUE;

/**
* Convert normal serial port parameters to hardware configuration
*
* @params Ch       The standard serial port configuration
*
**/
UINT8 dw_uart_convert_params (
  IN UINT8 Params
  )
{
  UINT8 Cfg;

  Cfg = LCR_DLS(LCR_DLS_CHAR_BITS(uart_bits(Params)));

  switch (uart_parity(Params)) {
  case UART_PARITY_EVEN:
    Cfg |= LCR_EPS;
  case UART_PARITY_ODD:
    Cfg |= LCR_PEN;
    break;
  }

  if (uart_stopb(Params))
    Cfg |= LCR_STOP;

  return Cfg;
}

/**
* Character output to serial port.
*
* @param Ch        The character to serial port.
*
**/
VOID dw_uart_putchar (
  IN UINT8 Ch
  )
{
  while (!dw_uart_write_poll(UART_CON_ID));
  dw_uart_write_byte(UART_CON_ID, Ch);
}

/**
* Get character from serial port.
*
# @retval character        The character from serial port.
*
**/
UINT32 dw_uart_getchar (VOID)
{
  return dw_uart_read_byte(UART_CON_ID);
}

/**
  Initialize the serial device hardware.

  If no initialization is required, then return RETURN_SUCCESS.
  If the serial device was successfuly initialized, then return RETURN_SUCCESS.
  If the serial device could not be initialized, then return RETURN_DEVICE_ERROR.

  @retval RETURN_SUCCESS        The serial device was initialized.
  @retval RETURN_DEVICE_ERROR   The serail device could not be initialized.

**/
EFI_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
  UINT16 Divisor;
  UINT8 Fraction;
  BOOLEAN Latched = FALSE;

  dw_uart_modem_disable(UART_CON_ID);
  dw_uart_loopback_disable(UART_CON_ID);
  dw_uart_16750_disable(UART_CON_ID);
  dw_uart_irda_disable(UART_CON_ID);
  
  while (!Latched) {
    MmioOr32(UART_LCR(UART_CON_ID), LCR_DLAB);
    Latched = !!dw_uart_is_baud(UART_CON_ID);
  }
  dw_uart_convert_baudrate(APB_CLK_FREQ, UART_CON_BAUDRATE,
    Divisor, Fraction);
  while (!Latched) {
    MmioAnd32(UART_LCR(UART_CON_ID), ~LCR_DLAB);
    Latched = !!dw_uart_is_baud(UART_CON_ID);
  }
  MmioWrite32(UART_LCR(UART_CON_ID), dw_uart_convert_params(UART_DEF_PARAMS));
  dw_uart_config_fifo(UART_CON_ID);
  return EFI_SUCCESS;
}

/**
  Write data from buffer to serial device.

  Writes NumberOfBytes data bytes from Buffer to the serial device.
  The number of bytes actually written to the serial device is returned.
  If the return value is less than NumberOfBytes, then the write operation failed.

  If Buffer is NULL, then ASSERT().

  If NumberOfBytes is zero, then return 0.

  @param  Buffer           Pointer to the data buffer to be written.
  @param  NumberOfBytes    Number of bytes to written to the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes written to the serial device.
                           If this value is less than NumberOfBytes, then the write operation failed.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
  )
{
  UINTN Index;

  if (Buffer == NULL || Initiated == FALSE) {
    return 0;
  }

  for(Index = 0; Index < NumberOfBytes; Index ++) {
    dw_uart_putchar (Buffer [Index]);
  }

  return Index;
}

/**
  Reads data from a serial device into a buffer.

  @param  Buffer           Pointer to the data buffer to store the data read from the serial device.
  @param  NumberOfBytes    Number of bytes to read from the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes read from the serial device.
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
  )
{
  UINTN Index;

  if (NULL == Buffer || Initiated == FALSE) {
    return 0;
  }

  for (Index = 0; Index < NumberOfBytes; Index ++) {
    Buffer [Index] = (UINT8)dw_uart_getchar ();
  }

  return Index;
}

/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls aserial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  if (Initiated == FALSE) {
    return FALSE;
  }

  return dw_uart_read_poll(UART_CON_ID);
}

/**
  Sets the control bits on a serial device.

  @param Control                Sets the bits of Control that are settable.

  @retval RETURN_SUCCESS        The new control bits were set on the serial device.
  @retval RETURN_UNSUPPORTED    The serial device does not support this operation.
  @retval RETURN_DEVICE_ERROR   The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortSetControl (
  IN UINT32 Control
  )
{
  if (Initiated == FALSE) {
    return EFI_NOT_READY;
  }
  return RETURN_SUCCESS;
}

/**
  Retrieve the status of the control bits on a serial device.

  @param Control                A pointer to return the current control signals from the serial device.

  @retval RETURN_SUCCESS        The control bits were read from the serial device.
  @retval RETURN_UNSUPPORTED    The serial device does not support this operation.
  @retval RETURN_DEVICE_ERROR   The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortGetControl (
  OUT UINT32 *Control
  )
{
  if (Initiated == FALSE) {
    return EFI_NOT_READY;
  }
  *Control = 0;
  return RETURN_SUCCESS;
}

/**
  Sets the baud rate, receive FIFO depth, transmit/receice time out, parity,
  data bits, and stop bits on a serial device.

  @param BaudRate           The requested baud rate. A BaudRate value of 0 will use the
                            device's default interface speed.
                            On output, the value actually set.
  @param ReveiveFifoDepth   The requested depth of the FIFO on the receive side of the
                            serial interface. A ReceiveFifoDepth value of 0 will use
                            the device's default FIFO depth.
                            On output, the value actually set.
  @param Timeout            The requested time out for a single character in microseconds.
                            This timeout applies to both the transmit and receive side of the
                            interface. A Timeout value of 0 will use the device's default time
                            out value.
                            On output, the value actually set.
  @param Parity             The type of parity to use on this serial device. A Parity value of
                            DefaultParity will use the device's default parity value.
                            On output, the value actually set.
  @param DataBits           The number of data bits to use on the serial device. A DataBits
                            vaule of 0 will use the device's default data bit setting.
                            On output, the value actually set.
  @param StopBits           The number of stop bits to use on this serial device. A StopBits
                            value of DefaultStopBits will use the device's default number of
                            stop bits.
                            On output, the value actually set.

  @retval RETURN_SUCCESS            The new attributes were set on the serial device.
  @retval RETURN_UNSUPPORTED        The serial device does not support this operation.
  @retval RETURN_INVALID_PARAMETER  One or more of the attributes has an unsupported value.
  @retval RETURN_DEVICE_ERROR       The serial device is not functioning correctly.

**/
RETURN_STATUS
EFIAPI
SerialPortSetAttributes (
  IN OUT UINT64             *BaudRate,
  IN OUT UINT32             *ReceiveFifoDepth,
  IN OUT UINT32             *Timeout,
  IN OUT EFI_PARITY_TYPE    *Parity,
  IN OUT UINT8              *DataBits,
  IN OUT EFI_STOP_BITS_TYPE *StopBits
  )
{
  if (Initiated == FALSE) {
    return EFI_NOT_READY;
  }
  return RETURN_SUCCESS;
}
