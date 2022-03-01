/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
 
//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/serial/port/CoreSerialPortPacket.h"

/* ****************************************************************************************
 * Macro
 */  

/* ****************************************************************************************
 * Using
 */  
using namespace core::arterytek::at32f415::serial::port;

//-----------------------------------------------------------------------------------------
using mcuf::io::ByteBuffer;
using mcuf::hal::serial::port::SerialPortEvent;
using mcuf::hal::serial::port::SerialPortStatus;

/* ****************************************************************************************
 * Variable <Static>
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
 * Public Method <Override> mcuf::function::Runnable
 */

void CoreSerialPortPacket::run(void){
  
  ByteBuffer* byteBuffer = this->mByteBuffer;
  SerialPortEvent* event = this->mEvent;
  SerialPortStatus status = this->mStatus;
  byteBuffer->position(byteBuffer->position() + this->mCount);
  void* attachment = this->mAttachment;
  int result = this->mLength - this->mCount;
  this->clear();
  
  if(event)
    event->onSerialPortEvent(status, result ,attachment);
  
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreSerialPortPacket::clear(void){
  this->mPointer = nullptr;
  this->mByteBuffer = nullptr;
  this->mCount = 0;
  this->mLength = 0;
}

/**
 *
 */
bool CoreSerialPortPacket::init(ByteBuffer& byteBuffer, void* attachment, SerialPortEvent* event){
  if(this->isExist())
    return false;
  
  if(!byteBuffer.hasRemaining())
    return false;
  
  this->mByteBuffer = &byteBuffer;
  this->mEvent = event;
  this->mLength = byteBuffer.remaining();
  this->mCount = 0;
  this->mPointer = static_cast<uint8_t*>(byteBuffer.pointer(byteBuffer.position()));
  this->mAttachment = attachment;
  
  return true;
}

/**
 *
 */
bool CoreSerialPortPacket::init(void* pointer, int length, void* attachment, SerialPortEvent* event){
  if(this->isExist())
    return false;
  
  this->mByteBuffer = nullptr;
  this->mEvent = event;
  this->mLength = length;
  this->mCount = 0;
  this->mPointer = static_cast<uint8_t*>(pointer);
  this->mAttachment = attachment;
  
  return true;
}

/**
 *
 */
bool CoreSerialPortPacket::isExist(void){
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
 * Private Method
 */
 
/* ****************************************************************************************
 * End of file
 */ 
