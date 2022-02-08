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
 
//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/general/trigger/CoreEdgeTriggerReg.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace general{
        namespace trigger{
          class CoreEdgeTrigger;
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::general::trigger::CoreEdgeTrigger extends mcuf::lang::Object implements 
  public mcuf::hal::general::trigger::EdgeTrigger, 
  public mcuf::hal::InterruptEvent{

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: 
    static uint16_t channelEnable;
    static uint16_t channelMode;
    static uint16_t channelLevel;
  
    mcuf::hal::general::trigger::EdgeTriggerEvent* mRunnableRise;
    mcuf::hal::general::trigger::EdgeTriggerEvent* mRunnableFall;
    core::arterytek::at32f415::general::trigger::CoreEdgeTriggerReg mRegister;

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
  public: CoreEdgeTrigger(core::arterytek::at32f415::general::trigger::CoreEdgeTriggerReg reg);

  /**
   * Destruct.
   */
  public: ~CoreEdgeTrigger(void);

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
  public: virtual bool enableFall(mcuf::hal::general::trigger::EdgeTriggerEvent* event) override;

  /**
   * 
   */
  public: virtual bool enableRise(mcuf::hal::general::trigger::EdgeTriggerEvent* event) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::InterruptEvent
   */
  
  /**
   *
   */
  public: virtual void interruptEvent(void) override;
  
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
