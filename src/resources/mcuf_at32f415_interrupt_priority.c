/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "core/arterytek/at32f415/bsp/at32f4xx.h"
#include "core/arterytek/at32f415/bsp/core_cm4.h"

/* ****************************************************************************************
 * Macro
 */
 
/* ****************************************************************************************
 * Type/Structure
 */ 
typedef struct _nvic_priority_level_t{
  IRQn_Type irq;
  uint8_t priority;
}nvic_priority_level_t;

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Public
 */

/* ****************************************************************************************
 * Private
 */
const nvic_priority_level_t nvic_priority_level[] = {
  {WWDG_IRQn,               15},
  {PVD_IRQn,                15},
  {TAMP_STAMP_IRQn,         15},
  {ERTC_WKUP_IRQn,          15},
  {FLASH_IRQn,              15},
  {RCC_IRQn,                15},
  {EXTI0_IRQn,              15},
  {EXTI1_IRQn,              15},
  {EXTI2_IRQn,              15},
  {EXTI3_IRQn,              15},
  {EXTI4_IRQn,              15},
  {DMA1_Channel1_IRQn,      15},
  {DMA1_Channel2_IRQn,      15},
  {DMA1_Channel3_IRQn,      15},
  {DMA1_Channel4_IRQn,      15},
  {DMA1_Channel5_IRQn,      15},
  {DMA1_Channel6_IRQn,      15},
  {DMA1_Channel7_IRQn,      15},
  {ADC1_2_IRQn,             15},
  {CAN1_TX_IRQn,            15},
  {CAN1_RX0_IRQn,           15},
  {CAN1_RX1_IRQn,           15},
  {CAN1_SCE_IRQn,           15},
  {EXTI9_5_IRQn,            15},
  {TMR1_BRK_TMR9_IRQn,      15},
  {TMR1_OV_TMR10_IRQn,      15},
  {TMR1_TRG_COM_TMR11_IRQn, 15},
  {TMR1_CC_IRQn,            15},
  {TMR2_GLOBAL_IRQn,        15},
  {TMR3_GLOBAL_IRQn,        15},
  {TMR4_GLOBAL_IRQn,        15},
  {I2C1_EV_IRQn,            15},
  {I2C1_ER_IRQn,            15},
  {I2C2_EV_IRQn,            15},
  {I2C2_ER_IRQn,            15},
  {SPI1_IRQn,               15},
  {SPI2_IRQn,               15},
  {USART1_IRQn,             15},
  {USART2_IRQn,             15},
  {USART3_IRQn,             15},
  {EXTI15_10_IRQn,          15},
  {ERTCAlarm_IRQn,          15},
  {USBWakeUp_IRQn,          15},
  {SDIO_IRQn,               15},
  {TMR5_GLOBAL_IRQn,        15},
  {UART4_IRQn,              15},
  {UART5_IRQn,              15},
  {DMA2_Channel1_IRQn,      15},
  {DMA2_Channel2_IRQn,      15},
  {DMA2_Channel3_IRQn,      15},
  {DMA2_Channel4_5_IRQn,    15},
  {USBOTG_IRQn,             15},
  {COMP1_IRQn,              15},
  {COMP2_IRQn,              15},
  {ACC_IRQn,                15},
  {DMA2_Channel6_7_IRQn,    15},
};
/* ****************************************************************************************
 * Inline Function
 */
 
/* ****************************************************************************************
 * Private Function
 */ 
 
/* ****************************************************************************************
 * Public Function
 */

/**
 *
 */
void mcuf_at32f415_interrupt_priority(void){
	int i;
	int count = (sizeof(nvic_priority_level) / sizeof(nvic_priority_level_t));
	
	for(i=0; i<count; i++){
		NVIC_SetPriority(nvic_priority_level[i].irq, nvic_priority_level[i].priority);
	}
}

/* *****************************************************************************************
 *    End of file
 */
