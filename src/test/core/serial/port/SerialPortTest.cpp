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
using mcuf::io::SerialPortInputStream;
using mcuf::io::OutputStreamBuffer;
using mcuf::io::PrintStream;
using mcuf::io::ByteBuffer;
using mcuf::io::Feture;

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
  ByteBuffer buffer = ByteBuffer(this->mStacker.allocMemoryAlignment32(128));
  
  Feture feture;
  
  while(true){
    
    buffer.clear();
    buffer.put("Enter 8 char: ");
    buffer.flip();
    this->mSerialPortOutputStream->write(&buffer, feture);
    feture.get();
    feture.reset();
    
    buffer.clear();
    buffer.put("Result: ");
    buffer.flip();
    buffer.position(buffer.limit());
    buffer.limit(buffer.limit()+8);
    this->mSerialPortInputStream->read(&buffer, feture);
    feture.get();
    feture.reset();
    
    
    
    buffer.limit(buffer.limit()+1);
    buffer.putByte('\n');
    buffer.flip();
    this->mSerialPortOutputStream->write(&buffer, feture);
    feture.get();
    feture.reset();
    
  }
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::serial::port::SerialPortEvent
 */

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
  Core::gpioc.init();
  Core::gpioc.setFunction(10, false);
  this->mCoreSerialPort = new(this->mStacker) CoreSerialPort(CoreSerialPortReg::REG_UART4, this->mStacker.allocMemoryAlignment32(256));
  this->mCoreSerialPort->init();
  this->mCoreSerialPort->baudrate(9600);
  this->mSerialPortInputStream = new(this->mStacker) SerialPortInputStream(this->mCoreSerialPort);
  this->mSerialPortOutputStream = new(this->mStacker) SerialPortOutputStream(this->mCoreSerialPort);
  
}

/* ****************************************************************************************
 * End of file
 */
