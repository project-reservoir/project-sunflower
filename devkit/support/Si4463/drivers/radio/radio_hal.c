/*!
 * File:
 *  radio_hal.c
 *
 * Description:
 *  This file contains RADIO HAL.
 *
 * Silicon Laboratories Confidential
 * Copyright 2011 Silicon Laboratories, Inc.
 */

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */

#include "..\..\bsp.h"
#include "radio.h"
#include "spi.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */
                 
                /* ======================================= *
                 *      L O C A L   F U N C T I O N S      *
                 * ======================================= */

                /* ======================================= *
                 *     P U B L I C   F U N C T I O N S     *
                 * ======================================= */

void radio_hal_AssertShutdown(void)
{
    GPIO_SetBits(RADIO_SDL_GPIO_PORT, RADIO_SDL_PIN);
}

void radio_hal_DeassertShutdown(void)
{
    GPIO_ResetBits(RADIO_SDL_GPIO_PORT, RADIO_SDL_PIN);
}

void radio_hal_ClearNsel(void)
{
    GPIO_ResetBits(SPIn_NSS_GPIO_PORT, SPIn_NSS_PIN);
}

void radio_hal_SetNsel(void)
{
    GPIO_SetBits(SPIn_NSS_GPIO_PORT, SPIn_NSS_PIN);
}

BIT radio_hal_NirqLevel(void)
{
    return GPIO_ReadInputDataBit(RADIO_NIRQ_GPIO_PORT, RADIO_NIRQ_PIN);
}

void radio_hal_SpiWriteByte(U8 byteToWrite)
{   
    //taskENTER_CRITICAL();
    SPI_WriteByte(byteToWrite);
    SPI_WaitForNotBusy();
    //taskEXIT_CRITICAL();
}

U8 radio_hal_SpiReadByte(void)
{
    uint8_t byte;
    //taskENTER_CRITICAL();
    SPI_ReadByte(&byte);
    SPI_WaitForNotBusy();
    //taskEXIT_CRITICAL();
    return byte;
}

void radio_hal_SpiWriteData(U8 byteCount, U8* pData)
{
    //taskENTER_CRITICAL();
    SPI_WriteBytes(pData, byteCount);
    SPI_WaitForNotBusy();
    //taskEXIT_CRITICAL();
}

void radio_hal_SpiReadData(U8 byteCount, U8* pData)
{
    //taskENTER_CRITICAL();
    SPI_ReadBytes(pData, byteCount);
    SPI_WaitForNotBusy();
    //taskEXIT_CRITICAL();
}

#ifdef RADIO_DRIVER_EXTENDED_SUPPORT
BIT radio_hal_Gpio0Level(void)
{
  BIT retVal = FALSE;

#ifdef SILABS_PLATFORM_DKMB
  retVal = FALSE;
#endif
#ifdef SILABS_PLATFORM_UDP
  retVal = EZRP_RX_DOUT;
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCDBB)
  retVal = RF_GPIO0;
#endif
#if (defined SILABS_PLATFORM_WMB930)
  retVal = FALSE;
#endif
#if defined (SILABS_PLATFORM_WMB912)
  #ifdef SILABS_IO_WITH_EXTENDER
    //TODO
    retVal = FALSE;
  #endif
#endif

  return retVal;
}

BIT radio_hal_Gpio1Level(void)
{
  return FALSE;
}

BIT radio_hal_Gpio2Level(void)
{
  BIT retVal = FALSE;

#ifdef SILABS_PLATFORM_DKMB
  retVal = DATA_NFFS;
#endif
#ifdef SILABS_PLATFORM_UDP
  retVal = FALSE; //No Pop
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCDBB) || (defined SILABS_PLATFORM_WMB930)
  retVal = RF_GPIO2;
#endif
#if defined (SILABS_PLATFORM_WMB912)
  #ifdef SILABS_IO_WITH_EXTENDER
    //TODO
    retVal = FALSE;
  #endif
#endif

  return retVal;
}

BIT radio_hal_Gpio3Level(void)
{
  BIT retVal = FALSE;

#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCDBB) || (defined SILABS_PLATFORM_WMB930)
  retVal = RF_GPIO3;
#elif defined (SILABS_PLATFORM_WMB912)
  #ifdef SILABS_IO_WITH_EXTENDER
    //TODO
    retVal = FALSE;
  #endif
#endif

  return retVal;
}

#endif
