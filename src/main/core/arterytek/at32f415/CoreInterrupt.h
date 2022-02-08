/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_F1908D49_0286_4F03_95AD_EC7128B908B9
#define CORE_ARTERYTEK_AT32F415_F1908D49_0286_4F03_95AD_EC7128B908B9

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"


/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CoreInterrupt;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreInterrupt extends mcuf::lang::Object
      implements mcuf::hal::InterruptEvent{

  /* **************************************************************************************
   * Enum Irq
   */
  public: enum Irq{
    IRQ_ADC1          = 0,  
    IRQ_CMP1          = 1,  
    IRQ_CMP2          = 2,  
    IRQ_DMA1_1        = 3,  
    IRQ_DMA1_2        = 4,  
    IRQ_DMA1_3        = 5,  
    IRQ_DMA1_4        = 6,  
    IRQ_DMA1_5        = 7,  
    IRQ_DMA1_6        = 8,  
    IRQ_DMA1_7        = 9,  
    IRQ_DMA2_1        = 10, 
    IRQ_DMA2_2        = 11, 
    IRQ_DMA2_3        = 12, 
    IRQ_DMA2_4        = 13, 
    IRQ_DMA2_5        = 14, 
    IRQ_DMA2_6        = 15, 
    IRQ_DMA2_7        = 16, 
    IRQ_ERTC_WKUP     = 17, 
    IRQ_EXINT0        = 18, 
    IRQ_EXINT1        = 19, 
    IRQ_EXINT2        = 20, 
    IRQ_EXINT3        = 21, 
    IRQ_EXINT4        = 22, 
    IRQ_EXINT5        = 23, 
    IRQ_EXINT6        = 24, 
    IRQ_EXINT7        = 25, 
    IRQ_EXINT8        = 26, 
    IRQ_EXINT9        = 27, 
    IRQ_EXINT10       = 28, 
    IRQ_EXINT11       = 29, 
    IRQ_EXINT12       = 30, 
    IRQ_EXINT13       = 31, 
    IRQ_EXINT14       = 32, 
    IRQ_EXINT15       = 33, 
    IRQ_FLASH         = 34, 
    IRQ_I2C1_ERR      = 35, 
    IRQ_I2C1_EVT      = 36, 
    IRQ_I2C2_ERR      = 37, 
    IRQ_I2C2_EVT      = 38, 
    IRQ_CRM           = 39, 
    IRQ_SDIO1         = 40, 
    IRQ_SPI1          = 41, 
    IRQ_SPI2          = 42, 
    IRQ_TMR1          = 43, 
    IRQ_TMR1_BRK      = 44, 
    IRQ_TMR1_TRG_COM  = 45, 
    IRQ_TMR1_CC       = 46, 
    IRQ_TMR2          = 47, 
    IRQ_TMR3          = 48, 
    IRQ_TMR4          = 49, 
    IRQ_TMR5          = 50, 
    IRQ_TMR9          = 51, 
    IRQ_TMR10         = 52, 
    IRQ_TMR11         = 53, 
    IRQ_OTGFS         = 54, 
    IRQ_WWDT          = 55, 
    IRQ_PVM           = 56, 
    IRQ_TAMP_STAMP    = 57, 
    IRQ_USART1        = 58, 
    IRQ_USART2        = 59, 
    IRQ_USART3        = 60, 
    IRQ_UART4         = 61, 
    IRQ_UART5         = 62, 
    IRQ_MAX_QUANTITY,
  };
        
  /* **************************************************************************************
   * Enum Flag
   */
  public: enum Flag{
    FLAG_TMR1_BRK_TMR9,
    FLAG_TMR1_OV_TMR10,
    FLAG_TMR1_TRG_COM_TMR11,
    FLAG_EXINT9_5,
    FLAG_EXINT15_10,
    FLAG_DMA2_Channel4_5,
    FLAG_DMA2_Channel6_7,
  };
  
  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */
  private: uint8_t mFlag[8];
  
  public: mcuf::hal::InterruptEvent* mHandle[IRQ_MAX_QUANTITY];

  
  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */

  /**
   * Construct.
   */
  public: CoreInterrupt(void);

  /**
   * Disconstruct.
   */
  public: virtual ~CoreInterrupt(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::InterruptEvent
   */
  public: void interruptEvent(void) override;

  /* **************************************************************************************
   * Public Method
   */

  /**
   * set interrupt handler.
   */
  public: void setHandler(Irq irq, mcuf::hal::InterruptEvent* runnable);
 
  
  /**
   * enable or disable interrupt.
   */
  public: void irqEnable(Irq irq, bool enable);

  /* **************************************************************************************
   * Protected Method <Static>
   */

  /* **************************************************************************************
   * Protected Method <Override>
   */

  /* **************************************************************************************
   * Protected Method
   */

  /* **************************************************************************************
   * Private Method <Static>
   */

  /* **************************************************************************************
   * Private Method <Override>
   */
   
  /* **************************************************************************************
   * Private Method
   */  

};



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_F1908D49_0286_4F03_95AD_EC7128B908B9 */
