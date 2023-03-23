/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "mcuf/package-info.h" 
#include "../bsp/package-info.h" 

#include "./CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  struct CoreInterruptConfig{
    IRQn irq[CoreInterrupt::IRQ_MAX_QUANTITY];
      
  }const coreInterruptConfig = {
    {
     /*  IRQ_ADC1          = 0,  */   ADC1_IRQn,
     /*  IRQ_CMP1          = 1,  */   CMP1_IRQn,
     /*  IRQ_CMP2          = 2,  */   CMP2_IRQn,
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
     /*  IRQ_EXINT0        = 18, */   EXINT0_IRQn,
     /*  IRQ_EXINT1        = 19, */   EXINT1_IRQn,
     /*  IRQ_EXINT2        = 20, */   EXINT2_IRQn,
     /*  IRQ_EXINT3        = 21, */   EXINT3_IRQn,
     /*  IRQ_EXINT4        = 22, */   EXINT4_IRQn,
     /*  IRQ_EXINT5        = 23, */   EXINT9_5_IRQn,
     /*  IRQ_EXINT6        = 24, */   EXINT9_5_IRQn,
     /*  IRQ_EXINT7        = 25, */   EXINT9_5_IRQn,
     /*  IRQ_EXINT8        = 26, */   EXINT9_5_IRQn,
     /*  IRQ_EXINT9        = 27, */   EXINT9_5_IRQn,
     /*  IRQ_EXINT10       = 28, */   EXINT15_10_IRQn,
     /*  IRQ_EXINT11       = 29, */   EXINT15_10_IRQn,
     /*  IRQ_EXINT12       = 30, */   EXINT15_10_IRQn,
     /*  IRQ_EXINT13       = 31, */   EXINT15_10_IRQn,
     /*  IRQ_EXINT14       = 32, */   EXINT15_10_IRQn,
     /*  IRQ_EXINT15       = 33, */   EXINT15_10_IRQn,
     /*  IRQ_FLASH         = 34, */   FLASH_IRQn,
     /*  IRQ_I2C1_ERR      = 35, */   I2C1_ERR_IRQn,
     /*  IRQ_I2C1_EVT      = 36, */   I2C1_EVT_IRQn,
     /*  IRQ_I2C2_ERR      = 37, */   I2C2_ERR_IRQn,
     /*  IRQ_I2C2_EVT      = 38, */   I2C2_EVT_IRQn,
     /*  IRQ_CRM           = 39, */   CRM_IRQn,
     /*  IRQ_SDIO1         = 40, */   SDIO1_IRQn,
     /*  IRQ_SPI1          = 41, */   SPI1_IRQn,
     /*  IRQ_SPI2          = 42, */   SPI2_IRQn,
     /*  IRQ_TMR1          = 43, */   TMR1_OVF_TMR10_IRQn,
     /*  IRQ_TMR1_BRK      = 44, */   TMR1_BRK_TMR9_IRQn,
     /*  IRQ_TMR1_TRG_COM  = 45, */   TMR1_TRG_HALL_TMR11_IRQn,
     /*  IRQ_TMR1_CC       = 46, */   TMR1_CH_IRQn,
     /*  IRQ_TMR2          = 47, */   TMR2_GLOBAL_IRQn,
     /*  IRQ_TMR3          = 48, */   TMR3_GLOBAL_IRQn,
     /*  IRQ_TMR4          = 49, */   TMR4_GLOBAL_IRQn,
     /*  IRQ_TMR5          = 50, */   TMR5_GLOBAL_IRQn,
     /*  IRQ_TMR9          = 51, */   TMR1_BRK_TMR9_IRQn,
     /*  IRQ_TMR10         = 52, */   TMR1_OVF_TMR10_IRQn,
     /*  IRQ_TMR11         = 53, */   TMR1_TRG_HALL_TMR11_IRQn,
     /*  IRQ_OTGFS         = 54, */   OTGFS1_IRQn,
     /*  IRQ_WWDT          = 55, */   WWDT_IRQn,
     /*  IRQ_PVM           = 56, */   PVM_IRQn,
     /*  IRQ_TAMP_STAMP    = 57, */   TAMP_STAMP_IRQn,
     /*  IRQ_USART1        = 58, */   USART1_IRQn,
     /*  IRQ_USART2        = 59, */   USART2_IRQn,
     /*  IRQ_USART3        = 60, */   USART3_IRQn,
     /*  IRQ_UART4         = 61, */   UART4_IRQn,
     /*  IRQ_UART5         = 62, */   UART5_IRQn,
     /*  IRQ_OTGFS_WAKE    = 63, */   OTGFS1_WKUP_IRQn
    },
  };
}


/* ****************************************************************************************
 * Using
 */  
using hal::InterruptEvent;
using core::CoreInterrupt;

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

/**
 *
 */
CoreInterrupt::CoreInterrupt(void){
  for(int i=0; i<IRQ_MAX_QUANTITY; ++i){
    this->mHandle[i] = this;
  }
  
  return;
}

/**
 *
 */
CoreInterrupt::~CoreInterrupt(void){
  return;
}

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override>
 */

/**
 *
 */
void CoreInterrupt::interruptEvent(void){
  return;
}

/* ****************************************************************************************
 * Public Method
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"

/**
 *
 */
void CoreInterrupt::setHandler(Irq irq, InterruptEvent* runnable){
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
void CoreInterrupt::irqEnable(Irq irq, bool enable){
  uint8_t* flag;
  uint8_t shift = 0;
  
  switch(irq){
    //-------------------------------------------------------------------------------------
    case IRQ_TMR1:
      IRQ_FLAG(this->mFlag[FLAG_TMR1_BRK_TMR9], 0, enable);
      IRQ_CTRL(TMR1_BRK_TMR9_IRQn, this->mFlag[FLAG_TMR1_BRK_TMR9]);
    
      IRQ_FLAG(this->mFlag[FLAG_TMR1_TRG_COM_TMR11], 0, enable);
      IRQ_CTRL(TMR1_TRG_HALL_TMR11_IRQn, this->mFlag[FLAG_TMR1_TRG_COM_TMR11]);
    
      IRQ_CTRL(TMR1_CH_IRQn, enable);
      
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
    
    case IRQ_EXINT5:
    case IRQ_EXINT6:
    case IRQ_EXINT7:
    case IRQ_EXINT8:
    case IRQ_EXINT9:
      flag = &this->mFlag[FLAG_EXINT9_5];
      shift = IRQ_EXINT5 - irq;
      break;
    
    //-------------------------------------------------------------------------------------
    case IRQ_EXINT10:
    case IRQ_EXINT11:
    case IRQ_EXINT12:
    case IRQ_EXINT13:
    case IRQ_EXINT14:
    case IRQ_EXINT15:
      flag = &this->mFlag[FLAG_EXINT15_10];
      shift = IRQ_EXINT10 - irq;
      break;
    
    //-------------------------------------------------------------------------------------
    default:
      flag = nullptr;
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

#pragma clang diagnostic pop

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
