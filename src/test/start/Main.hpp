/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_C5145AF1_08A9_4082_93D8_9F4ACA2D712C
#define CORE_ARTERYTEK_AT32F415_C5145AF1_08A9_4082_93D8_9F4ACA2D712C

/* ****************************************************************************************
 * Include
 */  
 
//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace start{
  class Main;
}

/* ****************************************************************************************
 * Class Object
 */  
class start::Main extends mcuf::lang::Thread{

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
  private: core::arterytek::at32f415::CorePin* mLED[8];
  private: uint32_t mStatus;
    
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
  public: Main(void);

  /**
   * Destruct.
   */
  public: ~Main(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

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
  private: void initGPIO(void);


  /**
   *
   */
  private: void throwTest(int i) throw(mcuf::lang::Throwable);
};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_C5145AF1_08A9_4082_93D8_9F4ACA2D712C */
