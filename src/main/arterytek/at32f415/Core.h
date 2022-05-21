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
#include "mcuf.h"

#include "arterytek/at32f415/CoreIomux.h"
#include "arterytek/at32f415/general/CoreGeneralPort.h"
#include "arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    class Core;
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class arterytek::at32f415::Core extends mcuf::lang::Object{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */
  public: static arterytek::at32f415::CoreInterrupt interrupt;
  public: static arterytek::at32f415::CoreIomux iomux;
  public: static arterytek::at32f415::general::CoreGeneralPort gpioa;
  public: static arterytek::at32f415::general::CoreGeneralPort gpiob;
  public: static arterytek::at32f415::general::CoreGeneralPort gpioc;
  public: static arterytek::at32f415::general::CoreGeneralPort gpiod;
  public: static arterytek::at32f415::general::CoreGeneralPort gpiof;
    
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
