/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include <string.h>
 
//-----------------------------------------------------------------------------------------
#include "bsp_arterytek_at32f415.h"
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/serial/CoreSerialPort.h"
#include "arterytek/at32f415/Core.h"
#include "arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */ 

/* ****************************************************************************************
 * Using
 */  
using namespace arterytek::at32f415::serial;
using namespace hal::serial;

//-----------------------------------------------------------------------------------------
using mcuf::function::Consumer;
using mcuf::lang::Memory;
using mcuf::lang::Pointer;
using mcuf::lang::System;

using mcuf::io::CompletionHandler;
using mcuf::io::Future;
using mcuf::io::InputBuffer;
using mcuf::io::RingBuffer;

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<unsigned char>(this->mRegister))
#define CONFIG                   (CoreSerialPort::mCoreSerialPortConfig[REGNUMB])
#define BASE                     ((usart_type*)CONFIG.baseAddress)

/* ****************************************************************************************
 * Variable <Static>
 */
const CoreSerialPortConfig CoreSerialPort::mCoreSerialPortConfig[5] = {
  {USART1 , CRM_USART1_PERIPH_CLOCK , CoreInterrupt::IRQ_USART1 },
  {USART2 , CRM_USART2_PERIPH_CLOCK , CoreInterrupt::IRQ_USART2 },
  {USART3 , CRM_USART3_PERIPH_CLOCK , CoreInterrupt::IRQ_USART3 },
  {UART4  , CRM_UART4_PERIPH_CLOCK  , CoreInterrupt::IRQ_UART4  },
  {UART5  , CRM_UART5_PERIPH_CLOCK  , CoreInterrupt::IRQ_UART5  },
};

/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreSerialPort::CoreSerialPort(CoreSerialPortReg reg, const Memory& memory) : 
mRingBufferInputStream(memory){
  
  this->mResult = 0;
  this->mRegister = reg;
  return;
}

/**
 * 
 */
CoreSerialPort::CoreSerialPort(CoreSerialPortReg reg, uint32_t ringBufferSize) : 
mRingBufferInputStream(ringBufferSize){
  
  this->mResult = 0;
  this->mRegister = reg;
  return;
}

/**
 * 
 */
CoreSerialPort::~CoreSerialPort(void){
  this->deinit();
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - hal::Base
 */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::deinit(void){
  if(!this->isInit())
    return false;
  
  Core::interrupt.irqEnable(CONFIG.irq, false);
  usart_reset(BASE);
  crm_periph_clock_enable(static_cast<crm_periph_clock_type>(CONFIG.crmClock), FALSE);
  this->abortRead();
  this->abortWrite();
  Core::interrupt.setHandler(CONFIG.irq, nullptr);
  return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(static_cast<crm_periph_clock_type>(CONFIG.crmClock), TRUE);
  Core::interrupt.setHandler(CONFIG.irq, this);
  
  usart_init(BASE, 9600, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(BASE, TRUE);
  usart_receiver_enable(BASE, TRUE);
  
  Core::interrupt.irqEnable(CONFIG.irq, true);
  usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);
  usart_enable(BASE, TRUE);
  return true;
}
  
/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override> - hal::serial::SerialPortConfig
 */

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreSerialPort::baudrate(void){
  return this->mBaudrate;
}

/**
 * @brief 
 * 
 * @param rate 
 * @return uint32_t 
 */
uint32_t CoreSerialPort::baudrate(uint32_t rate){
  usart_enable(BASE, FALSE);
  usart_init(BASE, rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  this->mBaudrate = rate;
  usart_enable(BASE, TRUE);
  return this->baudrate();
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::io::InputStreamBuffer
 */

/**
 * @brief Get the Output Buffer object
 * 
 * @return mcuf::io::OutputBuffer& 
 */
mcuf::io::OutputBuffer& CoreSerialPort::getOutputBuffer(void){
  return *this;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::io::OutputBuffer
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::io::InputStream
 */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::abortRead(void){
  return this->mRingBufferInputStream.abortRead();
}

/**
 * @brief 
 * 
 * @return true is busy.
 * @return false isn't busy.
 */
bool CoreSerialPort::readBusy(void){
  return this->mRingBufferInputStream.readBusy();
}

/**
 * @brief 
 * 
 * @param outputBuffer 
 * @return int 
 */
bool CoreSerialPort::read(mcuf::io::InputBuffer& inputBuffer, int timeout){
  return this->mRingBufferInputStream.read(inputBuffer, timeout);
}

/**
 * @brief nonblocking
 * 
 * @param outputBuffer 
 * @param attachment 
 * @param handler 
 * @return true successful.
 * @return false fail.
 */
bool CoreSerialPort::read(InputBuffer& inputBuffer, void* attachment, CompletionHandler<int, void*>* handler){
  return this->mRingBufferInputStream.read(inputBuffer, attachment, handler);
}

/**
 * @brief 
 * 
 * @param outputBuffer 
 * @param future 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::read(InputBuffer& inputBuffer, Future& future){
  return this->mRingBufferInputStream.read(inputBuffer, future);
}

/**
 * @brief 
 * 
 * @param value 
 * @param attachment 
 * @param handler 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::skip(int value, void* attachment, CompletionHandler<int, void*>* handler){
  return this->mRingBufferInputStream.skip(value, attachment, handler);
}

/**
 * @brief 
 * 
 * @param value 
 * @param future 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::skip(int value, Future& future){
  return this->mRingBufferInputStream.skip(value, future);
}

/* **************************************************************************************
 * Public Method <Override> - mcuf::io::OutputStream
 */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::abortWrite(void){
  if(this->writeBusy() == true)
    return false;
  
  usart_interrupt_enable(BASE, USART_TDBE_INT, FALSE);
  this->run();
  return true;
}

/**
 * @brief 
 * 
 * @return true is busy.
 * @return false isn't busy.
 */
bool CoreSerialPort::writeBusy(void){
  return (this->mOutputBuffer != nullptr);
}

/**
 * @brief 
 * 
 * @param outputBuffer
 * @param future 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::write(mcuf::io::OutputBuffer& outputBuffer, int timeout){
  Future future = Future();
  if(this->write(outputBuffer, future) == false)
    return false;
  
  future.waitDone(timeout);
  if(future.isDone() == false)
    this->abortWrite();
  
  future.waitDone();
  return true;
}  

/**
 * @brief 
 * 
 * @param outputBuffer
 * @param attachment 
 * @param handler 
 * @return true successful.
 * @return false fail.
 */
bool CoreSerialPort::write(OutputBuffer& outputBuffer, void* attachment, CompletionHandler<int, void*>* handler){
  if(this->writeBusy())
    return false;
  
  if(outputBuffer.avariable() <= 0)
    return false;
  
  this->mOutputBuffer = &outputBuffer;
  this->mCompletionHandler = handler;
  this->mAttachment = attachment;
  usart_interrupt_enable(BASE, USART_TDBE_INT, TRUE);
  
  return true;
}
/**
 * @brief 
 * 
 * @param outputBuffer
 * @param future 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::write(OutputBuffer& outputBuffer, Future& future){
  if(!future.isIdle())
    return false;
  
  future.setWait();
  bool result = this->write(outputBuffer, nullptr, &future);
  if(result == false)
    future.clear();

  return result;
}

/* **************************************************************************************
 * Public Method <Override> - mcuf::io::InputStreamBuffer
 */
/**
 * @brief Get the Output Buffer object
 * 
 * @return mcuf::io::OutputBuffer& 
 */
mcuf::io::OutputBuffer& CoreSerialPort::getOutputBuffer(void){
  return *this;
}

/* ****************************************************************************************
 * Public Method <Override> - hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreSerialPort::interruptEvent(void){
  usart_type* base = BASE;
  
  if(usart_flag_get(base, USART_RDBF_FLAG) != RESET){
    char readCache = usart_data_receive(base);
    this->mRingBufferInputStream.putByte(readCache);
  }
  
  //check usart tx empty interrupt flag
  if(!((PERIPH_REG((uint32_t)base, USART_TDBE_INT)) & PERIPH_REG_BIT(USART_TDBE_INT)))
    return;
  
  //send handle
  if(usart_flag_get(base, USART_TDBE_FLAG) != RESET){
    char data;
    
    if(this->mOutputBuffer->getByte(data)){
      /* Write one byte to the transmit data register */
      usart_data_transmit(base, data);
      ++this->mResult;
      
    }else{
      usart_interrupt_enable(base, USART_TDBE_INT, FALSE);
      System::execute(*this);
      
    }
  }
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */

/**
 * @brief 
 * 
 */
void CoreSerialPort::run(void){
  if(this->writeBusy() == false)
    return;
  
  CompletionHandler<int, void*>* completionHandler = this->mCompletionHandler;
  void* attachment = this->mAttachment;
  int result = this->mResult;
  this->mResult = 0;
  this->mOutputBuffer = nullptr;
  
  if(completionHandler != nullptr)
    completionHandler->completed(result, attachment);
  
  return;
}

/* ****************************************************************************************
 * Public Method
 */

/* ****************************************************************************************
 * Protected Method <Static>
 */
 
/* ****************************************************************************************
 * Protected Method <Override>
 */ 

/* ****************************************************************************************
 * Protected Method
 */

/* ****************************************************************************************
 * Private Method
 */

/* ****************************************************************************************
 * End of file
 */ 
