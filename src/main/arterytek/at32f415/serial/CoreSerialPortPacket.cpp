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
#include "arterytek/at32f415/serial/CoreSerialPortPacket.h"

/* ****************************************************************************************
 * Macro
 */  

/* ****************************************************************************************
 * Using
 */  
using namespace arterytek::at32f415::serial;

//-----------------------------------------------------------------------------------------
using mcuf::io::ByteBuffer;
using hal::serial::SerialPortEvent;
using hal::serial::SerialPortStatus;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */
/**
 * Construct.
 */
CoreSerialPortPacket::CoreSerialPortPacket(void){
  return;
}

/**
 * Destruct.
 */
CoreSerialPortPacket::~CoreSerialPortPacket(void){
  return;
}

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
  this->mLength = static_cast<uint16_t>(byteBuffer.remaining());
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
  this->mLength = static_cast<uint16_t>(length);
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
