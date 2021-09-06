/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"
#include "CtrlInterrupt.hpp"
#include "bsp_arterytek_at32f415/at32f4xx.h"
 
/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::ctrl::CtrlInterrupt;

/* ****************************************************************************************
 * Macro
 */
#define IRQ_CTRL(irq, enable) ((enable)?NVIC_EnableIRQ(irq):NVIC_DisableIRQ(irq))
#define IRQ_FLAG(source, shift, enable) ((enable)?(source |= (1 << shift)):(source &= (~(1 << shift))))

/* ****************************************************************************************
 * Variable
 */
uint8_t CtrlInterrupt::ioint_flag9_5 = 0;
uint8_t CtrlInterrupt::ioint_flag15_10 = 0;

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/**
 * 
 */
void CtrlInterrupt::ioint(IrqIOINT irq, bool enable){
  switch(irq){
    case IRQ_IOINT0:
      
      IRQ_CTRL(EXTI0_IRQn, enable);
      return;
    case IRQ_IOINT1:
      
      IRQ_CTRL(EXTI1_IRQn, enable);
      return;
    case IRQ_IOINT2:
      
      IRQ_CTRL(EXTI2_IRQn, enable);
      return;
    case IRQ_IOINT3:
      
      IRQ_CTRL(EXTI3_IRQn, enable);
      return;
    case IRQ_IOINT4:
      
      IRQ_CTRL(EXTI4_IRQn, enable);
      return;
    case IRQ_IOINT5:
      
      IRQ_FLAG(ioint_flag9_5, 0, enable);
      IRQ_CTRL(EXTI9_5_IRQn, ioint_flag9_5);
      return;
    case IRQ_IOINT6:
      
      IRQ_FLAG(ioint_flag9_5, 1, enable);
      IRQ_CTRL(EXTI9_5_IRQn, ioint_flag9_5);
      return;
    case IRQ_IOINT7:
      
      IRQ_FLAG(ioint_flag9_5, 2, enable);
      IRQ_CTRL(EXTI9_5_IRQn, ioint_flag9_5);
      return;
    case IRQ_IOINT8:
      
      IRQ_FLAG(ioint_flag9_5, 3, enable);
      IRQ_CTRL(EXTI9_5_IRQn, ioint_flag9_5);
      return;
    case IRQ_IOINT9:
      
      IRQ_FLAG(ioint_flag9_5, 4, enable);
      IRQ_CTRL(EXTI9_5_IRQn, ioint_flag9_5);
      return;
    case IRQ_IOINT10:
      
      IRQ_FLAG(ioint_flag15_10, 0, enable);
      IRQ_CTRL(EXTI15_10_IRQn, ioint_flag15_10);
      return;
    case IRQ_IOINT11:
      
      IRQ_FLAG(ioint_flag15_10, 1, enable);
      IRQ_CTRL(EXTI15_10_IRQn, ioint_flag15_10);
      return;
    case IRQ_IOINT12:
      
      IRQ_FLAG(ioint_flag15_10, 2, enable);
      IRQ_CTRL(EXTI15_10_IRQn, ioint_flag15_10);
      return;
    case IRQ_IOINT13:
      
      IRQ_FLAG(ioint_flag15_10, 3, enable);
      IRQ_CTRL(EXTI15_10_IRQn, ioint_flag15_10);
      return;
    case IRQ_IOINT14:
      
      IRQ_FLAG(ioint_flag15_10, 4, enable);
      IRQ_CTRL(EXTI15_10_IRQn, ioint_flag15_10);
      return;
    
    case IRQ_IOINT15:
      IRQ_FLAG(ioint_flag15_10, 5, enable);
      IRQ_CTRL(EXTI15_10_IRQn, ioint_flag15_10);
      return;
    
    default:
      THROW_ERROR("out of enum index");
  }
}

/**
 * 
 */
void CtrlInterrupt::spi(IrqSPI irq, bool enable){
  switch(irq){
    case IRQ_SPI1:
      IRQ_CTRL(SPI1_IRQn, enable);
      return;
    case IRQ_SPI2:
      IRQ_CTRL(SPI2_IRQn, enable);
      return;
    
    default:
      THROW_ERROR("out of enum index");
  }
}

/**
 * 
 */
void CtrlInterrupt::timer(IrqTIMER irq, bool enable){
  switch(irq){
    case IRQ_TMR2:                      //TMR2
      IRQ_CTRL(TMR2_GLOBAL_IRQn, enable);
      return;
    
    case IRQ_TMR3:                      //TMR3
      IRQ_CTRL(TMR3_GLOBAL_IRQn, enable);
      return;
    
    case IRQ_TMR4:                      //TMR4
      IRQ_CTRL(TMR4_GLOBAL_IRQn, enable);
      return;
    
    case IRQ_TMR5:                      //TMR5
      IRQ_CTRL(TMR5_GLOBAL_IRQn, enable);
      return;
    
    case IRQ_TMR9:                      //TMR9
      IRQ_CTRL(TMR1_BRK_TMR9_IRQn, enable);
      return;
    
    case IRQ_TMR10:                      //TMR10
      IRQ_CTRL(TMR1_OV_TMR10_IRQn, enable);
      return;
    
    case IRQ_TMR11:                      //TMR11
      IRQ_CTRL(TMR1_TRG_COM_TMR11_IRQn, enable);
      return;
    
    default:
      THROW_ERROR("out of enum index");
  }
}

/**
 * 
 */
void CtrlInterrupt::usart(IrqUSART irq , bool enable){
	switch(irq){
		case IRQ_USART1:                      //USART1
			IRQ_CTRL(USART1_IRQn, enable);
		  return;
    
		case IRQ_USART2:                      //USART2
			IRQ_CTRL(USART2_IRQn, enable);
		  return;
    
		case IRQ_USART3:                      //USART3
			IRQ_CTRL(USART3_IRQn, enable);
		  return;
    
		case IRQ_UART4:                      //UART4
			IRQ_CTRL(UART4_IRQn, enable);
		  return;
    
		case IRQ_UART5:                      //UART5
			IRQ_CTRL(UART5_IRQn, enable);
			return;
    
    default:
      THROW_ERROR("out of enum index");
	}
}


/* ****************************************************************************************
 * Public Method <Override>
 */

/* ****************************************************************************************
 * Public Method
 */

/* ****************************************************************************************
 * Protected Method <Static>
 */
 
/* ****************************************************************************************
 * Protected Method <Override>
 */ 

/* ****************************************************************************************
 * Protected Method
 */

/* ****************************************************************************************
 * Private Method
 */
 
/* ****************************************************************************************
 * End of file
 */ 
