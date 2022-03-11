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
#include "tool/Console.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using tool::Console;

using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreIomux;
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
Console::Console(void){
  Stacker stacker = Stacker(Memory(this->mDynamicMemory, sizeof(this->mDynamicMemory)));
  
  this->mCoreSerialPort = new(stacker) 
    CoreSerialPort(CoreSerialPortReg::REG_UART4, Memory(this->mCoreSerialPortMemory, sizeof(this->mCoreSerialPortMemory)));
  
  this->mCoreSerialPort->init();
  
  this->mCoreSerialPort->baudrate(128000);
  
  this->mSerialPortOutputStream = new(stacker)
    SerialPortOutputStream(*this->mCoreSerialPort);
  
  this->mOutputStreamBuffer = new(stacker)
    OutputStreamBuffer(*this->mSerialPortOutputStream, Memory(this->mOutputStreamBufferMemory, sizeof(this->mOutputStreamBufferMemory)));
  
  this->mPrintStream = new(stacker)
    PrintStream(*this->mOutputStreamBuffer, Memory(this->mPrintStreamMemory, sizeof(this->mPrintStreamMemory)));
  
  Core::gpioc.init();
  Core::iomux.remapSWDIO(CoreIomux::MapSWDIO::JTAGDISABLE);
  Core::gpioc.setFunction(10, false);
  return;
}

/**
 *
 */
Console::~Console(void){
  this->mCoreSerialPort->deinit();
  
  this->mPrintStream->~PrintStream();
  this->mOutputStreamBuffer->~OutputStreamBuffer();
  this->mSerialPortOutputStream->~SerialPortOutputStream();
  this->mCoreSerialPort->~CoreSerialPort();
  
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override>
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

/* ****************************************************************************************
 * End of file
 */
