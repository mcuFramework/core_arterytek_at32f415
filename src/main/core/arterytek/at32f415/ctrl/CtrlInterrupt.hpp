/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef MCUF_AT32F415_C29B827E_B1A4_466C_824F_22B5C293C4CC
#define MCUF_AT32F415_C29B827E_B1A4_466C_824F_22B5C293C4CC

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
      namespace ctrl{
        class CtrlInterrupt;
      }
    }
  }
}

/* ****************************************************************************************
 * Class CtrlInterrupt
 */  
class core::arterytek::at32f415::ctrl::CtrlInterrupt : 
      public mcuf::lang::Object{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Enum IrqIoint
   */
  public: enum IrqIOINT{
    IRQ_IOINT0,
    IRQ_IOINT1,
    IRQ_IOINT2,
    IRQ_IOINT3,
    IRQ_IOINT4,
    IRQ_IOINT5,
    IRQ_IOINT6,
    IRQ_IOINT7,
    IRQ_IOINT8,
    IRQ_IOINT9,
    IRQ_IOINT10,
    IRQ_IOINT11,
    IRQ_IOINT12,
    IRQ_IOINT13,
    IRQ_IOINT14,
    IRQ_IOINT15,
  };
  
  /* **************************************************************************************
   * Enum IrqSpi
   */
  public: enum IrqSPI{
    IRQ_SPI1,
    IRQ_SPI2
  };  
  
  /* **************************************************************************************
   * Enum IrqTimer
   */
  public: enum IrqTIMER{
    IRQ_TMR2,
    IRQ_TMR3,
    IRQ_TMR4,
    IRQ_TMR5,
    IRQ_TMR9,
    IRQ_TMR10,
    IRQ_TMR11
  };  
  
  /* **************************************************************************************
   * Enum IrqUSART
   */
  public: enum IrqUSART{
    IRQ_USART1,
    IRQ_USART2,
    IRQ_USART3,
    IRQ_UART4,
    IRQ_UART5,
  };  
        
  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: static uint8_t ioint_flag9_5;
  private: static uint8_t ioint_flag15_10;

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
  private: CtrlInterrupt(void) = default;

  /**
   * Disconstruct.
   */
  public: virtual ~CtrlInterrupt(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */


  /**
   * 
   */
  public: static void ioint(IrqIOINT irq, bool enable);

  /**
   * 
   */
  public: static void spi(IrqSPI irq, bool enable);

  /**
   * 
   */
  public: static void timer(IrqTIMER irq, bool enable);

  /**
   * 
   */
  public: static void usart(IrqUSART irq, bool enable);


  /* **************************************************************************************
   * Public Method <Override>
   */

  /* **************************************************************************************
   * Public Method
   */

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
#endif /* MCUF_AT32F415_C29B827E_B1A4_466C_824F_22B5C293C4CC */
