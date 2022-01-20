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


/* ****************************************************************************************
 * Using
 */  


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
Main::Main(Memory& memory, Memory& stacker) construct Thread(memory), 
  mStacker(stacker){
    
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
  
  CoreUsart uart2 = CoreUsart(CoreUsart::REG_USART2, this->mStacker.allocMemory(128));
  uart2.init();
  
  ByteBuffer b = ByteBuffer(this->mStacker.allocMemory(64));
  String s = String(this->mStacker.allocMemory(64));
  
  
  while(true){
    b.reset();
    b.putFormat("clock:%d\n", Core::getSystemCoreClock());
    b.flip();
    this->mLED[0]->setHigh();
    this->delay(500);
    this->mLED[0]->setLow();
    this->delay(500);
    uart2.write(&b, nullptr);
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
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLED[i] = new(this->mStacker.allocAlignment32(sizeof(CorePin))) CorePin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
  
  Core::gpioa.configOutput(2, CoreGpio::OutputMode_50M, false, true, true);
  
}

/* ****************************************************************************************
 * End of file
 */ 
