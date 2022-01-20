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
#include "core/arterytek/at32f415/Core.hpp"
#include "core/arterytek/at32f415/CoreInterrupt.hpp"
#include "core/arterytek/at32f415/CoreUsart.hpp"

/* ****************************************************************************************
 * Namespace
 */ 
namespace core{
  namespace arterytek{
    namespace at32f415{
      
      struct CoreUsartConfig{
        void* Register;
        volatile uint32_t* clock;
        uint32_t clockMask;
        CoreInterrupt::Irq irq;
        
      }const coreTimerConfig[5] = {
        {USART1 , &RCC->APB2EN, RCC_APB2PERIPH_USART1 , CoreInterrupt::IRQ_USART1 },
        {USART2 , &RCC->APB1EN, RCC_APB1PERIPH_USART2 , CoreInterrupt::IRQ_USART2 },
        {USART3 , &RCC->APB1EN, RCC_APB1PERIPH_USART3 , CoreInterrupt::IRQ_USART3 },
        {UART4  , &RCC->APB1EN, RCC_APB1PERIPH_UART4  , CoreInterrupt::IRQ_UART4  },
        {UART5  , &RCC->APB1EN, RCC_APB1PERIPH_UART4  , CoreInterrupt::IRQ_UART5  },
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


using mcuf::io::channel::ByteBuffer;
using mcuf::io::channel::CompletionHandler;
using mcuf::util::RingBuffer;
using mcuf::hal::SerialPort;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                   (coreTimerConfig[this->mRegister])
#define BASE                     ((USART_Type*)CONFIG.Register)

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
  
  Core::interrupt.irqHandler(CONFIG.irq, false);
  USART_Reset(BASE);
  *CONFIG.clock &= ~CONFIG.clockMask;
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
  
  *CONFIG.clock |= CONFIG.clockMask;
  Core::interrupt.setHandler(CONFIG.irq, this);
  
  USART_InitType config;
  
  config.USART_BaudRate = 9600;
  config.USART_WordLength = USART_WordLength_8b;
  config.USART_StopBits = USART_StopBits_1;
  config.USART_Parity = USART_Parity_No;
  config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  config.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(BASE, &config);
  
  Core::interrupt.irqHandler(CONFIG.irq, true);
  USART_INTConfig(BASE, USART_INT_RDNE, ENABLE);
  USART_Cmd(BASE, ENABLE);
 
  return true;
}
  
/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreUsart::isInit(void){
  return *CONFIG.clock & CONFIG.clockMask;
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
  USART_SetBaudrate(BASE, rate);
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
bool CoreUsart::read(ByteBuffer* byteBuffer, Event* event){
  if(this->readBusy())
    return false;
  
  if(this->getCount() >= byteBuffer->remaining()){
    uint32_t count = this->getCount();
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer->pointer(byteBuffer->position()));
    this->popMult(pointer, count);
    byteBuffer->position(byteBuffer->position() + count);
    
    if(event)
      event->onSerialPortEvent(Event::READ_SUCCESSFUL, byteBuffer);
    
    return true;
  }else if(this->isEmpty()){
    USART_INTConfig(BASE, USART_INT_RDNE, DISABLE);  //memory protected
    this->mPacketRead.init(*byteBuffer, event);
    USART_INTConfig(BASE, USART_INT_RDNE, ENABLE);  //memory protected
    
  }else{
    uint8_t* pointer = static_cast<uint8_t*>(byteBuffer->pointer(byteBuffer->position()));
    
    USART_INTConfig(BASE, USART_INT_RDNE, DISABLE);  //memory protected
    uint32_t count = this->getCount();
    
    byteBuffer->position(byteBuffer->position() + count);
    this->mPacketRead.init(*byteBuffer, event);
    USART_INTConfig(BASE, USART_INT_RDNE, ENABLE);  //memory protected
    
    if(count)
      this->popMult(pointer, count);
  }
 
  return true;
}

/**
 * 
 */
bool CoreUsart::write(ByteBuffer* byteBuffer, Event* event){
  
  if(this->writeBusy())
    return false;
  
  if(!this->mPacketWrite.init(*byteBuffer, event))
    return false;
  
  USART_INTConfig(BASE, USART_INT_TDE, ENABLE);
  
  return true;
}



/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */
void CoreUsart::run(void){
  USART_Type* base = BASE;
  
  if(USART_GetITStatus(base, USART_INT_RDNE) != RESET){
    uint8_t readCache = USART_ReceiveData(base);
    
    if(this->mPacketRead.mPointer && (this->mPacketRead.mLength > this->mPacketRead.mCount)){  //receiver pointer is not null
      /* Read one byte from the receive data register */
      this->mPacketRead.mPointer[this->mPacketRead.mCount] = readCache;  
      ++this->mPacketRead.mCount;

      if(this->mPacketRead.mCount >= this->mPacketRead.mLength){  //receiver is successful
        this->mPacketRead.mStatus = Event::READ_SUCCESSFUL;
        //if(!System::execute(this->mPacketRead))
          this->mPacketRead.run();
      }  
    }else{
      this->insert(&readCache);
    }
  }
  
  //send handle
  if(USART_GetITStatus(base, USART_INT_TDE) != RESET){   
    
    /* Write one byte to the transmit data register */
    USART_SendData(base, this->mPacketWrite.mPointer[this->mPacketWrite.mCount]);
    
    ++this->mPacketWrite.mCount;
    
    if(this->mPacketWrite.mCount >= this->mPacketWrite.mLength){
      /* Disable the USART1 Transmit interrupt */
      USART_INTConfig(base, USART_INT_TDE, DISABLE);
      this->mPacketWrite.mStatus = Event::WRITE_SUCCESSFUL;
      //if(!System::execute(this->mPacketWrite))
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
  Event* event = this->mEvent;
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
bool CoreUsart::Packet::init(ByteBuffer& byteBuffer, Event* event){
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
