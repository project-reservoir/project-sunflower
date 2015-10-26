#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Dummy_Handler(void) __attribute__((used));
     
void ADC_Handler(void) __attribute__((used));
void BusFault_Handler(void) __attribute__((used));
void CAN1_RX0_Handler(void) __attribute__((used));
void CAN1_RX1_Handler(void) __attribute__((used));
void CAN1_SCE_Handler(void) __attribute__((used));
void CAN1_TX_Handler(void) __attribute__((used));
void CAN2_RX0_Handler(void) __attribute__((used));
void CAN2_RX1_Handler(void) __attribute__((used));
void CAN2_SCE_Handler(void) __attribute__((used));
void CAN2_TX_Handler(void) __attribute__((used));
void DCMI_Handler(void) __attribute__((used));
void DMA1_Stream0_Handler(void) __attribute__((used));
void DMA1_Stream1_Handler(void) __attribute__((used));
void DMA1_Stream2_Handler(void) __attribute__((used));
void DMA1_Stream3_Handler(void) __attribute__((used));
void DMA1_Stream4_Handler(void) __attribute__((used));
void DMA1_Stream5_Handler(void) __attribute__((used));
void DMA1_Stream6_Handler(void) __attribute__((used));
void DMA1_Stream7_Handler(void) __attribute__((used));
void DMA2_Stream0_Handler(void) __attribute__((used));
void DMA2_Stream1_Handler(void) __attribute__((used));
void DMA2_Stream2_Handler(void) __attribute__((used));
void DMA2_Stream3_Handler(void) __attribute__((used));
void DMA2_Stream4_Handler(void) __attribute__((used));
void DMA2_Stream5_Handler(void) __attribute__((used));
void DMA2_Stream6_Handler(void) __attribute__((used));
void DMA2_Stream7_Handler(void) __attribute__((used));
void DebugMon_Handler(void) __attribute__((used));
void ETH_Handler(void) __attribute__((used));
void ETH_WKUP_Handler(void) __attribute__((used));
void EXTI0_Handler(void) __attribute__((used));
void EXTI15_10_Handler(void) __attribute__((used));
void EXTI1_Handler(void) __attribute__((used));
void EXTI2_Handler(void) __attribute__((used));
void EXTI3_Handler(void) __attribute__((used));
void EXTI4_Handler(void) __attribute__((used));
void EXTI9_5_Handler(void) __attribute__((used));
void FLASH_Handler(void) __attribute__((used));
void FMC_Handler(void) __attribute__((used));
void FPU_Handler(void) __attribute__((used));
void HASH_RNG_Handler(void) __attribute__((used));
void HardFault_Handler(void) __attribute__((used));
void I2C1_ER_Handler(void) __attribute__((used));
void I2C1_EV_Handler(void) __attribute__((used));
void I2C2_ER_Handler(void) __attribute__((used));
void I2C2_EV_Handler(void) __attribute__((used));
void I2C3_ER_Handler(void) __attribute__((used));
void I2C3_EV_Handler(void) __attribute__((used));
void MemManage_Handler(void) __attribute__((used));
void NMI_Handler(void) __attribute__((used));
void OTG_FS_Handler(void) __attribute__((used));
void OTG_FS_WKUP_Handler(void) __attribute__((used));
void OTG_HS_EP1_IN_Handler(void) __attribute__((used));
void OTG_HS_EP1_OUT_Handler(void) __attribute__((used));
void OTG_HS_Handler(void) __attribute__((used));
void OTG_HS_WKUP_Handler(void) __attribute__((used));
void PVD_Handler(void) __attribute__((used));
void PendSV_Handler(void) __attribute__((used));
void RCC_Handler(void) __attribute__((used));
void RTC_Alarm_Handler(void) __attribute__((used));
void RTC_WKUP_Handler(void) __attribute__((used));
void Reset_Handler(void) __attribute__((used));
void SDIO_Handler(void) __attribute__((used));
void SPI1_Handler(void) __attribute__((used));
void SPI2_Handler(void) __attribute__((used));
void SPI3_Handler(void) __attribute__((used));
void SVC_Handler(void) __attribute__((used));
void SysTick_Handler(void) __attribute__((used));
void TAMP_STAMP_Handler(void) __attribute__((used));
void TIM1_BRK_TIM9_Handler(void) __attribute__((used));
void TIM1_CC_Handler(void) __attribute__((used));
void TIM1_TRG_COM_TIM11_Handler(void) __attribute__((used));
void TIM1_UP_TIM10_Handler(void) __attribute__((used));
void TIM2_Handler(void) __attribute__((used));
void TIM3_Handler(void) __attribute__((used));
void TIM4_Handler(void) __attribute__((used));
void TIM5_Handler(void) __attribute__((used));
void TIM6_DAC_Handler(void) __attribute__((used));
void TIM7_Handler(void) __attribute__((used));
void TIM8_BRK_TIM12_Handler(void) __attribute__((used));
void TIM8_CC_Handler(void) __attribute__((used));
void TIM8_TRG_COM_TIM14_Handler(void) __attribute__((used));
void TIM8_UP_TIM13_Handler(void) __attribute__((used));
void UART4_Handler(void) __attribute__((used));
void UART5_Handler(void) __attribute__((used));
void USART1_Handler(void) __attribute__((used));
void USART2_Handler(void) __attribute__((used));
void USART3_Handler(void) __attribute__((used));
void USART6_Handler(void) __attribute__((used));
void UsageFault_Handler(void) __attribute__((used));
void WWDG_Handler(void) __attribute__((used));

void ADC_Handler_Standin(void) __attribute__((used));
void BusFault_Handler_Standin(void) __attribute__((used));
void CAN1_RX0_Handler_Standin(void) __attribute__((used));
void CAN1_RX1_Handler_Standin(void) __attribute__((used));
void CAN1_SCE_Handler_Standin(void) __attribute__((used));
void CAN1_TX_Handler_Standin(void) __attribute__((used));
void CAN2_RX0_Handler_Standin(void) __attribute__((used));
void CAN2_RX1_Handler_Standin(void) __attribute__((used));
void CAN2_SCE_Handler_Standin(void) __attribute__((used));
void CAN2_TX_Handler_Standin(void) __attribute__((used));
void DCMI_Handler_Standin(void) __attribute__((used));
void DMA1_Stream0_Handler_Standin(void) __attribute__((used));
void DMA1_Stream1_Handler_Standin(void) __attribute__((used));
void DMA1_Stream2_Handler_Standin(void) __attribute__((used));
void DMA1_Stream3_Handler_Standin(void) __attribute__((used));
void DMA1_Stream4_Handler_Standin(void) __attribute__((used));
void DMA1_Stream5_Handler_Standin(void) __attribute__((used));
void DMA1_Stream6_Handler_Standin(void) __attribute__((used));
void DMA1_Stream7_Handler_Standin(void) __attribute__((used));
void DMA2_Stream0_Handler_Standin(void) __attribute__((used));
void DMA2_Stream1_Handler_Standin(void) __attribute__((used));
void DMA2_Stream2_Handler_Standin(void) __attribute__((used));
void DMA2_Stream3_Handler_Standin(void) __attribute__((used));
void DMA2_Stream4_Handler_Standin(void) __attribute__((used));
void DMA2_Stream5_Handler_Standin(void) __attribute__((used));
void DMA2_Stream6_Handler_Standin(void) __attribute__((used));
void DMA2_Stream7_Handler_Standin(void) __attribute__((used));
void DebugMon_Handler_Standin(void) __attribute__((used));
void ETH_Handler_Standin(void) __attribute__((used));
void ETH_WKUP_Handler_Standin(void) __attribute__((used));
void EXTI0_Handler_Standin(void) __attribute__((used));
void EXTI15_10_Handler_Standin(void) __attribute__((used));
void EXTI1_Handler_Standin(void) __attribute__((used));
void EXTI2_Handler_Standin(void) __attribute__((used));
void EXTI3_Handler_Standin(void) __attribute__((used));
void EXTI4_Handler_Standin(void) __attribute__((used));
void EXTI9_5_Handler_Standin(void) __attribute__((used));
void FLASH_Handler_Standin(void) __attribute__((used));
void FMC_Handler_Standin(void) __attribute__((used));
void FPU_Handler_Standin(void) __attribute__((used));
void HASH_RNG_Handler_Standin(void) __attribute__((used));
void HardFault_Handler_Standin(void) __attribute__((used));
void I2C1_ER_Handler_Standin(void) __attribute__((used));
void I2C1_EV_Handler_Standin(void) __attribute__((used));
void I2C2_ER_Handler_Standin(void) __attribute__((used));
void I2C2_EV_Handler_Standin(void) __attribute__((used));
void I2C3_ER_Handler_Standin(void) __attribute__((used));
void I2C3_EV_Handler_Standin(void) __attribute__((used));
void MemManage_Handler_Standin(void) __attribute__((used));
void NMI_Handler_Standin(void) __attribute__((used));
void OTG_FS_Handler_Standin(void) __attribute__((used));
void OTG_FS_WKUP_Handler_Standin(void) __attribute__((used));
void OTG_HS_EP1_IN_Handler_Standin(void) __attribute__((used));
void OTG_HS_EP1_OUT_Handler_Standin(void) __attribute__((used));
void OTG_HS_Handler_Standin(void) __attribute__((used));
void OTG_HS_WKUP_Handler_Standin(void) __attribute__((used));
void PVD_Handler_Standin(void) __attribute__((used));
void PendSV_Handler_Standin(void) __attribute__((used));
void RCC_Handler_Standin(void) __attribute__((used));
void RTC_Alarm_Handler_Standin(void) __attribute__((used));
void RTC_WKUP_Handler_Standin(void) __attribute__((used));
void Reset_Handler_Standin(void) __attribute__((used));
void SDIO_Handler_Standin(void) __attribute__((used));
void SPI1_Handler_Standin(void) __attribute__((used));
void SPI2_Handler_Standin(void) __attribute__((used));
void SPI3_Handler_Standin(void) __attribute__((used));
void SVC_Handler_Standin(void) __attribute__((used));
void SysTick_Handler_Standin(void) __attribute__((used));
void TAMP_STAMP_Handler_Standin(void) __attribute__((used));
void TIM1_BRK_TIM9_Handler_Standin(void) __attribute__((used));
void TIM1_CC_Handler_Standin(void) __attribute__((used));
void TIM1_TRG_COM_TIM11_Handler_Standin(void) __attribute__((used));
void TIM1_UP_TIM10_Handler_Standin(void) __attribute__((used));
void TIM2_Handler_Standin(void) __attribute__((used));
void TIM3_Handler_Standin(void) __attribute__((used));
void TIM4_Handler_Standin(void) __attribute__((used));
void TIM5_Handler_Standin(void) __attribute__((used));
void TIM6_DAC_Handler_Standin(void) __attribute__((used));
void TIM7_Handler_Standin(void) __attribute__((used));
void TIM8_BRK_TIM12_Handler_Standin(void) __attribute__((used));
void TIM8_CC_Handler_Standin(void) __attribute__((used));
void TIM8_TRG_COM_TIM14_Handler_Standin(void) __attribute__((used));
void TIM8_UP_TIM13_Handler_Standin(void) __attribute__((used));
void UART4_Handler_Standin(void) __attribute__((used));
void UART5_Handler_Standin(void) __attribute__((used));
void USART1_Handler_Standin(void) __attribute__((used));
void USART2_Handler_Standin(void) __attribute__((used));
void USART3_Handler_Standin(void) __attribute__((used));
void USART6_Handler_Standin(void) __attribute__((used));
void UsageFault_Handler_Standin(void) __attribute__((used));
void WWDG_Handler_Standin(void) __attribute__((used));

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
