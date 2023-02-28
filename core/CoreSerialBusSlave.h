/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_A903283A_0075_42C5_8E57_6AEE1229B4AC
#define CORE_ARTERYTEK_AT32F415_A903283A_0075_42C5_8E57_6AEE1229B4AC

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreSerialBusConfig.h"
#include "./CoreSerialBusReg.h"
#include "./CoreSerialBusSlaveErrorEvent.h"
#include "./CoreSerialBusErrorCode.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  class CoreSerialBusSlave;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::CoreSerialBusSlave extends mcuf::Object implements
public mcuf::hal::Base,
public mcuf::hal::InterruptEvent{
  
  friend core::CoreSerialBusSlaveErrorEvent;
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
    core::CoreSerialBusSlaveErrorEvent mCoreSerialBusSlaveErrorEvent;
    uint16_t mAddress;
    uint8_t mStatus;
    core::CoreSerialBusReg mRegister;

  /* **************************************************************************************
   * Abstract method <Public>
   */
  public:
    /**
     * @brief 
     * 
     * @param data 
     */
    virtual void onWrite(uint8_t data) abstract;

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    virtual uint8_t onRead(void) abstract;

    /**
     * @brief 
     * 
     */
    virtual void onStart(void) abstract;

    /**
     * @brief 
     * 
     */
    virtual void onError(core::CoreSerialBusErrorCode code) abstract;
    
    /**
     * @brief 
     * 
     */
    virtual void onStop(void) abstract;

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */
  public: 
    /**
     * @brief Construct a new Core Serial Bus Slave object
     * 
     */
    CoreSerialBusSlave(core::CoreSerialBusReg reg, uint16_t address);

    /**
     * @brief Destroy the Core Serial Bus Slave object
     * 
     */
    virtual ~CoreSerialBusSlave(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> mcuf::hal::Base
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
     * @return true not init
     * @return false initd
     */
    virtual bool isInit(void) override;

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
  public:
    /**
     * @brief 
     * 
     */
    virtual void start(void);
  
    /**
     * @brief 
     * 
     */
    virtual void stop(void);

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
     * @brief 
     * 
     */
    void statusClear(void);

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_A903283A_0075_42C5_8E57_6AEE1229B4AC */
