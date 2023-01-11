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
public mcuf::hal::InterruptEvent,
public mcuf::hal::SerialBus, 
public mcuf::function::Runnable{
    
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
    mcuf::hal::SerialBusEvent* mEvent;
    mcuf::hal::SerialBusStatus mStatus;
    mcuf::OutputBuffer* mOutputBuffer;
    mcuf::InputBuffer* mInputBuffer;
    void* mAttachment;
  
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
   * Public Method <Override> mcuf::hal::SerialBusControl
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
   * Public Method <Override> mcuf::hal::SerialBusTransfer
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
     * @param in
     * @param attachment   
     * @param event 
     */
    virtual bool read(uint16_t address, 
                      mcuf::InputBuffer& in, 
                      void* attachment,
                      mcuf::hal::SerialBusEvent* event) override;

    /**
     * @brief 
     * 
     * @param address 
     * @param out
     * @param attachment                      
     * @param event 
     */
    virtual bool write(uint16_t address, 
                       mcuf::OutputBuffer& out,
                       void* attachment,
                       mcuf::hal::SerialBusEvent* event) override;
    
    /**
     * @brief 
     * 
     * @param address 
     * @param out
     * @param in
     * @param attachment                       
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool transfer(uint16_t address,
                          mcuf::OutputBuffer& out, 
                          mcuf::InputBuffer& in,
                          void* attachment,
                          mcuf::hal::SerialBusEvent* event) override;

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
                       mcuf::OutputBuffer* transfer, 
                       mcuf::InputBuffer* receiver,
                       void* attachment,
                       mcuf::hal::SerialBusEvent* event);
  
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
