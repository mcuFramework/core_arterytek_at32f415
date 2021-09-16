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
class core::arterytek::at32f415::CoreInterrupt{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */
  public: static mcuf::function::Runnable* WWDG;
  public: static mcuf::function::Runnable* PVD;
  public: static mcuf::function::Runnable* TAMP_STAMP;
  public: static mcuf::function::Runnable* ERTC_WKUP;
  public: static mcuf::function::Runnable* FLASH;
  public: static mcuf::function::Runnable* RCC;
  public: static mcuf::function::Runnable* DMA1_Channel[7];
  public: static mcuf::function::Runnable* DMA2_Channel[7];
  public: static mcuf::function::Runnable* EXTI[15];
  public: static mcuf::function::Runnable* USART[5];
  
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
  private: CoreInterrupt(void) = default;

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

#endif/* CORE_ARTERYTEK_AT32F415_F1908D49_0286_4F03_95AD_EC7128B908B9 */
