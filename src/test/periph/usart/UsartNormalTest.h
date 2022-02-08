/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_E6AD62D9_5988_4BB4_A785_88CCFE891A4E
#define CORE_ARTERYTEK_AT32F415_E6AD62D9_5988_4BB4_A785_88CCFE891A4E

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace periph{
  namespace usart{
    namespace normal{
      class UsartNormalTest;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class periph::usart::normal::UsartNormalTest extends mcuf::lang::Thread
  implements mcuf::hal::SerialPortEvent{

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
  private: mcuf::util::Stacker* mStacker;
  private: core::arterytek::at32f415::CorePin* mLED[8];
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
   public: UsartNormalTest(mcuf::lang::Memory& memory, mcuf::util::Stacker* stacker);

  /**
   * Destruct.
   */
  public: ~UsartNormalTest(void);

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
  private: void init(void);
  
};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_E6AD62D9_5988_4BB4_A785_88CCFE891A4E */
