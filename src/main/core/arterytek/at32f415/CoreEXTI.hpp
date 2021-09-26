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
      implements mcuf::hal::PinEdgeTrigger{

  /* **************************************************************************************
   * Enum Registor
   */
  public: enum Registor{
    REG_EXTI0,
    REG_EXTI1,
    REG_EXTI2,
    REG_EXTI3,
    REG_EXTI4,
    REG_EXTI5,
    REG_EXTI6,
    REG_EXTI7,
    REG_EXTI8,
    REG_EXTI9,
    REG_EXTI10,
    REG_EXTI11,
    REG_EXTI12,
    REG_EXTI13,
    REG_EXTI14,
    REG_EXTI15,
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
  public: CoreEXTI(void) = default;

  /**
   * Disconstruct.
   */
  public: virtual ~CoreEXTI(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

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

#endif/* CORE_ARTERYTEK_AT32F415_D8D8EA5F_F429_45F9_8877_8B78AE047D8A */
