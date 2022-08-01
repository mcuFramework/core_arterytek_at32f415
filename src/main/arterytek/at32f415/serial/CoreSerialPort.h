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
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/serial/CoreSerialPortConfig.h"
#include "arterytek/at32f415/serial/CoreSerialPortReg.h"


/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace serial{
      class CoreSerialPort;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class arterytek::at32f415::serial::CoreSerialPort extends mcuf::lang::Object implements 
public hal::serial::SerialPort,
public mcuf::io::OutputBuffer,
public hal::InterruptEvent,
public mcuf::function::Runnable{
       
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
    static const arterytek::at32f415::serial::CoreSerialPortConfig mCoreSerialPortConfig[5];
    
    mcuf::io::RingBufferInputStream mRingBufferInputStream;
    mcuf::io::OutputBuffer* mOutputBuffer;
    mcuf::io::CompletionHandler<int, void*>* mCompletionHandler;
    void* mAttachment;
    int mResult;
    uint32_t mBaudrate;
    arterytek::at32f415::serial::CoreSerialPortReg mRegister;


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
    CoreSerialPort(arterytek::at32f415::serial::CoreSerialPortReg reg, const mcuf::lang::Memory& memory);
  
    /**
     * @brief Construct a new Core Usart object
     * 
     * @param reg 
     * @param ringBufferSize 
     */
    CoreSerialPort(arterytek::at32f415::serial::CoreSerialPortReg reg, uint32_t ringBufferSize);  

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
   * Public Method <Override> - hal::serial::SerialPortConfig
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
   * Public Method <Override> - mcuf::io::OutputBuffer
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
    inline virtual int get(mcuf::io::InputBuffer& inputBuffer) override{
      return this->mRingBufferInputStream.get(inputBuffer);
    }
    
    /**
     * @brief 
     * 
     * @param byteBuffer 
     * @param length
     * @return int 
     */
    inline virtual int get(mcuf::io::InputBuffer& inputBuffer, int length) override{
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
   * Public Method <Override> - mcuf::io::InputStream
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
    virtual bool read(mcuf::io::InputBuffer& inputBuffer, int timeout) override;
    
    /**
     * @brief nonblocking
     * 
     * @param outputBuffer 
     * @param attachment 
     * @param handler 
     * @return true successful.
     * @return false fail.
     */
    virtual bool read(mcuf::io::InputBuffer& inputBuffer, 
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
    virtual bool read(mcuf::io::InputBuffer& inputBuffer, mcuf::io::Future& future) override;

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
                      mcuf::io::CompletionHandler<int, void*>* handler) override;

    /**
     * @brief 
     * 
     * @param value 
     * @param future 
     * @return true 
     * @return false 
     */
    virtual bool skip(int value, mcuf::io::Future& future) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::io::InputStreamBuffer
   */
  public:
    /**
     * @brief Get the Output Buffer object
     * 
     * @return mcuf::io::OutputBuffer& 
     */
    virtual mcuf::io::OutputBuffer& getOutputBuffer(void) override;
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
   * Public Method <Override> - hal::InterruptEvent
   */
  public: 

    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;
  
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
