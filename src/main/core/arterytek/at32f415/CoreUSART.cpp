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
#include "bsp_arterytek_at32f415/at32f415.h"
#include "core/arterytek/at32f415/Core.h"
#include "core/arterytek/at32f415/CoreInterrupt.h"
#include "core/arterytek/at32f415/CoreUsart.h"

/* ****************************************************************************************
 * Namespace
 */ 
namespace core{
  namespace arterytek{
    namespace at32f415{
      
      struct CoreUsartConfig{
        void* Register;
        crm_periph_clock_type crmClock;
        CoreInterrupt::Irq irq;
        
      }const coreUsartConfig[5] = {
        {USART1 , CRM_USART1_PERIPH_CLOCK , CoreInterrupt::IRQ_USART1 },
        {USART2 , CRM_USART2_PERIPH_CLOCK , CoreInterrupt::IRQ_USART2 },
        {USART3 , CRM_USART3_PERIPH_CLOCK , CoreInterrupt::IRQ_USART3 },
        {UART4  , CRM_UART4_PERIPH_CLOCK  , CoreInterrupt::IRQ_UART4  },
        {UART5  , CRM_UART5_PERIPH_CLOCK  , CoreInterrupt::IRQ_UART5  },
      };
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreUsart;
using mcuf::function::Consumer;
using mcuf::lang::Memory;
using mcuf::lang::Pointer;
using mcuf::lang::System;


using mcuf::io::ByteBuffer;
using mcuf::io::CompletionHandler;
using mcuf::util::RingBuffer;
using mcuf::hal::SerialPort;
using mcuf::hal::SerialPortEvent;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                   (coreUsartConfig[this->mRegister])
#define BASE                     ((usart_type*)CONFIG.Register)

/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreUsart::CoreUsart(CoreUsart::Register reg, const Memory& memory) construct RingBuffer(memory){
  this->mRegister = reg;
  this->mPacketRead.clear();
  this->mPacketWrite.clear();
  return;
}

/**
 * 
 */
CoreUsart::~CoreUsart(void){
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
bool CoreUsart::deinit(void){
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
bool CoreUsart::init(void){
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
bool CoreUsart::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override>
 */

/**
 * 
 */
bool CoreUsart::abortRead(void){
  return false;
}

/**
 * 
 */
bool CoreUsart::abortWrite(void){
  return false;
}

/**
 * 
 */
uint32_t CoreUsart::baudrate(void){
  return 0;
}

/**
 * 
 */
uint32_t CoreUsart::baudrate(uint32_t rate){
  usart_enable(BASE, FALSE);
  usart_init(BASE, rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_enable(BASE, TRUE);
  return 0;
}

/**
 *
 */
bool CoreUsart::readBusy(void){
  return this->mPacketRead.isExist();
}

/**
 *
 */
bool CoreUsart::writeBusy(void){
  return this->mPacketWrite.isExist();
}

/**
 * 
 */
bool CoreUsart::read(ByteBuffer* byteBuffer, SerialPortEvent* event){
  if(this->readBusy())
    return false;
  
  if(this->getCount() >= byteBuffer->remaining()){
    uint32_t count = this->getCount();
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer->pointer(byteBuffer->position()));
    this->popMult(pointer, count);
    byteBuffer->position(byteBuffer->position() + count);
    
    if(event)
      event->onSerialPortEvent(SerialPortEvent::HAL_SERIALPORT_READ_SUCCESSFUL, byteBuffer);
    
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
bool CoreUsart::write(ByteBuffer* byteBuffer, SerialPortEvent* event){
  
  if(this->writeBusy())
    return false;
  
  if(!this->mPacketWrite.init(*byteBuffer, event))
    return false;
  
  usart_interrupt_enable(BASE, USART_TDBE_INT, TRUE);
  
  return true;
}



/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */
void CoreUsart::run(void){
  usart_type* base = BASE;
  
  if(usart_flag_get(base, USART_RDBF_FLAG) != RESET){
    uint8_t readCache = usart_data_receive(base);
    
    if(this->mPacketRead.mPointer && (this->mPacketRead.mLength > this->mPacketRead.mCount)){  //receiver pointer is not null
      /* Read one byte from the receive data register */
      this->mPacketRead.mPointer[this->mPacketRead.mCount] = readCache;  
      ++this->mPacketRead.mCount;

      if(this->mPacketRead.mCount >= this->mPacketRead.mLength){  //receiver is successful
        this->mPacketRead.mStatus = SerialPortEvent::HAL_SERIALPORT_READ_SUCCESSFUL;
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
      this->mPacketWrite.mStatus = SerialPortEvent::HAL_SERIALPORT_WRITE_SUCCESSFUL;
      if(!System::execute(this->mPacketWrite))
        this->mPacketWrite.run();
    }
  }
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::io::OutputStream
 */
  
/**
 *
 */
void CoreUsart::flush(void){

}
  
/**
 *  write nonBlocking
 */
void CoreUsart::write(ByteBuffer* byteBuffer, void* attachment, CompletionHandler<int, void*>* handler){
                     
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
 * Variable
 */

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */

/**
 *
 */
void CoreUsart::Packet::run(void){
  
  ByteBuffer* byteBuffer = this->mByteBuffer;
  SerialPortEvent* event = this->mEvent;
  byteBuffer->position(byteBuffer->position() + this->mCount);
  this->clear();
  
  if(event)
    event->onSerialPortEvent(this->mStatus, byteBuffer);
  
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreUsart::Packet::clear(void){
  this->mPointer = nullptr;
  this->mByteBuffer = nullptr;
  this->mCount = 0;
  this->mLength = 0;
}

/**
 *
 */
bool CoreUsart::Packet::init(ByteBuffer& byteBuffer, SerialPortEvent* event){
  if(this->isExist())
    return false;
  
  if(!byteBuffer.hasRemaining())
    return false;
  
  this->mByteBuffer = &byteBuffer;
  this->mEvent = event;
  this->mLength = byteBuffer.remaining();
  this->mCount = 0;
  this->mPointer = static_cast<uint8_t*>(byteBuffer.pointer(byteBuffer.position()));
  
  return true;
}

/**
 *
 */
bool CoreUsart::Packet::isExist(void){
  return this->mByteBuffer;
}


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
 * Private Method <Static>
 */
 
/* ****************************************************************************************
 * Private Method
 */

/* ****************************************************************************************
 * End of file
 */ 
