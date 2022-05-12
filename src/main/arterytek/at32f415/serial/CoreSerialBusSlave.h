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
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/serial/CoreSerialBusConfig.h"
#include "arterytek/at32f415/serial/CoreSerialBusReg.h"
#include "arterytek/at32f415/serial/CoreSerialBusSlaveErrorEvent.h"
#include "arterytek/at32f415/serial/CoreSerialBusErrorCode.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace arterytek{
  namespace at32f415{
    namespace serial{
      class CoreSerialBusSlave;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::serial::CoreSerialBusSlave extends mcuf::lang::Object implements
public hal::Base,
public hal::InterruptEvent{
  
  friend arterytek::at32f415::serial::CoreSerialBusSlaveErrorEvent;
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
    arterytek::at32f415::serial::CoreSerialBusSlaveErrorEvent mCoreSerialBusSlaveErrorEvent;
    uint16_t mAddress;
    uint8_t mStatus;
    arterytek::at32f415::serial::CoreSerialBusReg mRegister;

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
    virtual void onError(arterytek::at32f415::serial::CoreSerialBusErrorCode code) abstract;
    
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
    CoreSerialBusSlave(arterytek::at32f415::serial::CoreSerialBusReg reg, uint16_t address);

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
   * Public Method <Override> hal::Base
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
