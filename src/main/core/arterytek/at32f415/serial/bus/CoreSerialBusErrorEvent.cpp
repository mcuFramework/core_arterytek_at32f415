/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
 
#include "core/arterytek/at32f415/serial/bus/CoreSerialBusErrorEvent.h"

//-----------------------------------------------------------------------------------------
#include "bsp_arterytek_at32f415.h"
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/serial/bus/CoreSerialBus.h"

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<char>(this->mBase.mRegister))
#define CONFIG                   (CoreSerialBus::mConfig[REGNUMB])
#define BASE                     ((i2c_type*)CONFIG.mBase)

/* ****************************************************************************************
 * Using
 */

using core::arterytek::at32f415::serial::bus::CoreSerialBusErrorEvent;

//-----------------------------------------------------------------------------------------
using namespace mcuf::hal::serial::bus;

//-----------------------------------------------------------------------------------------
using core::arterytek::at32f415::serial::bus::CoreSerialBus;
using mcuf::io::ByteBuffer;
using mcuf::lang::System;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Serial Bus Error Event object
 * 
 * @param base 
 */
CoreSerialBusErrorEvent::CoreSerialBusErrorEvent(CoreSerialBus& base) construct 
  mBase(base){
}

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
void CoreSerialBusErrorEvent::run(void){
  ByteBuffer* byteBuffer = this->mBase.mByteBuffer;
  ByteBuffer* byteBufferNext = this->mBase.mByteBufferNext;
  SerialBusEvent* event = this->mBase.mEvent;
  SerialBusStatus status = this->mBase.mStatus;
  void* attachment = this->mBase.mAttachment;
  
  byteBuffer->position(byteBuffer->position() + this->mBase.mCount);
  
  int result = this->mBase.mLength - this->mBase.mCount;
  
  this->mBase.handlerClear();
  
  if(event){
    event->onSerialBusEvent(status, result ,attachment);
    
    if(byteBufferNext){
      result = this->mBase.mByteBufferNext->remaining();
      this->mBase.mByteBufferNext = nullptr;
      event->onSerialBusEvent(SerialBusStatus::READ_FAIL, result ,attachment);
    }
  }
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreSerialBusErrorEvent::interruptEvent(void){
  i2c_type* base = BASE;
  
  i2c_interrupt_enable(base, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, FALSE); 
  
  if(this->mBase.mDirect == 0)
    this->mBase.mStatus = SerialBusStatus::READ_FAIL;
  
  else
    this->mBase.mStatus = SerialBusStatus::WRITE_FAIL;
  
  if(!System::execute(*this))
    this->run();
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
