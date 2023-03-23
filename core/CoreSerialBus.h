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
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreSerialBusConfig.h"
#include "./CoreSerialBusReg.h"
#include "./CoreSerialBusErrorEvent.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  class CoreSerialBus;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::CoreSerialBus extends mcuf::Object implements
public hal::InterruptEvent,
public hal::SerialBus, 
public func::Runnable{
    
  friend CoreSerialBusErrorEvent;

  /* **************************************************************************************
   * Enum status
   */
  private:
    enum struct Direct : char{
      WRITE,
      READ,
    };
    
  /* **************************************************************************************
   * Variable <Public>
   */
  public:
    static const core::CoreSerialBusConfig mConfig[2];
  
  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private:
    CoreSerialBusErrorEvent mCoreSerialBusErrorEvent;
    int mResult;
    hal::SerialBusEvent* mEvent;
    hal::SerialBusStatus mStatus;
    mcuf::ByteBuffer* mReadBuffer;
    mcuf::ByteBuffer* mWriteBuffer;
  
    uint16_t mAddress;
    core::CoreSerialBusReg mRegister;
    Direct mDirect;

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
    CoreSerialBus(core::CoreSerialBusReg reg);

    /**
     * @brief Destroy the Core Serial Bus object
     * 
     */
    virtual ~CoreSerialBus(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */
   
  /* **************************************************************************************
   * Public Method <Override> - func::Runnable
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
   * Public Method <Override> hal::SerialBus
   */
  public:
    /**
     * @brief 終止讀寫
     * 
     * @return true 終止成功
     * @return false 終止失敗
     */
    virtual bool abort(void) override;
    
   /**
     * @brief 取得輸出頻率
     * 
     * @return uint32_t Hz
     */
    virtual uint32_t getClockRate(void) override;

    /**
     * @brief 設定輸出頻率
     * 
     * @param clock 期望輸出頻率
     * @return uint32_t Hz，實際設定頻率
     */
    virtual uint32_t setClockRate(uint32_t clock) override;

    /**
     * @brief 設定讀寫地址
     * 
     * @param address 讀寫地址
     * @return uint16_t 實際設定之讀寫地址
     */
    virtual uint16_t setAddress(uint16_t address) override;

    /**
     * @brief 取得已被設定之讀寫地址
     * 
     * @return uint16_t 地址
     */
    virtual uint16_t getAddress(void) override;
    
    /**
     * @brief Set the Write Buffer object
     * 
     * @param writeBuffer 
     * @return mcuf::ByteBuffer* 
     */
    virtual mcuf::ByteBuffer* setWriteBuffer(mcuf::ByteBuffer* writeBuffer) override;

    /**
     * @brief Get the Write Buffer object
     * 
     * @return mcuf::ByteBuffer* 
     */
    virtual mcuf::ByteBuffer* getWriteBuffer(void) override;

    /**
     * @brief Set the Read Buffer object
     * 
     * @param readBuffer 
     * @return mcuf::ByteBuffer* 
     */
    virtual mcuf::ByteBuffer* setReadBuffer(mcuf::ByteBuffer* readBuffer) override;

    /**
     * @brief Get the Read Buffer object
     * 
     * @return mcuf::ByteBuffer* 
     */
    virtual mcuf::ByteBuffer* getReadBuffer(void) override;

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
     * @param in 
     * @param event 
     */
    virtual bool read(hal::SerialBusEvent* event) override;

    /**
     * @brief 
     * 
     * @param address 
     * @param out 
     * @param event 
     */
    virtual bool write(hal::SerialBusEvent* event) override;
    
    /**
     * @brief 
     * 
     * @param address 
     * @param out 
     * @param in 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool transfer(hal::SerialBusEvent* event) override;

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
    
    bool handlerConfig(hal::SerialBusEvent* event);
  
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
