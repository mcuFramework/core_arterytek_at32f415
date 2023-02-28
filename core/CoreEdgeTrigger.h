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
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreEdgeTriggerReg.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  class CoreEdgeTrigger;
}

/* ****************************************************************************************
 * Class Object
 */  
class core::CoreEdgeTrigger extends mcuf::Object implements 
  public mcuf::hal::EdgeTrigger, 
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
  
    mcuf::hal::EdgeTriggerEvent* mRunnableRise;
    mcuf::hal::EdgeTriggerEvent* mRunnableFall;
    core::CoreEdgeTriggerReg mRegister;

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */
  public: 
    /**
     * @brief Construct a new Core Edge Trigger object
     * 
     * @param reg 
     */
    CoreEdgeTrigger(core::CoreEdgeTriggerReg reg);

    /**
     * @brief Destroy the Core Edge Trigger object
     * 
     */
    virtual ~CoreEdgeTrigger(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::Base
   */
  public:
    /**
     * @brief uninitialze hardware.
     * 
     * @return true 
     * @return false 
     */
    virtual bool deinit(void) override;

    /**
     * @brief initialze hardware;
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;
    
    /**
     * @brief get hardware initialzed status.
     * 
     * @return true initd.
     * @return false not init.
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::PinEdgeTrigger
   */
  public: 

    /**
     * @brief 
     * 
     */
    virtual void disableAll(void) override;

    /**
     * @brief 
     * 
     */
    virtual void disableFall(void) override;

    /**
     * @brief 
     * 
     */
    virtual void disableRise(void) override;

    /**
     * @brief 
     * 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool enableFall(mcuf::hal::EdgeTriggerEvent* event) override;

    /**
     * @brief 
     * 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool enableRise(mcuf::hal::EdgeTriggerEvent* event) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::InterruptEvent
   */
  public: 
  
    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;
  
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
  private:
  
    /**
     *
     */
    void periphReset(void);

};



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D8D8EA5F_F429_45F9_8877_8B78AE047D8A */
