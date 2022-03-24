/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_E04A7635_B45D_4789_A805_7BC3EBE0657D
#define CORE_ARTERYTEK_AT32F415_E04A7635_B45D_4789_A805_7BC3EBE0657D

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/serial/bus/CoreSerialBusConfig.h"
#include "core/arterytek/at32f415/serial/bus/CoreSerialBusReg.h"
#include "core/arterytek/at32f415/serial/bus/CoreSerialBusErrorEvent.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace serial{
        namespace bus{
          class CoreSerialBus;
        }
      }
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::arterytek::at32f415::serial::bus::CoreSerialBus extends mcuf::lang::Object implements
  public mcuf::hal::InterruptEvent,
  public mcuf::hal::serial::bus::SerialBus, 
  public mcuf::function::Runnable{
    
  friend CoreSerialBusErrorEvent;

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
    static const core::arterytek::at32f415::serial::bus::CoreSerialBusConfig mConfig[2];
  
    core::arterytek::at32f415::serial::bus::CoreSerialBusReg mRegister;
    uint8_t  mDirect;
    CoreSerialBusErrorEvent mCoreSerialBusErrorEvent;
    
    uint16_t mLength;
    uint16_t mCount;    
    uint8_t* mPointer;
    mcuf::hal::serial::bus::SerialBusEvent* mEvent;
    mcuf::hal::serial::bus::SerialBusStatus mStatus;
    mcuf::io::ByteBuffer* mByteBuffer;
    mcuf::io::ByteBuffer* mByteBufferNext;
    void* mAttachment;

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
     * @brief Construct a new Core Serial Bus object
     * 
     * @param reg 
     */
    CoreSerialBus(core::arterytek::at32f415::serial::bus::CoreSerialBusReg reg);

    /**
     * @brief Destroy the Core Serial Bus object
     * 
     */
    virtual ~CoreSerialBus(void);

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
   * Public Method <Override> mcuf::hal::serial::bus::SerialBusControl
   */
  public:
    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t clockRate(void) override;

    /**
     * @brief 
     * 
     * @param clock 
     * @return uint32_t 
     */
    virtual uint32_t clockRate(uint32_t clock) override;

  /* **************************************************************************************
   * Public Method <Override> mcuf::hal::serial::bus::SerialBusTransfer
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
     * @param address 
     * @param receiver 
     * @param event 
     */
    virtual bool read(uint16_t address, 
                      mcuf::io::ByteBuffer& receiver, 
                      void* attachment,
                      mcuf::hal::serial::bus::SerialBusEvent* event) override;

    /**
     * @brief 
     * 
     * @param address 
     * @param receiver 
     * @param event 
     */
    virtual bool write(uint16_t address, 
                       mcuf::io::ByteBuffer& transfer,
                       void* attachment,
                       mcuf::hal::serial::bus::SerialBusEvent* event) override;
    
    /**
     * @brief 
     * 
     * @param address 
     * @param transfer 
     * @param receiver 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool writeAfterRead(uint16_t address, 
                                mcuf::io::ByteBuffer& transfer, 
                                mcuf::io::ByteBuffer& receiver,
                                void* attachment,
                                mcuf::hal::serial::bus::SerialBusEvent* event) override;

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
  private:
    
    /**
     *
     */
    bool handlerFormat(mcuf::io::ByteBuffer& byteBuffer);
  
    /**
     *
     */
    void handlerClear(void);
  
    /**
     *
     */
    bool beginRead(void);
  
    /**
     *
     */
    bool beginWrite(void);

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_E04A7635_B45D_4789_A805_7BC3EBE0657D */
