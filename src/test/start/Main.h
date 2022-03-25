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
class start::Main extends mcuf::lang::Thread implements mcuf::hal::serial::bus::SerialBusEvent{
  
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
    mcuf::util::Stacker mStacker;
    core::arterytek::at32f415::serial::bus::CoreSerialBus* coreSerialBus;
    mcuf::hal::general::pin::GeneralPin* mLed[6];

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
     * Construct.
     */
    Main(mcuf::lang::Memory& memory, mcuf::lang::Memory& stacker);

    /**
     * Destruct.
     */
    virtual ~Main(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */
  public:
    /**
     * @brief 
     * 
     * @param status handle status
     * @param result 0 = successful, other = remaining byte count.
     * @param attachment user data
     */
    virtual void onSerialBusEvent(mcuf::hal::serial::bus::SerialBusStatus status, 
                                  int result,
                                  void* attachment) override;
    
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Runnable
   */
  public:
    
    /**
     *
     */
    virtual void run(void) override;

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

#endif/* CORE_ARTERYTEK_AT32F415_C5145AF1_08A9_4082_93D8_9F4ACA2D712C */
