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

#include "bsp_arterytek_at32f415/at32f4xx.h"
#include "core/arterytek/at32f415/CoreInterrupt.hpp"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      struct CoreInterruptConfig{
        IRQn irq[CoreInterrupt::IRQ_MAX_QUANTITY];
        
      }const coreInterruptConfig = {
        .irq = {
         /*  IRQ_ADC           = 0,  */   ADC1_2_IRQn,
         /*  IRQ_COMP1         = 1,  */   COMP1_IRQn,
         /*  IRQ_COMP2         = 2,  */   COMP2_IRQn,
         /*  IRQ_DMA1_1        = 3,  */   DMA1_Channel1_IRQn,
         /*  IRQ_DMA1_2        = 4,  */   DMA1_Channel2_IRQn,
         /*  IRQ_DMA1_3        = 5,  */   DMA1_Channel3_IRQn,
         /*  IRQ_DMA1_4        = 6,  */   DMA1_Channel4_IRQn,
         /*  IRQ_DMA1_5        = 7,  */   DMA1_Channel5_IRQn,
         /*  IRQ_DMA1_6        = 8,  */   DMA1_Channel6_IRQn,
         /*  IRQ_DMA1_7        = 9,  */   DMA1_Channel7_IRQn,
         /*  IRQ_DMA2_1        = 10, */   DMA2_Channel1_IRQn,
         /*  IRQ_DMA2_2        = 11, */   DMA2_Channel2_IRQn,
         /*  IRQ_DMA2_3        = 12, */   DMA2_Channel3_IRQn,
         /*  IRQ_DMA2_4        = 13, */   DMA2_Channel4_5_IRQn,
         /*  IRQ_DMA2_5        = 14, */   DMA2_Channel4_5_IRQn,
         /*  IRQ_DMA2_6        = 15, */   DMA2_Channel6_7_IRQn,
         /*  IRQ_DMA2_7        = 16, */   DMA2_Channel6_7_IRQn,
         /*  IRQ_ERTC_WKUP     = 17, */   ERTC_WKUP_IRQn,
         /*  IRQ_EXTI0         = 18, */   EXTI0_IRQn,
         /*  IRQ_EXTI1         = 19, */   EXTI1_IRQn,
         /*  IRQ_EXTI2         = 20, */   EXTI2_IRQn,
         /*  IRQ_EXTI3         = 21, */   EXTI3_IRQn,
         /*  IRQ_EXTI4         = 22, */   EXTI4_IRQn,
         /*  IRQ_EXTI5         = 23, */   EXTI9_5_IRQn,
         /*  IRQ_EXTI6         = 24, */   EXTI9_5_IRQn,
         /*  IRQ_EXTI7         = 25, */   EXTI9_5_IRQn,
         /*  IRQ_EXTI8         = 26, */   EXTI9_5_IRQn,
         /*  IRQ_EXTI9         = 27, */   EXTI9_5_IRQn,
         /*  IRQ_EXTI10        = 28, */   EXTI15_10_IRQn,
         /*  IRQ_EXTI11        = 29, */   EXTI15_10_IRQn,
         /*  IRQ_EXTI12        = 30, */   EXTI15_10_IRQn,
         /*  IRQ_EXTI13        = 31, */   EXTI15_10_IRQn,
         /*  IRQ_EXTI14        = 32, */   EXTI15_10_IRQn,
         /*  IRQ_EXTI15        = 33, */   EXTI15_10_IRQn,
         /*  IRQ_FLASH         = 34, */   FLASH_IRQn,
         /*  IRQ_I2C1_ER       = 35, */   I2C1_ER_IRQn,
         /*  IRQ_I2C1_EV       = 36, */   I2C1_EV_IRQn,
         /*  IRQ_I2C2_ER       = 37, */   I2C2_ER_IRQn,
         /*  IRQ_I2C2_EV       = 38, */   I2C2_EV_IRQn,
         /*  IRQ_RCC           = 39, */   RCC_IRQn,
         /*  IRQ_SDIO          = 40, */   SDIO_IRQn,
         /*  IRQ_SPI1          = 41, */   SPI1_IRQn,
         /*  IRQ_SPI2          = 42, */   SPI2_IRQn,
         /*  IRQ_TMR1          = 43, */   TMR1_OV_TMR10_IRQn,
         /*  IRQ_TMR1_BRK      = 44, */   TMR1_BRK_TMR9_IRQn,
         /*  IRQ_TMR1_TRG_COM  = 45, */   TMR1_TRG_COM_TMR11_IRQn,
         /*  IRQ_TMR1_CC       = 46, */   TMR1_CC_IRQn,
         /*  IRQ_TMR2          = 47, */   TMR2_GLOBAL_IRQn,
         /*  IRQ_TMR3          = 48, */   TMR3_GLOBAL_IRQn,
         /*  IRQ_TMR4          = 49, */   TMR4_GLOBAL_IRQn,
         /*  IRQ_TMR5          = 50, */   TMR5_GLOBAL_IRQn,
         /*  IRQ_TMR9          = 51, */   TMR1_BRK_TMR9_IRQn,
         /*  IRQ_TMR10         = 52, */   TMR1_OV_TMR10_IRQn,
         /*  IRQ_TMR11         = 53, */   TMR1_TRG_COM_TMR11_IRQn,
         /*  IRQ_USBOTG        = 54, */   USBOTG_IRQn,
         /*  IRQ_WWDG          = 55, */   WWDG_IRQn,
         /*  IRQ_PVD           = 56, */   PVD_IRQn,
         /*  IRQ_TAMP_STAMP    = 57, */   TAMP_STAMP_IRQn,
         /*  IRQ_USART1        = 58, */   USART1_IRQn,
         /*  IRQ_USART2        = 59, */   USART2_IRQn,
         /*  IRQ_USART3        = 60, */   USART3_IRQn,
         /*  IRQ_UART4         = 61, */   UART4_IRQn,
         /*  IRQ_UART5         = 62, */   UART5_IRQn,

        },
      };
    }
  }
}


/* ****************************************************************************************
 * Using
 */  
using mcuf::function::Runnable;
using core::arterytek::at32f415::CoreInterrupt;

/* ****************************************************************************************
 * Macro
 */  

#define CONFIG coreInterruptConfig

#define IRQ_CTRL(irq, enable) ((enable)?NVIC_EnableIRQ(irq):NVIC_DisableIRQ(irq))
#define IRQ_FLAG(source, shift, enable) ((enable)?(source |= (1 << shift)):(source &= (~(1 << shift))))

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override>
 */

/**
 *
 */
void CoreInterrupt::run(void){
  return;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreInterrupt::setHandler(Irq irq, mcuf::function::Runnable* runnable){
  if(!runnable)
    runnable = this;
  
  switch(irq){
    //-------------------------------------------------------------------------------------
    case IRQ_TMR1:
      this->mHandle[IRQ_TMR1] = runnable;
      this->mHandle[IRQ_TMR1_BRK] = runnable;
      this->mHandle[IRQ_TMR1_TRG_COM] = runnable;
      this->mHandle[IRQ_TMR1_CC] = runnable;
      break;
    
    //-------------------------------------------------------------------------------------
    default:
      this->mHandle[irq] = runnable;
      break;
  }
}

/**
 *
 */
void CoreInterrupt::irqHandler(Irq irq, bool enable){
  uint8_t* flag;
  uint8_t shift;
  
  switch(irq){
    //-------------------------------------------------------------------------------------
    case IRQ_TMR1:
      IRQ_FLAG(this->mFlag[FLAG_TMR1_BRK_TMR9], 0, enable);
      IRQ_CTRL(TMR1_BRK_TMR9_IRQn, this->mFlag[FLAG_TMR1_BRK_TMR9]);
    
      IRQ_FLAG(this->mFlag[FLAG_TMR1_TRG_COM_TMR11], 0, enable);
      IRQ_CTRL(TMR1_TRG_COM_TMR11_IRQn, this->mFlag[FLAG_TMR1_TRG_COM_TMR11]);
    
      IRQ_CTRL(TMR1_CC_IRQn, enable);
      
      flag = &this->mFlag[FLAG_TMR1_OV_TMR10];
      shift = 0;
      break;
    
    //-------------------------------------------------------------------------------------
    case IRQ_TMR9:
      flag = &this->mFlag[FLAG_TMR1_BRK_TMR9];
      shift = 1;
      break;
    
    //-------------------------------------------------------------------------------------
    case IRQ_TMR10:
      flag = &this->mFlag[FLAG_TMR1_OV_TMR10];
      shift = 2;
      break;
    
    //-------------------------------------------------------------------------------------
    case IRQ_TMR11:
      flag = &this->mFlag[FLAG_TMR1_TRG_COM_TMR11];
      shift = 3;
      break;
    
    case IRQ_EXTI5:
    case IRQ_EXTI6:
    case IRQ_EXTI7:
    case IRQ_EXTI8:
    case IRQ_EXTI9:
      flag = &this->mFlag[FLAG_EXTI9_5];
      shift = IRQ_EXTI5 - irq;
      break;
    
    //-------------------------------------------------------------------------------------
    case IRQ_EXTI10:
    case IRQ_EXTI11:
    case IRQ_EXTI12:
    case IRQ_EXTI13:
    case IRQ_EXTI14:
    case IRQ_EXTI15:
      flag = &this->mFlag[FLAG_EXTI15_10];
      shift = IRQ_EXTI10 - irq;
      break;
    
    //-------------------------------------------------------------------------------------
    default:
      flag = 0x00000000;
      break;
  }
  
  if(flag){
    IRQ_FLAG(*flag, shift, enable);
    IRQ_CTRL(CONFIG.irq[irq], *flag);
  }else{
    IRQ_CTRL(CONFIG.irq[irq], enable);
  }
  
  return;
}

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
