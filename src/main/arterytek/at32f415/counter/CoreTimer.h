/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_A50EF4F4_B571_4399_889B_FE5C5348027C
#define CORE_ARTERYTEK_AT32F415_A50EF4F4_B571_4399_889B_FE5C5348027C

/* ****************************************************************************************
 * Include
 */  
 
//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//----------------------------------------------------------------------------------------- 
#include "arterytek/at32f415/counter/CoreTimerReg.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace counter{
      class CoreTimer;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class arterytek::at32f415::counter::CoreTimer extends mcuf::lang::Object implements 
  public hal::counter::Timer ,
  public hal::InterruptEvent{
        
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
    arterytek::at32f415::counter::CoreTimerReg mRegister;
    hal::counter::TimerEvent* mEvent;

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
     * @brief Construct a new Core Timer object
     * 
     * @param reg 
     */
    CoreTimer(arterytek::at32f415::counter::CoreTimerReg reg);

    /**
     * @brief Destroy the Core Timer object
     * 
     */
    ~CoreTimer(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - hal::Base
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
     * @brief initialze hardware
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;

    /**
     * @brief 
     * 
     * @return true initd.
     * @return false not init.
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::counter::TimerControl
   */  
  public:
  
    /**
     * @brief 
     * 
     */
    virtual void cancel(void) override;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool isBusy(void) override;
    
    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool isDone(void) override;
    
    /**
     * @brief Get the Timer Clock object
     * 
     * @return uint32_t hz
     */
    virtual uint32_t getTimerClock(void) override;  

    /**
     * @brief 
     * 
     * @param tick 
     * @return true 
     * @return false 
     */
    virtual bool startAtTick(uint32_t tick) override;

    /**
     * @brief 
     * 
     * @param tick 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool startAtTick(uint32_t tick, hal::counter::TimerEvent* event) override;
    
    /**
     * @brief 
     * 
     * @param microSecond 
     * @return true 
     * @return false 
     */
    virtual bool startAtTime(uint32_t microSecond) override;

    /**
     * @brief 
     * 
     * @param microSecond 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool startAtTime(uint32_t microSecond, hal::counter::TimerEvent* event) override;
    
    /**
     * @brief 
     * 
     * @param tick 
     */
    virtual void resetTick(uint32_t tick) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::InterruptEvent
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
  public: 

    /**
     * @brief 
     * 
     */
    void execute(void);                             

  /* **************************************************************************************
   * Protected Method <Static>
   */

  /* **************************************************************************************
   * Protected Method <Override>
   */

  /* **************************************************************************************
   * Protected Method
   */
  protected: 
  
    /**
     * @brief 
     * 
     * @param enable 
     */
    void clockEnable(bool enable);
    
    /**
     * @brief 
     * 
     * @param tick 
     */
    void configTick(uint32_t tick);
    
    /**
     * @brief Get the Tick At Micro Second object
     * 
     * @param microSecond 
     * @return uint32_t 
     */
    uint32_t getTickAtMicroSecond(uint32_t microSecond);
    
    /**
     * @brief 
     * 
     * @param enable 
     */
    void interruptEnable(bool enable);
  
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

#endif/* CORE_ARTERYTEK_AT32F415_A50EF4F4_B571_4399_889B_FE5C5348027C */
