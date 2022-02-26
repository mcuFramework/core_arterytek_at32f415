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
void CoreSerialPortPacket::clear(void){
  this->mPointer = nullptr;
  this->mByteBuffer = nullptr;
  this->mCount = 0;
  this->mLength = 0;
}

/**
 *
 */
bool CoreSerialPortPacket::init(ByteBuffer& byteBuffer, SerialPortEvent* event){
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
