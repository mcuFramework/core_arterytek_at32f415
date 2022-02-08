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


/* ****************************************************************************************
 * Using
 */  


using mcuf::function::Runnable;
using mcuf::function::ConsumerEvent;

using namespace start;
using namespace mcuf::io;
using namespace mcuf::hw;
using namespace mcuf::hal;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace mcuf::function;
using namespace core::arterytek::at32f415;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using namespace core::arterytek::at32f415::timer;
using namespace mcuf::hal::timer;


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
Main::Main(Memory& memory, Memory& stacker) construct Thread(memory), 
  mStacker(stacker){

}

/**
 * Destruct.
 */
Main::~Main(void){
  
}

/* ****************************************************************************************
 * Public Method <Static>
 */

/**
 * 
 */
void Main::onTimerEvent(TimerStatus status){
  this->mLED[1]->setToggle();
}

/* ****************************************************************************************
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 * 
 */
void Main::run(void){
  this->initGPIO();
  
  CoreTimer timer = CoreTimer(CoreTimerReg::REG_TMR3);
  timer.init();
  
  while(true){
    this->mLED[0]->setHigh();
    this->delay(500);
    this->mLED[0]->setLow();
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
void Main::initGPIO(void){
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; ++i){
    this->mLED[i] = new(this->mStacker.allocAlignment32(sizeof(CoreGeneralPin))) CoreGeneralPin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
}

/* ****************************************************************************************
 * End of file
 */ 
