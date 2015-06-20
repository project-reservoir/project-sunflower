#include "system_interrupts.h"
#include "cmsis_os.h"
#include "app_header.h"

extern void __main(void);

void Reset_Handler(void)
{
	SystemInit();
	__main();
}

void SysTick_Handler(void)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
	}

	HAL_IncTick();
}

// These functions are the "static" handlers. They're placed at fixed memory addresses 
// and call the real handlers, which can be placed anywhere.
// DO NOT CHANGE THESE FUNCTIONS. THEY ALL COMPILE DOWN TO EXACTLY 8 BYTES EACH AND CHANGING
// THAT AMOUNT WILL CAUSE THE BOOTLOADER TO FAIL. LIKEWISE, DO NOT CREATE INTERRUPT HANDLERS 
// THAT COMPILE DOWN TO LESS THAN 8 INSTRUCTIONS. THE COMPILER WILL OPTIMIZE THEM AWAY AND MESS
// UP THE ALIGNMENT OF THIS SECTION.

__attribute__((section("!!!!0.ADC_Handler"))) void ADC_Handler_Standin() { ADC_Handler(); }
__attribute__((section("!!!!0.BusFault_Handler"))) void BusFault_Handler_Standin() { BusFault_Handler(); } { BusFault_Handler(); }
__attribute__((section("!!!!0.CAN1_RX0_Handler"))) void CAN1_RX0_Handler_Standin() { CAN1_RX0_Handler(); } { CAN1_RX0_Handler(); }
__attribute__((section("!!!!0.CAN1_RX1_Handler"))) void CAN1_RX1_Handler_Standin() { CAN1_RX1_Handler(); } { CAN1_RX1_Handler(); }
__attribute__((section("!!!!0.CAN1_SCE_Handler"))) void CAN1_SCE_Handler_Standin() { CAN1_SCE_Handler(); } { CAN1_SCE_Handler(); }
__attribute__((section("!!!!0.CAN1_TX_Handler"))) void CAN1_TX_Handler_Standin() { CAN1_TX_Handler(); }
__attribute__((section("!!!!0.CAN2_RX0_Handler"))) void CAN2_RX0_Handler_Standin() { CAN2_RX0_Handler(); }
__attribute__((section("!!!!0.CAN2_RX1_Handler"))) void CAN2_RX1_Handler_Standin() { CAN2_RX1_Handler(); }
__attribute__((section("!!!!0.CAN2_SCE_Handler"))) void CAN2_SCE_Handler_Standin() { CAN2_SCE_Handler(); }
__attribute__((section("!!!!0.CAN2_TX_Handler"))) void CAN2_TX_Handler_Standin() { CAN2_TX_Handler(); }
__attribute__((section("!!!!0.DCMI_Handler"))) void DCMI_Handler_Standin() { DCMI_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream0_Handler"))) void DMA1_Stream0_Handler_Standin() { DMA1_Stream0_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream1_Handler"))) void DMA1_Stream1_Handler_Standin() { DMA1_Stream1_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream2_Handler"))) void DMA1_Stream2_Handler_Standin() { DMA1_Stream2_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream3_Handler"))) void DMA1_Stream3_Handler_Standin() { DMA1_Stream3_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream4_Handler"))) void DMA1_Stream4_Handler_Standin() { DMA1_Stream4_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream5_Handler"))) void DMA1_Stream5_Handler_Standin() { DMA1_Stream5_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream6_Handler"))) void DMA1_Stream6_Handler_Standin() { DMA1_Stream6_Handler(); }
__attribute__((section("!!!!0.DMA1_Stream7_Handler"))) void DMA1_Stream7_Handler_Standin() { DMA1_Stream7_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream0_Handler"))) void DMA2_Stream0_Handler_Standin() { DMA2_Stream0_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream1_Handler"))) void DMA2_Stream1_Handler_Standin() { DMA2_Stream1_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream2_Handler"))) void DMA2_Stream2_Handler_Standin() { DMA2_Stream2_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream3_Handler"))) void DMA2_Stream3_Handler_Standin() { DMA2_Stream3_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream4_Handler"))) void DMA2_Stream4_Handler_Standin() { DMA2_Stream4_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream5_Handler"))) void DMA2_Stream5_Handler_Standin() { DMA2_Stream5_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream6_Handler"))) void DMA2_Stream6_Handler_Standin() { DMA2_Stream6_Handler(); }
__attribute__((section("!!!!0.DMA2_Stream7_Handler"))) void DMA2_Stream7_Handler_Standin() { DMA2_Stream7_Handler(); }
__attribute__((section("!!!!0.DebugMon_Handler"))) void DebugMon_Handler_Standin() { DebugMon_Handler(); }
__attribute__((section("!!!!0.ETH_Handler"))) void ETH_Handler_Standin() { ETH_Handler(); }
__attribute__((section("!!!!0.ETH_WKUP_Handler"))) void ETH_WKUP_Handler_Standin() { ETH_WKUP_Handler(); }
__attribute__((section("!!!!0.EXTI0_Handler"))) void EXTI0_Handler_Standin() { EXTI0_Handler(); }
__attribute__((section("!!!!0.EXTI15_10_Handler"))) void EXTI15_10_Handler_Standin() { EXTI15_10_Handler(); }
__attribute__((section("!!!!0.EXTI1_Handler"))) void EXTI1_Handler_Standin() { EXTI1_Handler(); }
__attribute__((section("!!!!0.EXTI2_Handler"))) void EXTI2_Handler_Standin() { EXTI2_Handler(); }
__attribute__((section("!!!!0.EXTI3_Handler"))) void EXTI3_Handler_Standin() { EXTI3_Handler(); }
__attribute__((section("!!!!0.EXTI4_Handler"))) void EXTI4_Handler_Standin() { EXTI4_Handler(); }
__attribute__((section("!!!!0.EXTI9_5_Handler"))) void EXTI9_5_Handler_Standin() { EXTI9_5_Handler(); }
__attribute__((section("!!!!0.FLASH_Handler"))) void FLASH_Handler_Standin() { FLASH_Handler(); }
__attribute__((section("!!!!0.FMC_Handler"))) void FMC_Handler_Standin() { FMC_Handler(); }
__attribute__((section("!!!!0.FPU_Handler"))) void FPU_Handler_Standin() { FPU_Handler(); }
__attribute__((section("!!!!0.HASH_RNG_Handler"))) void HASH_RNG_Handler_Standin() { HASH_RNG_Handler(); }
__attribute__((section("!!!!0.HardFault_Handler"))) void HardFault_Handler_Standin() { HardFault_Handler(); }
__attribute__((section("!!!!0.I2C1_ER_Handler"))) void I2C1_ER_Handler_Standin() { I2C1_ER_Handler(); }
__attribute__((section("!!!!0.I2C1_EV_Handler"))) void I2C1_EV_Handler_Standin() { I2C1_EV_Handler(); }
__attribute__((section("!!!!0.I2C2_ER_Handler"))) void I2C2_ER_Handler_Standin() { I2C2_ER_Handler(); }
__attribute__((section("!!!!0.I2C2_EV_Handler"))) void I2C2_EV_Handler_Standin() { I2C2_EV_Handler(); }
__attribute__((section("!!!!0.I2C3_ER_Handler"))) void I2C3_ER_Handler_Standin() { I2C3_ER_Handler(); }
__attribute__((section("!!!!0.I2C3_EV_Handler"))) void I2C3_EV_Handler_Standin() { I2C3_EV_Handler(); }
__attribute__((section("!!!!0.MemManage_Handler"))) void MemManage_Handler_Standin() { MemManage_Handler(); }
__attribute__((section("!!!!0.NMI_Handler"))) void NMI_Handler_Standin() { NMI_Handler(); }
__attribute__((section("!!!!0.OTG_FS_Handler"))) void OTG_FS_Handler_Standin() { OTG_FS_Handler(); }
__attribute__((section("!!!!0.OTG_FS_WKUP_Handler"))) void OTG_FS_WKUP_Handler_Standin() { OTG_FS_WKUP_Handler(); }
__attribute__((section("!!!!0.OTG_HS_EP1_IN_Handler"))) void OTG_HS_EP1_IN_Handler_Standin() { OTG_HS_EP1_IN_Handler(); }
__attribute__((section("!!!!0.OTG_HS_EP1_OUT_Handler"))) void OTG_HS_EP1_OUT_Handler_Standin() { OTG_HS_EP1_OUT_Handler(); }
__attribute__((section("!!!!0.OTG_HS_Handler"))) void OTG_HS_Handler_Standin() { OTG_HS_Handler(); }
__attribute__((section("!!!!0.OTG_HS_WKUP_Handler"))) void OTG_HS_WKUP_Handler_Standin() { OTG_HS_WKUP_Handler(); }
__attribute__((section("!!!!0.PVD_Handler"))) void PVD_Handler_Standin() { PVD_Handler(); }
__attribute__((section("!!!!0.PendSV_Handler"))) void PendSV_Handler_Standin() { PendSV_Handler(); }
__attribute__((section("!!!!0.RCC_Handler"))) void RCC_Handler_Standin() { RCC_Handler(); }
__attribute__((section("!!!!0.RTC_Alarm_Handler"))) void RTC_Alarm_Handler_Standin() { RTC_Alarm_Handler(); }
__attribute__((section("!!!!0.RTC_WKUP_Handler"))) void RTC_WKUP_Handler_Standin() { RTC_WKUP_Handler(); }
__attribute__((section("!!!!0.Reset_Handler"))) void Reset_Handler_Standin() { Reset_Handler(); }
__attribute__((section("!!!!0.SDIO_Handler"))) void SDIO_Handler_Standin() { SDIO_Handler(); }
__attribute__((section("!!!!0.SPI1_Handler"))) void SPI1_Handler_Standin() { SPI1_Handler(); }
__attribute__((section("!!!!0.SPI2_Handler"))) void SPI2_Handler_Standin() { SPI2_Handler(); }
__attribute__((section("!!!!0.SPI3_Handler"))) void SPI3_Handler_Standin() { SPI3_Handler(); }
__attribute__((section("!!!!0.SVC_Handler"))) void SVC_Handler_Standin() { SVC_Handler(); }
__attribute__((section("!!!!0.SysTick_Handler"))) void SysTick_Handler_Standin() { SysTick_Handler(); }
__attribute__((section("!!!!0.TAMP_STAMP_Handler"))) void TAMP_STAMP_Handler_Standin() { TAMP_STAMP_Handler(); }
__attribute__((section("!!!!0.TIM1_BRK_TIM9_Handler"))) void TIM1_BRK_TIM9_Handler_Standin() { TIM1_BRK_TIM9_Handler(); }
__attribute__((section("!!!!0.TIM1_CC_Handler"))) void TIM1_CC_Handler_Standin() { TIM1_CC_Handler(); }
__attribute__((section("!!!!0.TIM1_TRG_COM_TIM11_Handler"))) void TIM1_TRG_COM_TIM11_Handler_Standin() { TIM1_TRG_COM_TIM11_Handler(); }
__attribute__((section("!!!!0.TIM1_UP_TIM10_Handler"))) void TIM1_UP_TIM10_Handler_Standin() { TIM1_UP_TIM10_Handler(); }
__attribute__((section("!!!!0.TIM2_Handler"))) void TIM2_Handler_Standin() { TIM2_Handler(); }
__attribute__((section("!!!!0.TIM3_Handler"))) void TIM3_Handler_Standin() { TIM3_Handler(); }
__attribute__((section("!!!!0.TIM4_Handler"))) void TIM4_Handler_Standin() { TIM4_Handler(); }
__attribute__((section("!!!!0.TIM5_Handler"))) void TIM5_Handler_Standin() { TIM5_Handler(); }
__attribute__((section("!!!!0.TIM6_DAC_Handler"))) void TIM6_DAC_Handler_Standin() { TIM6_DAC_Handler(); }
__attribute__((section("!!!!0.TIM7_Handler"))) void TIM7_Handler_Standin() { TIM7_Handler(); }
__attribute__((section("!!!!0.TIM8_BRK_TIM12_Handler"))) void TIM8_BRK_TIM12_Handler_Standin() { TIM8_BRK_TIM12_Handler(); }
__attribute__((section("!!!!0.TIM8_CC_Handler"))) void TIM8_CC_Handler_Standin() { TIM8_CC_Handler(); }
__attribute__((section("!!!!0.TIM8_TRG_COM_TIM14_Handler"))) void TIM8_TRG_COM_TIM14_Handler_Standin() { TIM8_TRG_COM_TIM14_Handler(); }
__attribute__((section("!!!!0.TIM8_UP_TIM13_Handler"))) void TIM8_UP_TIM13_Handler_Standin() { TIM8_UP_TIM13_Handler(); }
__attribute__((section("!!!!0.UART4_Handler"))) void UART4_Handler_Standin() { UART4_Handler(); }
__attribute__((section("!!!!0.UART5_Handler"))) void UART5_Handler_Standin() { UART5_Handler(); }
__attribute__((section("!!!!0.USART1_Handler"))) void USART1_Handler_Standin() { USART1_Handler(); }
__attribute__((section("!!!!0.USART2_Handler"))) void USART2_Handler_Standin() { USART2_Handler(); }
__attribute__((section("!!!!0.USART3_Handler"))) void USART3_Handler_Standin() { USART3_Handler(); }
__attribute__((section("!!!!0.USART6_Handler"))) void USART6_Handler_Standin() { USART6_Handler(); }
__attribute__((section("!!!!0.UsageFault_Handler"))) void UsageFault_Handler_Standin() { UsageFault_Handler(); }
__attribute__((section("!!!!0.WWDG_Handler"))) void WWDG_Handler_Standin() { WWDG_Handler(); }