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
class start::Main extends mcuf::lang::Thread implements mcuf::hal::TimerEvent, 
  mcuf::hal::SerialPortEvent{

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
  private: mcuf::util::Stacker mStacker;
  private: core::arterytek::at32f415::CorePin* mLED[8];
  private: core::arterytek::at32f415::CorePin* mBTN[8];
  private: uint32_t mStatus;
  private: mcuf::io::ByteBuffer* txBuffer;
  private: mcuf::io::ByteBuffer* rxBuffer;
  private: core::arterytek::at32f415::CoreUsart* usart;
    
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
   public: Main(mcuf::lang::Memory& memory, mcuf::lang::Memory& stacker);

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
   * Public Method <Override> - mcuf::hal::Timer::Event
   */
  
  /**
   *
   */
  public: void onTimerEvent(TimerStatus status) override;   

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::SerialPortEvent::Event
   */
  
  /**
   *
   */
  public: void onSerialPortEvent(SerialPortStatus status, mcuf::io::ByteBuffer* byteBuffer) override;

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

};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_C5145AF1_08A9_4082_93D8_9F4ACA2D712C */
