/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

//__asm(".global __use_no_semihosting_swi");
//__asm(".global __use_no_semihosting");

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "start/Main.h"
#include "core/analog/package-info.h"
#include "core/serial/package-info.h"
#include "core/counter/package-info.h"
#include "tool/package-info.h"

/* ****************************************************************************************
 * Using
 */  
using namespace start;

using namespace arterytek::at32f415;
using namespace arterytek::at32f415::general;
using namespace arterytek::at32f415::serial;

using namespace core::analog::input;
using namespace core::counter::pulse;
using namespace core::serial::port;
using namespace core::serial::periph;
using namespace tool;

using namespace mcuf::io;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace hal::general;
using namespace hal::serial;

//-----------------------------------------------------------------------------------------
using mcuf::function::Runnable;
using mcuf::lang::Memory;

using hal::general::GeneralPinMode;

/* ****************************************************************************************
 * Namespace
 */  

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Operator Method
 */

BoardPeriph* boardPeriph;
SystemConsole* console;

/**
 * Construct.
 */
Main::Main(Memory& memory, Memory& stacker) : Thread(memory), mStacker(stacker){
  boardPeriph = new(this->mStacker) BoardPeriph();
  console = new(this->mStacker) SystemConsole();
}

/**
 * Destruct.
 */
Main::~Main(void){
}

/* ****************************************************************************************
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 * 
 */
void Main::run(void){

  //Runnable* runnable = new(this->mStacker) PulseWidthTest(this->mStacker);
  //Runnable* runnable = new(this->mStacker) CoreAnalogInputTest(this->mStacker);
  //Runnable* runnable = new(this->mStacker) SerialPortTest(this->mStacker);
  //Runnable* runnable = new(this->mStacker) SerialPeriphTest(this->mStacker);
  
  //runnable->run();
  
  console->out().print("start\n");
  
  while(true){
    boardPeriph->led[0].setToggle();
    this->delay(250);
    if(console->in().avariable() > 0){
      console->out().print("receiver:");
      console->out().println(console->in());
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

/* ****************************************************************************************
 * End of file
 */ 
