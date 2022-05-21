/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_22815FFC_AE64_4292_8A47_5EF5C2B183D0
#define CORE_ARTERYTEK_AT32F415_22815FFC_AE64_4292_8A47_5EF5C2B183D0

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */  
namespace arterytek{
  namespace at32f415{
    namespace usb{
      class CoreHumanInterfaceDevices;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::usb::CoreHumanInterfaceDevices extends mcuf::io::RingBufferInputStream implements
public mcuf::io::OutputStream,
public hal::Base,
public hal::InterruptEvent{

  /* **************************************************************************************
   * Enum Descriptor
   */
  private:
    mcuf::io::OutputBuffer* mOutputBuffer;
    void* mAttachment;
    mcuf::io::CompletionHandler<int, void*>* mHandler;
    int mResult;
  
  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */

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
     * @brief Construct a new Core Human Interface Devices object
     * 
     * @param buffer 
     * @param bufferSize 
     */
    CoreHumanInterfaceDevices(void* buffer, uint32_t bufferSize);
      
    /**
     * @brief Construct a new Core Human Interface Devices object
     * 
     * @param memory 
     */
    CoreHumanInterfaceDevices(const mcuf::lang::Memory& memory);  

    /**
     * @brief Construct a new Core Human Interface Devices object
     * 
     * @param length 
     */
    CoreHumanInterfaceDevices(uint32_t length);

    /**
     * @brief Destroy the Core Human Interface Devices object
     * 
     */
    virtual ~CoreHumanInterfaceDevices(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
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
   * Public Method <Override> - hal::InterruptEvent
   */
  public:
    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;
  /* **************************************************************************************
   * Public Method <Override> - mcuf::io::OutputStream
   */
  public:
    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool abortWrite(void) override;
    
    /**
     * @brief 
     * 
     * @return true is busy.
     * @return false isn't busy.
     */
    virtual bool writeBusy(void) override;
    
    /**
     * @brief 
     * 
     * @param outputBuffer
     * @param future 
     * @return true 
     * @return false 
     */
    virtual bool write(mcuf::io::OutputBuffer& outputBuffer, int timeout) override;  
    
    /**
     * @brief 
     * 
     * @param outputBuffer
     * @param attachment 
     * @param handler 
     * @return true successful.
     * @return false fail.
     */
    virtual bool write(mcuf::io::OutputBuffer& outputBuffer, 
                       void* attachment,
                       mcuf::io::CompletionHandler<int, void*>* handler) override;

    /**
     * @brief 
     * 
     * @param outputBuffer
     * @param future 
     * @return true 
     * @return false 
     */
    virtual bool write(mcuf::io::OutputBuffer& outputBuffer, mcuf::io::Future& future) override;

  /* **************************************************************************************
   * Public Method
   */
  public:
    /**
     * @brief 
     * 
     */
    void onTransfer(void);
  
    /**
     * @brief 
     * 
     * @param data 
     */
    void onReceiver(void *udev, uint8_t *report, uint16_t len);

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
    void executeCompletionHandler(void);

    /**
     * @brief 
     * 
     */
    void writePacket(void);
    
};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_22815FFC_AE64_4292_8A47_5EF5C2B183D0 */
