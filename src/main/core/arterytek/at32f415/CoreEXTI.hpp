/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_D8D8EA5F_F429_45F9_8877_8B78AE047D8A
#define CORE_ARTERYTEK_AT32F415_D8D8EA5F_F429_45F9_8877_8B78AE047D8A

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
      class CoreEXTI;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreEXTI extends mcuf::lang::Object
  implements mcuf::hal::EdgeTrigger, mcuf::function::Runnable{

  /* **************************************************************************************
   * Enum Registor
   */
  public: enum Register{
    REG_EXTI0  = 0,
    REG_EXTI1  = 1,
    REG_EXTI2  = 2,
    REG_EXTI3  = 3,
    REG_EXTI4  = 4,
    REG_EXTI5  = 5,
    REG_EXTI6  = 6,
    REG_EXTI7  = 7,
    REG_EXTI8  = 8,
    REG_EXTI9  = 9,
    REG_EXTI10 = 10,
    REG_EXTI11 = 11,
    REG_EXTI12 = 12,
    REG_EXTI13 = 13,
    REG_EXTI14 = 14,
    REG_EXTI15 = 15,
  };
  
  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: static uint16_t channelEnable;
	private: static uint16_t channelMode;
	private: static uint16_t channelLevel;
  
  private: Register mRegister;
  private: Event* mRunnableRise;
  private: Event* mRunnableFall;

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
  public: CoreEXTI(Register reg);

  /**
   * Destruct.
   */
  public: ~CoreEXTI(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::Base
   */

  /**
   * uninitialze hardware.
   */
  public: virtual bool deinit(void) override;

  /**
   * initialze hardware;
   */
  public: virtual bool init(void) override;
  
  /**
   * get hardware initialzed status.
   * 
   * @return false = not init, true = initd
   */
  public: virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::PinEdgeTrigger
   */
   
  /**
   * 
   */
  public: virtual void disableAll(void) override;

  /**
   * 
   */
  public: virtual void disableFall(void) override;

  /**
   * 
   */
  public: virtual void disableRise(void) override;

  /**
   * 
   */
  public: virtual bool enableFall(mcuf::hal::EdgeTrigger::Event* event) override;

  /**
   * 
   */
  public: virtual bool enableRise(mcuf::hal::EdgeTrigger::Event* event) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Runnable
   */
  
  /**
   *
   */
  public: virtual void run(void) override;
  
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
   
  /**
   *
   */
  private: void periphReset(void);

};



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D8D8EA5F_F429_45F9_8877_8B78AE047D8A */
