#include "system_interrupts.h"

void Dummy_Handler(void)
{
	for(;;);
}

__weak ADC_Handler()
{
	Dummy_Handler();
}

__weak BusFault_Handler()
{
	Dummy_Handler();
}

__weak void CAN1_RX0_Handler()
{
	Dummy_Handler();
}

__weak void CAN1_RX1_Handler()
{
	Dummy_Handler();
}

__weak void CAN1_SCE_Handler()
{
	Dummy_Handler();
}

__weak void CAN1_TX_Handler()
{
	Dummy_Handler();
}

__weak void CAN2_RX0_Handler()
{
	Dummy_Handler();
}

__weak void CAN2_RX1_Handler()
{
	Dummy_Handler();
}

__weak void CAN2_SCE_Handler()
{
	Dummy_Handler();
}

__weak void CAN2_TX_Handler()
{
	Dummy_Handler();
}

__weak void DCMI_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream0_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream1_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream2_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream3_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream4_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream5_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream6_Handler()
{
	Dummy_Handler();
}

__weak void DMA1_Stream7_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream0_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream1_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream2_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream3_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream4_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream5_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream6_Handler()
{
	Dummy_Handler();
}

__weak void DMA2_Stream7_Handler()
{
	Dummy_Handler();
}

__weak void DebugMon_Handler()
{
	Dummy_Handler();
}

__weak void ETH_Handler()
{
	Dummy_Handler();
}

__weak void ETH_WKUP_Handler()
{
	Dummy_Handler();
}

__weak void EXTI0_Handler()
{
	Dummy_Handler();
}

__weak void EXTI15_10_Handler()
{
	Dummy_Handler();
}

__weak void EXTI1_Handler()
{
	Dummy_Handler();
}

__weak void EXTI2_Handler()
{
	Dummy_Handler();
}

__weak void EXTI3_Handler()
{
	Dummy_Handler();
}

__weak void EXTI4_Handler()
{
	Dummy_Handler();
}

__weak void EXTI9_5_Handler()
{
	Dummy_Handler();
}

__weak void FLASH_Handler()
{
	Dummy_Handler();
}

__weak void FMC_Handler()
{
	Dummy_Handler();
}

__weak void FPU_Handler()
{
	Dummy_Handler();
}

__weak void HASH_RNG_Handler()
{
	Dummy_Handler();
}

__weak void HardFault_Handler()
{
	Dummy_Handler();
}

__weak void I2C1_ER_Handler()
{
	Dummy_Handler();
}

__weak void I2C1_EV_Handler()
{
	Dummy_Handler();
}

__weak void I2C2_ER_Handler()
{
	Dummy_Handler();
}

__weak void I2C2_EV_Handler()
{
	Dummy_Handler();
}

__weak void I2C3_ER_Handler()
{
	Dummy_Handler();
}

__weak void I2C3_EV_Handler()
{
	Dummy_Handler();
}

__weak void MemManage_Handler()
{
	Dummy_Handler();
}

__weak void NMI_Handler()
{
	Dummy_Handler();
}

__weak void OTG_FS_Handler()
{
	Dummy_Handler();
}

__weak void OTG_FS_WKUP_Handler()
{
	Dummy_Handler();
}

__weak void OTG_HS_EP1_IN_Handler()
{
	Dummy_Handler();
}

__weak void OTG_HS_EP1_OUT_Handler()
{
	Dummy_Handler();
}

__weak void OTG_HS_Handler()
{
	Dummy_Handler();
}

__weak void OTG_HS_WKUP_Handler()
{
	Dummy_Handler();
}

__weak void PVD_Handler()
{
	Dummy_Handler();
}

__weak void PendSV_Handler()
{
	Dummy_Handler();
}

__weak void RCC_Handler()
{
	Dummy_Handler();
}

__weak void RTC_Alarm_Handler()
{
	Dummy_Handler();
}

__weak void RTC_WKUP_Handler()
{
	Dummy_Handler();
}

__weak void Reset_Handler()
{
	Dummy_Handler();
}

__weak void SDIO_Handler()
{
	Dummy_Handler();
}

__weak void SPI1_Handler()
{
	Dummy_Handler();
}

__weak void SPI2_Handler()
{
	Dummy_Handler();
}

__weak void SPI3_Handler()
{
	Dummy_Handler();
}


__weak void SVC_Handler()
{
	Dummy_Handler();
}

__weak void SysTick_Handler()
{
	Dummy_Handler();
}

__weak void TAMP_STAMP_Handler()
{
	Dummy_Handler();
}

__weak void TIM1_BRK_TIM9_Handler()
{
	Dummy_Handler();
}

__weak void TIM1_CC_Handler()
{
	Dummy_Handler();
}

__weak void TIM1_TRG_COM_TIM11_Handler()
{
	Dummy_Handler();
}

__weak void TIM1_UP_TIM10_Handler()
{
	Dummy_Handler();
}

__weak void TIM2_Handler()
{
	Dummy_Handler();
}

__weak void TIM3_Handler()
{
	Dummy_Handler();
}

__weak void TIM4_Handler()
{
	Dummy_Handler();
}

__weak void TIM5_Handler()
{
	Dummy_Handler();
}

__weak void TIM6_DAC_Handler()
{
	Dummy_Handler();
}

__weak void TIM7_Handler()
{
	Dummy_Handler();
}

__weak void TIM8_BRK_TIM12_Handler()
{
	Dummy_Handler();
}

__weak void TIM8_CC_Handler()
{
	Dummy_Handler();
}

__weak void TIM8_TRG_COM_TIM14_Handler()
{
	Dummy_Handler();
}

__weak void TIM8_UP_TIM13_Handler()
{
	Dummy_Handler();
}

__weak void UART4_Handler()
{
	Dummy_Handler();
}

__weak void UART5_Handler()
{
	Dummy_Handler();
}

__weak void USART1_Handler()
{
	Dummy_Handler();
}

__weak void USART2_Handler()
{
	Dummy_Handler();
}

__weak void USART3_Handler()
{
	Dummy_Handler();
}

__weak void USART6_Handler()
{
	Dummy_Handler();
}

__weak void UsageFault_Handler()
{
	Dummy_Handler();
}

__weak void WWDG_Handler()
{
	Dummy_Handler();
}
