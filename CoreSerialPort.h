/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141
#define CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreSerialPortConfig.h"
#include "./CoreSerialPortReg.h"


/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  class CoreSerialPort;
}

/* ****************************************************************************************
 * Class Object
 */  
class core::CoreSerialPort extends mcuf::Object implements 
public mcuf::hal::SerialPort,
public mcuf::OutputBuffer,
public mcuf::hal::InterruptEvent,
public mcuf::Runnable{
       
  /* **************************************************************************************
   * Enum Register
   */

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
    static const core::CoreSerialPortConfig mCoreSerialPortConfig[5];
    
    mcuf::RingBufferInputStream mRingBufferInputStream;
    mcuf::OutputBuffer* mOutputBuffer;
    mcuf::CompletionHandler<int, void*>* mCompletionHandler;
    void* mAttachment;
    int mResult;
    uint32_t mBaudrate;
    core::CoreSerialPortReg mRegister;


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
     * @brief Construct a new Core Usart object
     * 
     * @param reg 
     * @param memory 
     */
    CoreSerialPort(core::CoreSerialPortReg reg, const mcuf::Memory& memory);
  
    /**
     * @brief Construct a new Core Usart object
     * 
     * @param reg 
     * @param ringBufferSize 
     */
    CoreSerialPort(core::CoreSerialPortReg reg, uint32_t ringBufferSize);  

    /**
     * @brief Destroy the Core Usart object
     * 
     */
    virtual ~CoreSerialPort(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
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
     * @brief initialze hardware
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;

    /**
     * @brief 
     * 
     * @return true initd.
     * @return false not init.
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::SerialPortConfig
   */
  public:
  
    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t baudrate(void) override;

    /**
     * @brief 
     * 
     * @param rate 
     * @return uint32_t 
     */
    virtual uint32_t baudrate(uint32_t rate) override;
  /* **************************************************************************************
   * Public Method <Override> - mcuf::InputStreamBuffer
   */
  public:
    /**
     * @brief Get the Output Buffer object
     * 
     * @return mcuf::OutputBuffer& 
     */
    virtual mcuf::OutputBuffer& getOutputBuffer(void) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::OutputBuffer
   */
  public:
    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    inline virtual bool isEmpty(void) const override{
      return this->mRingBufferInputStream.isEmpty();
    }
  
    /**
     * @brief 
     * 
     * @return int 
     */
    inline virtual int avariable(void) const override{
      return this->mRingBufferInputStream.avariable();
    }

    /**
     * @brief pop buffer byte non blocking.
     * 
     * @param result 
     * @return true has data in buffer.
     * @return false no data in buffer.
     */
    inline virtual bool getByte(char& result) override{
      return this->mRingBufferInputStream.getByte(result);
    }

    /**
     * @brief 
     * 
     * @param byteBuffer 
     * @return int 
     */
    inline virtual int get(mcuf::InputBuffer& inputBuffer) override{
      return this->mRingBufferInputStream.get(inputBuffer);
    }
    
    /**
     * @brief 
     * 
     * @param byteBuffer 
     * @param length
     * @return int 
     */
    inline virtual int get(mcuf::InputBuffer& inputBuffer, int length) override{
      return this->mRingBufferInputStream.get(inputBuffer, length);
    }    

    /**
     * @brief 
     * 
     * @param buffer 
     * @param bufferSize 
     * @return int 
     */
    inline virtual int get(void* buffer, int bufferSize) override{
      return this->mRingBufferInputStream.get(buffer, bufferSize);
    }

    /**
     * @brief 
     * 
     * @param value 
     * @return int 
     */
    inline virtual int skip(int value) override{
      return this->mRingBufferInputStream.skip(value);
    }

  /* **************************************************************************************
   * Public Method <Override> - mcuf::InputStream
   */
  public:
    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool abortRead(void) override;  
    
    /**
     * @brief 
     * 
     * @return true is busy.
     * @return false isn't busy.
     */
    virtual bool readBusy(void) override;

    /**
     * @brief 
     * 
     * @param outputBuffer 
     * @param timeout
     * @return int 
     */
    virtual bool read(mcuf::InputBuffer& inputBuffer, int timeout) override;
    
    /**
     * @brief nonblocking
     * 
     * @param outputBuffer 
     * @param attachment 
     * @param handler 
     * @return true successful.
     * @return false fail.
     */
    virtual bool read(mcuf::InputBuffer& inputBuffer, 
                      void* attachment,
                      mcuf::CompletionHandler<int, void*>* handler) override;

    /**
     * @brief 
     * 
     * @param outputBuffer 
     * @param future 
     * @return true 
     * @return false 
     */
    virtual bool read(mcuf::InputBuffer& inputBuffer, mcuf::Future& future) override;

    /**
     * @brief 
     * 
     * @param value 
     * @param attachment 
     * @param handler 
     * @return true 
     * @return false 
     */
    virtual bool skip(int value, 
                      void* attachment,
                      mcuf::CompletionHandler<int, void*>* handler) override;

    /**
     * @brief 
     * 
     * @param value 
     * @param future 
     * @return true 
     * @return false 
     */
    virtual bool skip(int value, mcuf::Future& future) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::OutputStream
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
    virtual bool write(mcuf::OutputBuffer& outputBuffer, int timeout) override;    
  
    /**
     * @brief 
     * 
     * @param outputBuffer
     * @param attachment 
     * @param handler 
     * @return true successful.
     * @return false fail.
     */
    virtual bool write(mcuf::OutputBuffer& outputBuffer, 
                      void* attachment,
                      mcuf::CompletionHandler<int, void*>* handler) override;

    /**
     * @brief 
     * 
     * @param outputBuffer
     * @param future 
     * @return true 
     * @return false 
     */
    virtual bool write(mcuf::OutputBuffer& outputBuffer, mcuf::Future& future) override;
    
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
   * Public Method <Override> - mcuf::Runnable
   */
  public:
    /**
     * @brief 
     * 
     */
    virtual void run(void) override;
                        
  
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



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141 */
