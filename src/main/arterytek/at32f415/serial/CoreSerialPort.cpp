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

using mcuf::io::ByteBuffer;
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
CoreSerialPort::CoreSerialPort(CoreSerialPortReg reg, const Memory& memory) : RingBuffer(memory){
  this->mRegister = reg;
  this->mPacketRead.clear();
  this->mPacketWrite.clear();
  return;
}

/**
 * 
 */
CoreSerialPort::CoreSerialPort(CoreSerialPortReg reg, uint32_t ringBufferSize) : RingBuffer(ringBufferSize){
  this->mRegister = reg;
  this->mPacketRead.clear();
  this->mPacketWrite.clear();
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
  return 0;
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
  usart_enable(BASE, TRUE);
  return this->baudrate();
}

/* ****************************************************************************************
 * Public Method <Override> - hal::serial::SerialPortTransfer
 */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::abortWrite(void){
  if(!this->writeBusy())
    return false;
  
  usart_interrupt_enable(BASE, USART_TDBE_INT, FALSE);
  this->mPacketWrite.run();
  return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::writeBusy(void){
  return this->mPacketWrite.isExist();
}

/**
 * @brief 
 * 
 * @param byteBuffer 
 * @param attachment 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::write(ByteBuffer& byteBuffer, void* attachment, SerialPortEvent* event){
  
  if(this->writeBusy())
    return false;
  
  if(!this->mPacketWrite.init(byteBuffer, attachment, event))
    return false;
  
  usart_interrupt_enable(BASE, USART_TDBE_INT, TRUE);
  
  return true;
}

/* ****************************************************************************************
 * Public Method <Override> - hal::serial::SerialPortReceiver
 */


/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreSerialPort::avariable(void){
  return static_cast<uint32_t>(this->getCount());
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::abortRead(void){
  if(!this->readBusy())
    return false;
  
  this->mPacketRead.run();
  return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::clear(void){
  if(this->readBusy())
    return false;
  
  this->flush();
  return true;
}

/**
 * @brief pop buffer byte non blocking.
 * 
 * @param result 
 * @return true has data in buffer.
 * @return false no data in buffer.
 */
bool CoreSerialPort::getByte(char& result){
  return this->pop(&result);
}

/**
 * @brief 
 * 
 * @param byteBuffer 
 * @return int 
 */
int CoreSerialPort::get(mcuf::io::ByteBuffer& byteBuffer){
  void* buffer = byteBuffer.pointer(byteBuffer.position());
  int bufferSize = byteBuffer.remaining();
  return this->get(buffer, bufferSize);
}

/**
 * @brief 
 * 
 * @param buffer 
 * @param bufferSize 
 * @return int 
 */
int CoreSerialPort::get(void* buffer, int bufferSize){
  return this->popMult(buffer, bufferSize);
}

/**
 * @brief 
 * 
 * @param buffer 
 * @param maxLength 
 * @return uint32_t 
 */
uint32_t CoreSerialPort::read(void* buffer, uint32_t maxLength){
  if(this->readBusy())
    return 0;

  return static_cast<uint32_t>(this->popMult(buffer, static_cast<int>(maxLength)));
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::readBusy(void){
  return this->mPacketRead.isExist();
}

/**
 * @brief 
 * 
 * @param byteBuffer 
 * @param attachment 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::read(ByteBuffer& byteBuffer, void* attachment, SerialPortEvent* event){
  if(this->readBusy())
    return false;
  
  if(this->getCount() >= byteBuffer.remaining()){
    int count = byteBuffer.remaining();
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer.pointer(byteBuffer.position()));
    this->popMult(pointer, count);
    byteBuffer.position(byteBuffer.position() + count);
    
    if(event)
      event->onSerialPortEvent(SerialPortStatus::READ_SUCCESSFUL, 0, attachment);
    
    return true;
    
  }else if(this->isEmpty()){
    usart_interrupt_enable(BASE, USART_RDBF_INT, FALSE);  //memory protected
    this->mPacketRead.init(byteBuffer, attachment, event);
    usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);  //memory protected
    
  }else{
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer.pointer(byteBuffer.position()));
    
    usart_interrupt_enable(BASE, USART_RDBF_INT, FALSE);  //memory protected
    int count = this->getCount();
    
    byteBuffer.position(byteBuffer.position() + count);
    this->mPacketRead.init(byteBuffer, attachment, event);
    usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);  //memory protected
    
    if(count)
      this->popMult(pointer, count);
  }
 
  return true;
}

/**
 * @brief 
 * 
 * @param value 
 * @param attachment 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreSerialPort::skip(int value, void* attachment, hal::serial::SerialPortEvent* event){
  if(this->readBusy())
    return false;
  
  if(value <= 0)
    return false;
  
  if(this->getCount() >= value){
    this->popMult(nullptr, value);
    
    if(event)
      event->onSerialPortEvent(SerialPortStatus::READ_SUCCESSFUL, 0, attachment);
    
    return true;
    
  }else if(this->isEmpty()){
    usart_interrupt_enable(BASE, USART_RDBF_INT, FALSE);  //memory protected
    this->mPacketRead.init(nullptr, value, attachment, event);
    usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);  //memory protected
    
  }else{

    usart_interrupt_enable(BASE, USART_RDBF_INT, FALSE);  //memory protected
    int count = this->getCount();
    this->mPacketRead.init(nullptr, (value - count), attachment, event);
    usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);  //memory protected
    
    if(count)
      this->popMult(nullptr, count);
  }
 
  return true;
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
    uint16_t readCache = usart_data_receive(base);
    
    if(this->mPacketRead.mLength > this->mPacketRead.mCount){  //receiver pointer is not null
      /* Read one byte from the receive data register */
      
      if(this->mPacketRead.mPointer)
        this->mPacketRead.mPointer[this->mPacketRead.mCount] = static_cast<uint8_t>(readCache);  
        
      ++this->mPacketRead.mCount;

      if(this->mPacketRead.mCount >= this->mPacketRead.mLength){  //receiver is successful
        this->mPacketRead.mStatus = SerialPortStatus::READ_SUCCESSFUL;
        if(!System::execute(this->mPacketRead))
          this->mPacketRead.run();
      }  
    }else{
      this->insert(&readCache);
    }
  }
  
  //check usart tx empty interrupt flag
  if(!((PERIPH_REG((uint32_t)base, USART_TDBE_INT)) & PERIPH_REG_BIT(USART_TDBE_INT)))
    return;
  
  //send handle
  if(usart_flag_get(base, USART_TDBE_FLAG) != RESET){   
    
    /* Write one byte to the transmit data register */
    usart_data_transmit(base, this->mPacketWrite.mPointer[this->mPacketWrite.mCount]);
    
    ++this->mPacketWrite.mCount;
    
    if(this->mPacketWrite.mCount >= this->mPacketWrite.mLength){
      /* Disable the USART Transmit interrupt */
      usart_interrupt_enable(base, USART_TDBE_INT, FALSE);
      this->mPacketWrite.mStatus = SerialPortStatus::WRITE_SUCCESSFUL;
      if(!System::execute(this->mPacketWrite))
        this->mPacketWrite.run();
    }
  }
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
