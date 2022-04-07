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
#include "arterytek/at32f415/serial/CoreSerialBusConfig.h"
#include "arterytek/at32f415/serial/CoreSerialBusReg.h"
#include "arterytek/at32f415/serial/CoreSerialBusErrorEvent.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace serial{
      class CoreSerialBus;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::serial::CoreSerialBus extends mcuf::lang::Object implements
  public hal::InterruptEvent,
  public hal::serial::SerialBus, 
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
    static const arterytek::at32f415::serial::CoreSerialBusConfig mConfig[2];
  
    arterytek::at32f415::serial::CoreSerialBusReg mRegister;
    uint8_t  mDirect;
    CoreSerialBusErrorEvent mCoreSerialBusErrorEvent;
    
    uint16_t mAddress;
    uint16_t mLength;
    uint16_t mCount;    
    uint8_t* mPointer;
    hal::serial::SerialBusEvent* mEvent;
    hal::serial::SerialBusStatus mStatus;
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
    CoreSerialBus(arterytek::at32f415::serial::CoreSerialBusReg reg);

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
   * Public Method <Override> - hal::InterruptEvent
   */
  public:

    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;   
   
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
   * Public Method <Override> hal::serial::SerialBusControl
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
   * Public Method <Override> hal::serial::SerialBusTransfer
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
                      hal::serial::SerialBusEvent* event) override;

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
                       hal::serial::SerialBusEvent* event) override;
    
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
                                hal::serial::SerialBusEvent* event) override;

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
    
    bool handlerConfig(uint16_t address, 
                       mcuf::io::ByteBuffer* transfer, 
                       mcuf::io::ByteBuffer* receiver,
                       void* attachment,
                       hal::serial::SerialBusEvent* event);
  
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
    bool begin(void);
                       
    /**
     *
     */
    void afterRead(void);                       
                       
    /**
     *
     */
    void statusClear(void);
                       
                       
};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_E04A7635_B45D_4789_A805_7BC3EBE0657D */
