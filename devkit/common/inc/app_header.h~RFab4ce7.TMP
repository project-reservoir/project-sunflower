#ifndef __APP_HEADER_H
#define __APP_HEADER_H

#include "stm32f4xx.h"

#define SRAM_START			0x20000000
#define FLASH_START			0x08000000
#define MAIN_APP_START		0x08000800
#define BACKUP_APP_START    0x08008400

typedef struct APP_HEADER_T {
	uint32_t crc32;
	uint32_t crc32_start_mark;
	uint32_t version;
	uint32_t entry_point;
	uint32_t ro_size;
	uint32_t rw_size;
    
    uint32_t initial_sp;
    
    // Note: these are sorted alphabetically (rather than in vector table order) 
    // due to a quirk of the linker.
    
    uint32_t     ADC_Handler;                    // ADC1, ADC2 and ADC3s                            
    uint32_t     BusFault_Handler;           	 // Bus Fault Handler
    uint32_t     CAN1_RX0_Handler;               // CAN1 RX0                                               
    uint32_t     CAN1_RX1_Handler;               // CAN1 RX1                                               
    uint32_t     CAN1_SCE_Handler;               // CAN1 SCE                                               
    uint32_t     CAN1_TX_Handler;                // CAN1 TX                                                
    uint32_t     CAN2_RX0_Handler;               // CAN2 RX0                                               
    uint32_t     CAN2_RX1_Handler;               // CAN2 RX1                                               
    uint32_t     CAN2_SCE_Handler;               // CAN2 SCE                                               
    uint32_t     CAN2_TX_Handler;                // CAN2 TX                                                
    uint32_t     DCMI_Handler;                   // DCMI  			                              
    uint32_t     DMA1_Stream0_Handler;           // DMA1 Stream 0                                   
    uint32_t     DMA1_Stream1_Handler;           // DMA1 Stream 1                                   
    uint32_t     DMA1_Stream2_Handler;           // DMA1 Stream 2                                   
    uint32_t     DMA1_Stream3_Handler;           // DMA1 Stream 3                                   
    uint32_t     DMA1_Stream4_Handler;           // DMA1 Stream 4                                   
    uint32_t     DMA1_Stream5_Handler;           // DMA1 Stream 5                                   
    uint32_t     DMA1_Stream6_Handler;           // DMA1 Stream 6                                   
    uint32_t     DMA1_Stream7_Handler;           // DMA1 Stream7                                           
    uint32_t     DMA2_Stream0_Handler;           // DMA2 Stream 0                                   
    uint32_t     DMA2_Stream1_Handler;           // DMA2 Stream 1                                   
    uint32_t     DMA2_Stream2_Handler;           // DMA2 Stream 2                                   
    uint32_t     DMA2_Stream3_Handler;           // DMA2 Stream 3                                   
    uint32_t     DMA2_Stream4_Handler;           // DMA2 Stream 4                                   
    uint32_t     DMA2_Stream5_Handler;           // DMA2 Stream 5                                   
    uint32_t     DMA2_Stream6_Handler;           // DMA2 Stream 6                                   
    uint32_t     DMA2_Stream7_Handler;           // DMA2 Stream 7                                   
    uint32_t     DebugMon_Handler;           		// Debug Monitor Handler
    uint32_t     ETH_Handler;                    // Ethernet                                        
    uint32_t     ETH_WKUP_Handler;               // Ethernet Wakeup through EXTI line                      
    uint32_t     EXTI0_Handler;                  // EXTI Line0                                             
    uint32_t     EXTI15_10_Handler;              // External Line[15:10]s                                  
    uint32_t     EXTI1_Handler;                  // EXTI Line1                                             
    uint32_t     EXTI2_Handler;                  // EXTI Line2                                             
    uint32_t     EXTI3_Handler;                  // EXTI Line3                                             
    uint32_t     EXTI4_Handler;                  // EXTI Line4                                             
    uint32_t     EXTI9_5_Handler;                // External Line[9:5]s                                    
    uint32_t     FLASH_Handler;                  // FLASH                                           
    uint32_t     FMC_Handler;                    // FMC                                             
    uint32_t     FPU_Handler;                    // FPU
    uint32_t     HASH_RNG_Handler;               // Hash and Rng
    uint32_t     HardFault_Handler;          		// Hard Fault Handler
    uint32_t     I2C1_ER_Handler;                // I2C1 Error                                             
    uint32_t     I2C1_EV_Handler;                // I2C1 Event                                             
    uint32_t     I2C2_ER_Handler;                // I2C2 Error                                               
    uint32_t     I2C2_EV_Handler;                // I2C2 Event                                             
    uint32_t     I2C3_ER_Handler;                // I2C3 error                                             
    uint32_t     I2C3_EV_Handler;                // I2C3 event                                             
    uint32_t     MemManage_Handler;         		// MPU Fault Handler
    uint32_t     NMI_Handler;                		// NMI Handler
    uint32_t     OTG_FS_Handler;                 // USB OTG FS                                      
    uint32_t     OTG_FS_WKUP_Handler;            // USB OTG FS Wakeup through EXTI line                        
    uint32_t     OTG_HS_EP1_IN_Handler;          // USB OTG HS End Point 1 In                       
    uint32_t     OTG_HS_EP1_OUT_Handler;         // USB OTG HS End Point 1 Out                      
    uint32_t     OTG_HS_Handler;                 // USB OTG HS                                      
    uint32_t     OTG_HS_WKUP_Handler;            // USB OTG HS Wakeup through EXTI                         
    uint32_t     PVD_Handler;                    // PVD through EXTI Line detection                        
    uint32_t     PendSV_Handler;            		// PendSV Handler
    uint32_t     RCC_Handler;                    // RCC                                             
    uint32_t     RTC_Alarm_Handler;              // RTC Alarm (A and B) through EXTI Line                  
    uint32_t     RTC_WKUP_Handler;               // RTC Wakeup through the EXTI line                       
    uint32_t     Reset_Handler;            		  	// Reset Handler
    uint32_t     SDIO_Handler;                   // SDIO                                            
    uint32_t     SPI1_Handler;                   // SPI1                                            
    uint32_t     SPI2_Handler;                   // SPI2                                            
    uint32_t     SPI3_Handler;                   // SPI3                                            
    uint32_t     SVC_Handler;                		// SVCall Handler
    uint32_t     SysTick_Handler;            		// SysTick Handler
    uint32_t     TAMP_STAMP_Handler;             // Tamper and TimeStamps through the EXTI line            
    uint32_t     TIM1_BRK_TIM9_Handler;          // TIM1 Break and TIM9                   
    uint32_t     TIM1_CC_Handler;                // TIM1 Capture Compare                                   
    uint32_t     TIM1_TRG_COM_TIM11_Handler;     // TIM1 Trigger and Commutation and TIM11
    uint32_t     TIM1_UP_TIM10_Handler;          // TIM1 Update and TIM10                 
    uint32_t     TIM2_Handler;                   // TIM2                                            
    uint32_t     TIM3_Handler;                   // TIM3                                            
    uint32_t     TIM4_Handler;                   // TIM4                                            
    uint32_t     TIM5_Handler;                   // TIM5                                            
    uint32_t     TIM6_DAC_Handler;               // TIM6 and DAC1&2 underrun errors                   
    uint32_t     TIM7_Handler;                   // TIM7                   
    uint32_t     TIM8_BRK_TIM12_Handler;         // TIM8 Break and TIM12                  
    uint32_t     TIM8_CC_Handler;                // TIM8 Capture Compare                                   
    uint32_t     TIM8_TRG_COM_TIM14_Handler;     // TIM8 Trigger and Commutation and TIM14
    uint32_t     TIM8_UP_TIM13_Handler;          // TIM8 Update and TIM13                 
    uint32_t     UART4_Handler;                  // UART4                                           
    uint32_t     UART5_Handler;                  // UART5                                           
    uint32_t     USART1_Handler;                 // USART1                                          
    uint32_t     USART2_Handler;                 // USART2                                          
    uint32_t     USART3_Handler;                 // USART3                                          
    uint32_t     USART6_Handler;                 // USART6                                           
    uint32_t     UsageFault_Handler;         		// Usage Fault Handler
    uint32_t     WWDG_Handler;                   // Window WatchDog
    
} APP_HEADER;

typedef struct NVIC_BLOCK_T {
	uint32_t     eram;                       		// Top of Stack
	uint32_t     Reset_Handler;              		// Reset Handler
	uint32_t     NMI_Handler;                		// NMI Handler
	uint32_t     HardFault_Handler;        		  // Hard Fault Handler
	uint32_t     MemManage_Handler;         		// MPU Fault Handler
	uint32_t     BusFault_Handler;         		  // Bus Fault Handler
	uint32_t     UsageFault_Handler;      		  // Usage Fault Handler
	
	uint32_t     reserved_1;              		  // Reserved
	uint32_t     reserved_2;                		// Reserved
	uint32_t     reserved_3;                 		// Reserved
	uint32_t     reserved_4;                		// Reserved
	
	uint32_t     SVC_Handler;                   // SVCall Handler
	uint32_t     DebugMon_Handler;           		// Debug Monitor Handler
	
	uint32_t     reserved_5;                 		// Reserved
	
	uint32_t     PendSV_Handler;            		// PendSV Handler
	uint32_t     SysTick_Handler;           		// SysTick Handler

	// External Interrupts
	uint32_t     WWDG_Handler;                   // Window WatchDog
	uint32_t     PVD_Handler;                    // PVD through EXTI Line detection                        
	uint32_t     TAMP_STAMP_Handler;             // Tamper and TimeStamps through the EXTI line            
	uint32_t     RTC_WKUP_Handler;               // RTC Wakeup through the EXTI line                       
	uint32_t     FLASH_Handler;                  // FLASH                                           
	uint32_t     RCC_Handler;                    // RCC                                             
	uint32_t     EXTI0_Handler;                  // EXTI Line0                                             
	uint32_t     EXTI1_Handler;                  // EXTI Line1                                             
	uint32_t     EXTI2_Handler;                  // EXTI Line2                                             
	uint32_t     EXTI3_Handler;                  // EXTI Line3                                             
	uint32_t     EXTI4_Handler;                  // EXTI Line4                                             
	uint32_t     DMA1_Stream0_Handler;           // DMA1 Stream 0                                   
	uint32_t     DMA1_Stream1_Handler;           // DMA1 Stream 1                                   
	uint32_t     DMA1_Stream2_Handler;           // DMA1 Stream 2                                   
	uint32_t     DMA1_Stream3_Handler;           // DMA1 Stream 3                                   
	uint32_t     DMA1_Stream4_Handler;           // DMA1 Stream 4                                   
	uint32_t     DMA1_Stream5_Handler;           // DMA1 Stream 5                                   
	uint32_t     DMA1_Stream6_Handler;           // DMA1 Stream 6                                   
	uint32_t     ADC_Handler;                    // ADC1, ADC2 and ADC3s                            
	uint32_t     CAN1_TX_Handler;                // CAN1 TX                                                
	uint32_t     CAN1_RX0_Handler;               // CAN1 RX0                                               
	uint32_t     CAN1_RX1_Handler;               // CAN1 RX1                                               
	uint32_t     CAN1_SCE_Handler;               // CAN1 SCE                                               
	uint32_t     EXTI9_5_Handler;                // External Line[9:5]s                                    
	uint32_t     TIM1_BRK_TIM9_Handler;          // TIM1 Break and TIM9                   
	uint32_t     TIM1_UP_TIM10_Handler;          // TIM1 Update and TIM10                 
	uint32_t     TIM1_TRG_COM_TIM11_Handler;     // TIM1 Trigger and Commutation and TIM11
	uint32_t     TIM1_CC_Handler;                // TIM1 Capture Compare                                   
	uint32_t     TIM2_Handler;                   // TIM2                                            
	uint32_t     TIM3_Handler;                   // TIM3                                            
	uint32_t     TIM4_Handler;                   // TIM4                                            
	uint32_t     I2C1_EV_Handler;                // I2C1 Event                                             
	uint32_t     I2C1_ER_Handler;                // I2C1 Error                                             
	uint32_t     I2C2_EV_Handler;                // I2C2 Event                                             
	uint32_t     I2C2_ER_Handler;                // I2C2 Error                                               
	uint32_t     SPI1_Handler;                   // SPI1                                            
	uint32_t     SPI2_Handler;                   // SPI2                                            
	uint32_t     USART1_Handler;                 // USART1                                          
	uint32_t     USART2_Handler;                 // USART2                                          
	uint32_t     USART3_Handler;                 // USART3                                          
	uint32_t     EXTI15_10_Handler;              // External Line[15:10]s                                  
	uint32_t     RTC_Alarm_Handler;              // RTC Alarm (A and B) through EXTI Line                  
	uint32_t     OTG_FS_WKUP_Handler;            // USB OTG FS Wakeup through EXTI line                        
	uint32_t     TIM8_BRK_TIM12_Handler;         // TIM8 Break and TIM12                  
	uint32_t     TIM8_UP_TIM13_Handler;          // TIM8 Update and TIM13                 
	uint32_t     TIM8_TRG_COM_TIM14_Handler;     // TIM8 Trigger and Commutation and TIM14
	uint32_t     TIM8_CC_Handler;                // TIM8 Capture Compare                                   
	uint32_t     DMA1_Stream7_Handler;           // DMA1 Stream7                                           
	uint32_t     FMC_Handler;                    // FMC                                             
	uint32_t     SDIO_Handler;                   // SDIO                                            
	uint32_t     TIM5_Handler;                   // TIM5                                            
	uint32_t     SPI3_Handler;                   // SPI3                                            
	uint32_t     UART4_Handler;                  // UART4                                           
	uint32_t     UART5_Handler;                  // UART5                                           
	uint32_t     TIM6_DAC_Handler;               // TIM6 and DAC1&2 underrun errors                   
	uint32_t     TIM7_Handler;                   // TIM7                   
	uint32_t     DMA2_Stream0_Handler;           // DMA2 Stream 0                                   
	uint32_t     DMA2_Stream1_Handler;           // DMA2 Stream 1                                   
	uint32_t     DMA2_Stream2_Handler;           // DMA2 Stream 2                                   
	uint32_t     DMA2_Stream3_Handler;           // DMA2 Stream 3                                   
	uint32_t     DMA2_Stream4_Handler;           // DMA2 Stream 4                                   
	uint32_t     ETH_Handler;                    // Ethernet                                        
	uint32_t     ETH_WKUP_Handler;               // Ethernet Wakeup through EXTI line                      
	uint32_t     CAN2_TX_Handler;                // CAN2 TX                                                
	uint32_t     CAN2_RX0_Handler;               // CAN2 RX0                                               
	uint32_t     CAN2_RX1_Handler;               // CAN2 RX1                                               
	uint32_t     CAN2_SCE_Handler;               // CAN2 SCE                                               
	uint32_t     OTG_FS_Handler;                 // USB OTG FS                                      
	uint32_t     DMA2_Stream5_Handler;           // DMA2 Stream 5                                   
	uint32_t     DMA2_Stream6_Handler;           // DMA2 Stream 6                                   
	uint32_t     DMA2_Stream7_Handler;           // DMA2 Stream 7                                   
	uint32_t     USART6_Handler;                 // USART6                                           
	uint32_t     I2C3_EV_Handler;                // I2C3 event                                             
	uint32_t     I2C3_ER_Handler;                // I2C3 error                                             
	uint32_t     OTG_HS_EP1_OUT_Handler;         // USB OTG HS End Point 1 Out                      
	uint32_t     OTG_HS_EP1_IN_Handler;          // USB OTG HS End Point 1 In                       
	uint32_t     OTG_HS_WKUP_Handler;            // USB OTG HS Wakeup through EXTI                         
	uint32_t     OTG_HS_Handler;                 // USB OTG HS                                      
	uint32_t     DCMI_Handler;                   // DCMI  
	uint32_t     reserved_6;                     // Reserved				                              
	uint32_t     HASH_RNG_Handler;               // Hash and Rng
	uint32_t     FPU_Handler;                    // FPU
} NVIC_BLOCK;

#endif // __APP_HEADER_H
