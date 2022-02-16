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

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

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
  
  this->mSerialPort = new(this->mStacker) CoreSerialPort(CoreSerialPortReg::REG_USART2, 
                                                         this->mStacker.allocMemoryAlignment32(64));
  
  this->mSerialPort->init();
  this->mOutputStream = new(this->mStacker) SerialPortOutputStream(this->mSerialPort);
  this->mOutputStreamBuffer = new(this->mStacker) OutputStreamBuffer(this->mOutputStream, this->mStacker.allocMemoryAlignment32(512));
  this->mPrintStream = new(this->mStacker) PrintStream(this->mOutputStreamBuffer, this->mStacker.allocMemoryAlignment32(128));
  
  while(true){
    for(int i=0; i<8; ++i){
      this->mLed[i]->setToggle();
      this->delay(500);
      this->mPrintStream->println(123);
      this->mPrintStream->println(456);
      this->mPrintStream->println(789);
      this->mPrintStream->format("hello");
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

void SerialPortTest::init(void){
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLed[i] = new(this->mStacker) CoreGeneralPin(&Core::gpiob, i);
    this->mLed[i]->setOutput();
    this->mLed[i]->setLow();
  }
  
  Core::gpioa.configOutput(2, OutputMode::SPEED_50M, false, true, true);
}

/* ****************************************************************************************
 * End of file
 */
