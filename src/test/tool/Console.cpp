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

using arterytek::at32f415::Core;
using arterytek::at32f415::CoreIomux;
using arterytek::at32f415::general::CoreGeneralPin;
using arterytek::at32f415::general::CoreGeneralPort;
using arterytek::at32f415::general::OutputMode;
using arterytek::at32f415::serial::CoreSerialPort;
using arterytek::at32f415::serial::CoreSerialPortReg;
using mcuf::util::Stacker;
using mcuf::lang::Memory;

using mcuf::io::OutputStreamHandler;
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
Console::Console(void) : 
mCoreSerialPort(CoreSerialPortReg::REG_UART4, Memory(this->mCoreSerialPortMemory, sizeof(this->mCoreSerialPortMemory))),
mOutputStreamHandler(this->mCoreSerialPort, Memory(this->mOutputStreamHandlerMemory, sizeof(this->mOutputStreamHandlerMemory))),
mPrintStream(this->mOutputStreamHandler, Memory(this->mPrintStreamMemory, sizeof(this->mPrintStreamMemory))){

  this->mCoreSerialPort.init();
  this->mCoreSerialPort.baudrate(128000);
  
  Core::gpioc.setFunction(10, false);
  return;
}

/**
 *
 */
Console::~Console(void){
  this->mCoreSerialPort.deinit();
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