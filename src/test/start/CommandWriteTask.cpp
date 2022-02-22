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
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

#include "start/CommandWriteTask.hpp"

const uint8_t data_connect[36] = {
  0x52, 0x43, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x0D, 0x0A
};

/* ****************************************************************************************
 * Using
 */  
using start::CommandWriteTask;
using namespace core::arterytek::at32f415;
using namespace mcuf::lang;
using namespace mcuf::io::channel;

/* ****************************************************************************************
 * Macro
 */
 
/* ****************************************************************************************
 * Variable
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * Construct.
 */
CommandWriteTask::CommandWriteTask(CoreUSART& usart){
  this->mUSART = & usart;
  this->mByteBuffer = new HeapByteBuffer(128);
  this->busy = false;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Consumer<mcuf::io::channel::ByteBuffer&>
 */

/** 
 *
 */
void CommandWriteTask::accept(ByteBuffer& byteBuffer){
  this->busy = false;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
bool CommandWriteTask::writeConnect(void){
  if(this->busy)
    return false;
  
  if(this->mUSART->writeBusy())
    return false;
  
  this->busy = true;
  
  this->mByteBuffer->reset();
  for(int i=0; i<36; i++){
    this->mByteBuffer->putByte(data_connect[i]);
  }
  
  this->mByteBuffer->flip();
  this->mUSART->write(*this->mByteBuffer, this);

  return true;
}
  
/**
 *
 */
bool CommandWriteTask::writeData(void){
  if(this->busy)
    return false;
  
  if(this->mUSART->writeBusy())
    return false;
  
  this->busy = true;
  
  this->mByteBuffer->reset();
  this->mByteBuffer->putByte(0x52);
  this->mByteBuffer->putByte(0x43);
  this->mByteBuffer->putByte(0x03);
  
  for(int i=0; i<10; i++){
    uint8_t b0 = this->mData[i]>>16;
    uint8_t b1 = this->mData[i]>>8;
    uint8_t b2 = this->mData[i];
    this->mByteBuffer->putByte(b0);
    this->mByteBuffer->putByte(b1);
    this->mByteBuffer->putByte(b2);
  }
  
  uint32_t checksum = 0;
  uint8_t* checksunStart = this->mByteBuffer->lowerArray();
  for(int i=0; i<33; i++){
    checksum += checksunStart[i];
  }
  
  this->mByteBuffer->putByte(checksum);
  this->mByteBuffer->putByte(0x0D);
  this->mByteBuffer->putByte(0x0A);
  this->mByteBuffer->flip();

  this->mUSART->write(*this->mByteBuffer, this);
  return true;
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
