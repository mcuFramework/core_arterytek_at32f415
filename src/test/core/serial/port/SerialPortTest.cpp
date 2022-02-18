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

//-----------------------------------------------------------------------------------------
#include "core/serial/port/SerialPortTest.h"

/* ****************************************************************************************
 * Macro
 */
#define LED_ERROR() this->mBlinker.mPin = &this->mBoardPeriph->led[7];
#define LED_SUCCESSFUL() this->mBlinker.mPin = &this->mBoardPeriph->led[6];

#define PACKAGE_SIZE 64
const char cmd_ack[] = {0x5E, 0x01, 0x5F, 0x00};
const char cmd_error[] = {0x62, 0x01, 0x63, 0x00};
const char cmd_exception[] = {0x62, 0x02, 0x60, 0x00};

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------
using namespace tool;
using namespace mcuf::hal::serial::port;

//-----------------------------------------------------------------------------------------
using core::serial::port::SerialPortTest;
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using core::arterytek::at32f415::general::port::CoreGeneralPort;
using core::arterytek::at32f415::general::port::OutputMode;
using core::arterytek::at32f415::serial::port::CoreSerialPort;
using core::arterytek::at32f415::serial::port::CoreSerialPortReg;
using mcuf::util::Stacker;
using mcuf::lang::Memory;
using mcuf::lang::System;

using mcuf::io::SerialPortOutputStream;
using mcuf::io::OutputStreamBuffer;
using mcuf::io::PrintStream;
using mcuf::io::ByteBuffer;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
SerialPortTest::SerialPortTest(Stacker& stacker) construct mStacker(stacker){
  return;
}

/**
 *
 */
SerialPortTest::~SerialPortTest(void){
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::run
 */

/**
 * @brief
 * 
 */
void SerialPortTest::run(void){
  this->init();
  this->mStage = 0;
  this->mPackageNumber = 0;
  this->mBlinker.mPin = &this->mBoardPeriph->led[0];
  System::scheduleAtFixedRate(this->mBlinker, 100, 100);
  
  while(true){
    if(!this->mBoardPeriph->wakeup.value()){
      this->mBlinker.mPin = &this->mBoardPeriph->led[1];
      mSelectMode = 0;
      break;
    }
    
    if(!this->mBoardPeriph->function.value()){
      this->mBlinker.mPin = &this->mBoardPeriph->led[2];
      mSelectMode = 1;
      break;
    }
  }
  
  this->mBoardPeriph->led[0].setLow();
  this->beginRead(9);
  
  while(true){
    this->delay(1000);
  }
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::serial::port::SerialPortEvent
 */
  
/**
 * @brief 
 * 
 * @param status 
 * @param byteBuffer 
*/

void SerialPortTest::onSerialPortEvent(SerialPortStatus status, ByteBuffer* byteBuffer){
  if(status == SerialPortStatus::READ_SUCCESSFUL){
    if(this->mStage == 0){
      this->readCommand(byteBuffer);
    
    }else if(this->mStage == 1){
      this->readPackage(byteBuffer);
    }
    
  }else{
    LED_ERROR();
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

/**
 *
 */
void SerialPortTest::init(void){
  this->mBoardPeriph = new(this->mStacker) BoardPeriph();
  this->mConsole = new(this->mStacker) Console();
  
  this->mReceiver = new(this->mStacker) ByteBuffer(this->mStacker.allocMemoryAlignment32(2112));
}

/**
 *
 */
void SerialPortTest::beginRead(int len){
  this->mReceiver->clear();
  this->mReceiver->limit(len);
  this->mConsole->mCoreSerialPort->read(this->mReceiver, this);
}

/**
 *
 */
void SerialPortTest::readCommand(ByteBuffer* byteBuffer){
  char command;
  int address;
  int len;
    
  byteBuffer->position(0);
  byteBuffer->getByte(command);
  byteBuffer->getIntMsb(address);
  byteBuffer->getIntMsb(len);
      
      
     
  if(command != 0x72){
    LED_ERROR();
    this->mConsole->out().print(cmd_error);
  }else{
    this->mConsole->out().print(cmd_ack);
    this->mStage = 1;
    this->mLength = len;
    this->mPackageNumber = 0;
    
    int readSize = 1;
    int alreadyRead = PACKAGE_SIZE * (this->mPackageNumber + 1);
    
    if((alreadyRead + PACKAGE_SIZE) > this->mLength)
      readSize += this->mLength%PACKAGE_SIZE;
    
    else
      readSize += PACKAGE_SIZE;
    
    this->beginRead(readSize);
  }
}

/**
 *
 */
void SerialPortTest::readPackage(ByteBuffer* byteBuffer){
  int readSize = 1;
  int alreadyRead = PACKAGE_SIZE * (this->mPackageNumber + 1);
  
  if((alreadyRead + PACKAGE_SIZE) > this->mLength)
    readSize += this->mLength%PACKAGE_SIZE;
  
  else
    readSize += PACKAGE_SIZE;
  
  
  if(this->mPackageNumber == 1){
    if(this->mSelectMode == 1){
      this->mSelectMode = 0;
      this->beginRead(readSize);
      this->mConsole->out().print(cmd_exception);
      return;
    }
  }
  
  ++this->mPackageNumber;
  
  if(alreadyRead >= this->mLength){
    LED_SUCCESSFUL();
  }else{
    this->beginRead(readSize);
  }
  
  this->mConsole->out().print(cmd_ack);
  
  return;
}

/* ****************************************************************************************
 * End of file
 */
