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
#include "core/analog/input/CoreAnalogInputTest.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------
using namespace tool;

//-----------------------------------------------------------------------------------------
using core::analog::input::CoreAnalogInputTest;

using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreIomux;
using core::arterytek::at32f415::analog::input::CoreAnalogInputPort;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using core::arterytek::at32f415::general::port::CoreGeneralPort;
using core::arterytek::at32f415::general::port::OutputMode;

using mcuf::util::Stacker;
using mcuf::lang::Memory;
using mcuf::lang::System;

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
CoreAnalogInputTest::CoreAnalogInputTest(Stacker& stacker) construct mStacker(stacker){
  return;
}

/**
 *
 */
CoreAnalogInputTest::~CoreAnalogInputTest(void){
  return;
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
void CoreAnalogInputTest::run(void){
  this->init();
  
  this->mCoreAnalogInputPort->init();
  
  for(int i=0; i<16; ++i)
    this->mConsole->out().format("%04d\t", i);
  
  this->mConsole->out().println();
  
  while(true){
    for(int i=0; i<16; ++i){
      this->mConsole->out().format("%04d\t", this->mCoreAnalogInputPort->read(i));
    }
    
    this->mConsole->out().println();
    
    this->delay(500);
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
void CoreAnalogInputTest::init(void){
  this->mConsole = new(this->mStacker) Console();
  this->mCoreAnalogInputPort = new(this->mStacker) CoreAnalogInputPort();
  
  Core::gpioa.init();
  Core::gpioa.setAnalog(0);
  Core::gpioa.setAnalog(1);
  Core::gpioa.setAnalog(2);
  Core::gpioa.setAnalog(3);
  Core::gpioa.setAnalog(4);
  Core::gpioa.setAnalog(5);
  Core::gpioa.setAnalog(6);
  Core::gpioa.setAnalog(7);
  
  Core::gpiob.init();
  Core::gpiob.setAnalog(0);
  Core::gpiob.setAnalog(1);
  
  Core::gpioc.init();
  Core::gpioc.setAnalog(0);
  Core::gpioc.setAnalog(1);
  Core::gpioc.setAnalog(2);
  Core::gpioc.setAnalog(3);
  Core::gpioc.setAnalog(4);
  Core::gpioc.setAnalog(5);
}

/* ****************************************************************************************
 * End of file
 */
