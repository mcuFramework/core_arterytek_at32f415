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
#include "core/arterytek/at32f415/serial/port/CoreSerialPort.h"
#include "core/arterytek/at32f415/Core.h"
#include "core/arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */ 
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace serial{
        namespace port{
          struct CoreSerialPortConfig{
            void* Register;
            crm_periph_clock_type crmClock;
            CoreInterrupt::Irq irq;
            
          }const coreSerialPortConfig[5] = {
            {USART1 , CRM_USART1_PERIPH_CLOCK , CoreInterrupt::IRQ_USART1 },
            {USART2 , CRM_USART2_PERIPH_CLOCK , CoreInterrupt::IRQ_USART2 },
            {USART3 , CRM_USART3_PERIPH_CLOCK , CoreInterrupt::IRQ_USART3 },
            {UART4  , CRM_UART4_PERIPH_CLOCK  , CoreInterrupt::IRQ_UART4  },
            {UART5  , CRM_UART5_PERIPH_CLOCK  , CoreInterrupt::IRQ_UART5  },
          };
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using namespace core::arterytek::at32f415::serial::port;
using namespace mcuf::hal::serial::port;

//-----------------------------------------------------------------------------------------
using mcuf::function::Consumer;
using mcuf::lang::Memory;
using mcuf::lang::Pointer;
using mcuf::lang::System;

using mcuf::io::ByteBuffer;
using mcuf::util::RingBuffer;

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<char>(this->mRegister))
#define CONFIG                   (coreSerialPortConfig[REGNUMB])
#define BASE                     ((usart_type*)CONFIG.Register)

/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreSerialPort::CoreSerialPort(CoreSerialPortReg reg, const Memory& memory) construct RingBuffer(memory){
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
 * Public Method <Override> - mcuf::hal::Base
 */

/**
 * uninitialze hardware.
 */
bool CoreSerialPort::deinit(void){
  if(!this->isInit())
    return false;
  
  Core::interrupt.irqEnable(CONFIG.irq, false);
  usart_reset(BASE);
  crm_periph_clock_enable(CONFIG.crmClock, FALSE);
  this->abortRead();
  this->abortWrite();
  Core::interrupt.setHandler(CONFIG.irq, nullptr);
  return true;
}

/**
 * initialze hardware;
 */
bool CoreSerialPort::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(CONFIG.crmClock, TRUE);
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
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreSerialPort::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::serial::port::SerialPortConfig
 */

/**
 * 
 */
uint32_t CoreSerialPort::baudrate(void){
  return 0;
}

/**
 * 
 */
uint32_t CoreSerialPort::baudrate(uint32_t rate){
  usart_enable(BASE, FALSE);
  usart_init(BASE, rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_enable(BASE, TRUE);
  return 0;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::serial::port::SerialPortTransfer
 */

/**
 * 
 */
bool CoreSerialPort::abortRead(void){
  return false;
}

/**
 * 
 */
bool CoreSerialPort::abortWrite(void){
  return false;
}

/**
 *
 */
bool CoreSerialPort::readBusy(void){
  return this->mPacketRead.isExist();
}

/**
 *
 */
bool CoreSerialPort::writeBusy(void){
  return this->mPacketWrite.isExist();
}

/**
 * 
 */
bool CoreSerialPort::read(ByteBuffer* byteBuffer, SerialPortEvent* event){
  if(this->readBusy())
    return false;
  
  if(this->getCount() >= byteBuffer->remaining()){
    uint32_t count = this->getCount();
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer->pointer(byteBuffer->position()));
    this->popMult(pointer, count);
    byteBuffer->position(byteBuffer->position() + count);
    
    if(event)
      event->onSerialPortEvent(SerialPortStatus::READ_SUCCESSFUL, byteBuffer);
    
    return true;
  }else if(this->isEmpty()){
    usart_interrupt_enable(BASE, USART_RDBF_INT, FALSE);  //memory protected
    this->mPacketRead.init(*byteBuffer, event);
    usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);  //memory protected
    
  }else{
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer->pointer(byteBuffer->position()));
    
    usart_interrupt_enable(BASE, USART_RDBF_INT, FALSE);  //memory protected
    uint32_t count = this->getCount();
    
    byteBuffer->position(byteBuffer->position() + count);
    this->mPacketRead.init(*byteBuffer, event);
    usart_interrupt_enable(BASE, USART_RDBF_INT, TRUE);  //memory protected
    
    if(count)
      this->popMult(pointer, count);
  }
 
  return true;
}

/**
 * 
 */
bool CoreSerialPort::write(ByteBuffer* byteBuffer, SerialPortEvent* event){
  
  if(this->writeBusy())
    return false;
  
  if(!this->mPacketWrite.init(*byteBuffer, event))
    return false;
  
  usart_interrupt_enable(BASE, USART_TDBE_INT, TRUE);
  
  return true;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::InterruptEvent
 */
void CoreSerialPort::interruptEvent(void){
  usart_type* base = BASE;
  
  if(usart_flag_get(base, USART_RDBF_FLAG) != RESET){
    uint8_t readCache = usart_data_receive(base);
    
    if(this->mPacketRead.mPointer && (this->mPacketRead.mLength > this->mPacketRead.mCount)){  //receiver pointer is not null
      /* Read one byte from the receive data register */
      this->mPacketRead.mPointer[this->mPacketRead.mCount] = readCache;  
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
      /* Disable the USART1 Transmit interrupt */
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
