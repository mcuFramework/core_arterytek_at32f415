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
#include "start/Main.hpp"
#include "start/SpeedReader.hpp"
#include "start/CommandWriteTask.hpp"


/* ****************************************************************************************
 * Using
 */  


using mcuf::lang::managerment::MemoryManager;
using mcuf::function::Runnable;
using mcuf::function::ConsumerEvent;

using namespace start;
using namespace mcuf::io::channel;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace mcuf::function;
using namespace core::arterytek::at32f415;



/* ****************************************************************************************
 * Namespace
 */  

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Operator Method
 */

/**
 * Construct.
 */
Main::Main(void) construct Thread("mainThread"){
  this->mStatus = 0;
}

/**
 * Destruct.
 */
Main::~Main(void){
  
}

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override>
 */

/**
 *
 */
void Main::run(void){
  this->initGPIO();
  while(1){
    this->mLED[0]->setToggle();
    this->delay(1000);
  }
}

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

/**
 *
 */
void Main::initGPIO(void){
  Core::gpiob.init();
  Core::gpioc.init();
  Core::afio.init();
  Core::afio.remapDEBUG(Core::afio.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLED[i] = new CorePin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
  Core::gpioc.configOutput(10, CoreGPIO::OutputMode_50M, false, true, true);
}

/**
 *
 */
void Main::throwTest(int i) throw(Throwable){
  
  this->mLED[i]->setHigh();
}
 
/* ****************************************************************************************
 * End of file
 */ 
