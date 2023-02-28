/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_B783141D_7465_4A74_900D_2B6244C11E04
#define CORE_ARTERYTEK_AT32F415_B783141D_7465_4A74_900D_2B6244C11E04

/* ****************************************************************************************
 * Include
 */  
#include "mcuf/package-info.h" 

#include "./CoreIomux.h"
#include "./CoreGeneralPort.h"
#include "./CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  class Core;
}

/* ****************************************************************************************
 * Class Object
 */  
class core::Core extends mcuf::Object{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */
  public: static core::CoreInterrupt interrupt;
  public: static core::CoreIomux iomux;
  public: static core::CoreGeneralPort gpioa;
  public: static core::CoreGeneralPort gpiob;
  public: static core::CoreGeneralPort gpioc;
  public: static core::CoreGeneralPort gpiod;
  public: static core::CoreGeneralPort gpiof;
    
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
  private:
    /**
     * 
     */
    Core(void);

    /**
     * 
     */
    virtual ~Core(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */
  
  /**
   *
   */
  public: static uint32_t getSystemCoreClock(void);
  
  /**
   *
   */
  public: static bool setSystemCoreClock(uint32_t mhz);
  

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

#endif/* CORE_ARTERYTEK_AT32F415_B783141D_7465_4A74_900D_2B6244C11E04 */
