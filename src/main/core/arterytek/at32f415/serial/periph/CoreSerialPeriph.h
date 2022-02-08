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
#include "core/arterytek/at32f415/serial/periph/CoreSerialPeriphPacket.h"
#include "core/arterytek/at32f415/serial/periph/CoreSerialPeriphReg.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace serial{
        namespace periph{
          class CoreSerialPeriph;
        }
      }
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::arterytek::at32f415::serial::periph::CoreSerialPeriph extends mcuf::lang::Object implements
  public mcuf::hal::InterruptEvent,
  public mcuf::hal::serial::periph::SerialPeriph,
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
    core::arterytek::at32f415::serial::periph::CoreSerialPeriphReg mRegister;
    mcuf::hal::serial::periph::SerialPeriphEvent* mEvent;
    mcuf::hal::serial::periph::SerialPeriphStatus mStatus;
    core::arterytek::at32f415::serial::periph::CoreSerialPeriphPacket mTransfer;
    core::arterytek::at32f415::serial::periph::CoreSerialPeriphPacket mReceiver;
    
  
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
    CoreSerialPeriph(core::arterytek::at32f415::serial::periph::CoreSerialPeriphReg reg);

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
   * Public Method <Override> - mcuf::hal::InterruptEvent
   */
  public:

    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::serial::periph::SerialPeriph
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
   * Public Method <Override> - mcuf::hal::serial::periph::SerialPeriphTransfer
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
                          mcuf::hal::serial::periph::SerialPeriphPacket* packet,
                          mcuf::hal::serial::periph::SerialPeriphEvent* event) override;
  
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

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_A421D616_D539_4611_AA4E_9D9E304D4E28 */
