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
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CoreTimer;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreTimer extends mcuf::lang::Object
      implements mcuf::hal::Timer ,mcuf::function::Runnable{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Enum Register
   */
  public: enum Register{
    REG_TMR1  = 0,
    REG_TMR2  = 1,
    REG_TMR3  = 2,
    REG_TMR4  = 3,
    REG_TMR5  = 4,
    REG_TMR9  = 5,
    REG_TMR10 = 6,
    REG_TMR11 = 7,
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
  
  private: Register mRegister;
  private: void* mAttachment;
  private: mcuf::function::Consumer<void*>* mExecute;

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
  public: CoreTimer(Register reg);

  /**
   * Destruct.
   */
  public: ~CoreTimer(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
   */
  
  /**
   * uninitialze hardware.
   */
  public: virtual bool deinit(void) override;
  
  /**
   * 
   */
  public: virtual void cancel(void) override;

  /**
   * 
   */
  public: virtual bool isBusy(void) override;
  
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
  
  /**
   * 
   */
  public: virtual bool isDone(void) override;

  /**
   * 
   */
  public: virtual uint32_t getTickBaseMilliSecond(void) override;
  
  /**
   *
   */
  public: virtual void run(void) override;

  /**
   * 
   */
  public: virtual bool startAtTick(uint32_t tick) override;

  /**
   * 
   */
  public: virtual bool startAtTick(uint32_t tick,
                                   void* attachment,  
                                   mcuf::function::Consumer<void*>* execute) override;
  
  /**
   * 
   */
  public: virtual bool startAtTime(uint32_t microSecond) override;

  /**
   * 
   */
  public: virtual bool startAtTime(uint32_t microSecond, 
                                   void* attachment,  
                                   mcuf::function::Consumer<void*>* execute) override;

  /* **************************************************************************************
   * Public Method
   */
  
  /**
   *
   */
  public: void execute(void);                             

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
  private: void clockEnable(bool enable);
  
  /**
   *
   */
  private: void configTick(uint32_t tick);
  
  /**
   *
   */
  private: bool configTime(uint32_t microSecond);
  
  /**
   *
   */
  private: void interruptEnable(bool enable);


};



/* *****************************************************************************************
 * End of file
 */ 


#endif/* CORE_ARTERYTEK_AT32F415_A50EF4F4_B571_4399_889B_FE5C5348027C */
