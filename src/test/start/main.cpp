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
#include "periph/TestCoreEXTI.hpp"

/* ****************************************************************************************
 * Using
 */  
using periph::TestCoreEXTI;
 
using start::Main;
using mcuf::lang::System;
using mcuf::lang::Memory;
using mcuf::lang::Thread;
using mcuf::lang::managerment::MemoryManager;
using mcuf::function::Runnable;
using mcuf::function::ConsumerEvent;

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
  
  TestCoreEXTI* testCoreEXTI1 = new TestCoreEXTI(*this->mLED[1], CoreEXTI::REG_EXTI1, TestCoreEXTI::TESTMODE_FALL);
  testCoreEXTI1->start();
  
  TestCoreEXTI* testCoreEXTI2 = new TestCoreEXTI(*this->mLED[2], CoreEXTI::REG_EXTI2, TestCoreEXTI::TESTMODE_RISE);
  testCoreEXTI2->start();
  
  TestCoreEXTI* testCoreEXTI3 = new TestCoreEXTI(*this->mLED[3], CoreEXTI::REG_EXTI3, TestCoreEXTI::TESTMODE_ALL);
  testCoreEXTI3->start();
  
  
  while(1){
    this->mLED[0]->setToggle();
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
  Core::gpiob.init();
  Core::gpioc.init();
  Core::afio.init();
  Core::afio.remapDEBUG(Core::afio.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLED[i] = new CorePin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
  for(int i=0; i<8; i++){
    this->mEXTI[i] = new CorePin(&Core::gpioc, i);
    this->mEXTI[i]->setInput();
    this->mEXTI[i]->pinMode(this->mEXTI[i]->PinMode_Pullup);
    Core::afio.remapEXTI(Core::afio.EXTI_PC, i);
  }
}
 
/* ****************************************************************************************
 * End of file
 */ 
