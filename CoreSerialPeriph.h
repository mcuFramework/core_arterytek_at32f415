/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_A421D616_D539_4611_AA4E_9D9E304D4E28
#define CORE_ARTERYTEK_AT32F415_A421D616_D539_4611_AA4E_9D9E304D4E28

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreSerialPeriphConfig.h"
#include "./CoreSerialPeriphPacket.h"
#include "./CoreSerialPeriphReg.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  class CoreSerialPeriph;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::CoreSerialPeriph extends mcuf::Object implements
  public mcuf::hal::InterruptEvent,
  public mcuf::hal::SerialPeriph,
  public mcuf::Runnable{

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
    static const core::CoreSerialPeriphConfig mCoreSerialPeriphConfig[2];
  
    mcuf::hal::GeneralPin* mSelectChipSelect;
    mcuf::hal::GeneralPin* mChipSelect[8];
    core::CoreSerialPeriphReg mRegister;
    mcuf::hal::SerialPeriphEvent* mEvent;
    mcuf::hal::SerialPeriphStatus mStatus;
    core::CoreSerialPeriphPacket mTransfer;
    core::CoreSerialPeriphPacket mReceiver;
    
  
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
     * @brief Construct a new Core Serial Periph object
     * 
     * @param reg 
     */
    CoreSerialPeriph(core::CoreSerialPeriphReg reg);

    /**
     * @brief Destroy the Core Serial Periph object
     * 
     */
    virtual ~CoreSerialPeriph(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::Runnable
   */
  public:

    /**
     * @brief 
     * 
     */
    virtual void run(void) override;

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
   * Public Method <Override> - mcuf::hal::SerialPeriph
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
     * @return true not init
     * @return false initd
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::SerialPeriphTransfer
   */
  public:

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool abort(void) override;
    
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
     * @param chipSelect 
     * @param packet 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool transfer(uint32_t chipSelect, 
                          mcuf::hal::SerialPeriphPacket* packet,
                          mcuf::hal::SerialPeriphEvent* event) override;
  
  /* **************************************************************************************
   * Public Method
   */
  public:
    
    /**
     *
     */
    bool setChipSelectPin(uint32_t chipSelect, mcuf::hal::GeneralPin* pin);

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
  private:
    
    /**
     *
     */
  static CoreSerialPeriphPacket handlePacket(mcuf::ByteBuffer* byteBuffer);
  
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
    void execute(void);

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_A421D616_D539_4611_AA4E_9D9E304D4E28 */
