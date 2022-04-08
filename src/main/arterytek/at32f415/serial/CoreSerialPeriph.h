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
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/serial/CoreSerialPeriphConfig.h"
#include "arterytek/at32f415/serial/CoreSerialPeriphPacket.h"
#include "arterytek/at32f415/serial/CoreSerialPeriphReg.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace serial{
      class CoreSerialPeriph;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::serial::CoreSerialPeriph extends mcuf::lang::Object implements
  public hal::InterruptEvent,
  public hal::serial::SerialPeriph,
  public mcuf::function::Runnable{

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
    static const arterytek::at32f415::serial::CoreSerialPeriphConfig mCoreSerialPeriphConfig[2];
  
    hal::general::GeneralPin* mSelectChipSelect;
    hal::general::GeneralPin* mChipSelect[8];
    arterytek::at32f415::serial::CoreSerialPeriphReg mRegister;
    hal::serial::SerialPeriphEvent* mEvent;
    hal::serial::SerialPeriphStatus mStatus;
    arterytek::at32f415::serial::CoreSerialPeriphPacket mTransfer;
    arterytek::at32f415::serial::CoreSerialPeriphPacket mReceiver;
    
  
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
    CoreSerialPeriph(arterytek::at32f415::serial::CoreSerialPeriphReg reg);

    /**
     * @brief Destroy the Core Serial Periph object
     * 
     */
    virtual ~CoreSerialPeriph(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Runnable
   */
  public:

    /**
     * @brief 
     * 
     */
    virtual void run(void) override;

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
   * Public Method <Override> - hal::serial::SerialPeriph
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
   * Public Method <Override> - hal::serial::SerialPeriphTransfer
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
                          hal::serial::SerialPeriphPacket* packet,
                          hal::serial::SerialPeriphEvent* event) override;
  
  /* **************************************************************************************
   * Public Method
   */
  public:
    
    /**
     *
     */
    bool setChipSelectPin(uint32_t chipSelect, hal::general::GeneralPin* pin);

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
  static CoreSerialPeriphPacket handlePacket(mcuf::io::ByteBuffer* byteBuffer);
  
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
