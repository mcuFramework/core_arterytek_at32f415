/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_D8ED01C5_7D15_40C2_907A_57E66EBBBBA4
#define CORE_ARTERYTEK_AT32F415_D8ED01C5_7D15_40C2_907A_57E66EBBBBA4

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "periph/Test.hpp"

/* ****************************************************************************************
 * Namespace
 */  
namespace periph{
  class TestCoreEXTI;
}

/* ****************************************************************************************
 * Class Object
 */  
class periph::TestCoreEXTI extends mcuf::lang::Object
  implements mcuf::function::Runnable, periph::Test{

  /* **************************************************************************************
   * Subclass
   */
  
  public: enum TestMode{
    TESTMODE_RISE = 0,
    TESTMODE_FALL = 1,
    TESTMODE_ALL  = 2
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
  private: TestMode mTestMode;
  private: core::arterytek::at32f415::CorePin* mPin;
  private: core::arterytek::at32f415::CoreEXTI mCoreEXTI;

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
  public: TestCoreEXTI(core::arterytek::at32f415::CorePin& pin, 
                       core::arterytek::at32f415::CoreEXTI::Register reg,
                       TestMode testMode);

  /**
   * Destruct.
   */
  public: ~TestCoreEXTI(void);

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
   * Public Method <Override> - periph::Test
   */  

  /**
   *
   */
  public: virtual void start(void) override;
  
  /** 
   *
   */
  public: virtual void stop(void) override;

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

#endif/* CORE_ARTERYTEK_AT32F415_D8ED01C5_7D15_40C2_907A_57E66EBBBBA4 */
