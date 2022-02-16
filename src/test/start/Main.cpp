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
#include "core/serial/package-info.h"
#include "tool/package-info.h"

/* ****************************************************************************************
 * Using
 */  
using namespace start;
using namespace core::serial::port;
using namespace tool;

//-----------------------------------------------------------------------------------------
using mcuf::function::Runnable;
using mcuf::lang::Memory;

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
Main::Main(Memory& memory, Memory& stacker) construct Thread(memory), mStacker(stacker){
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
  Console* console = new(this->mStacker) Console();
  BoardPeriph* boardPerilh = new(this->mStacker) BoardPeriph();
  
  int i=0;
  while(true){
    console->out().print("value: ");
    console->out().println(i++);
    this->delay(100);
    boardPerilh->led[i%8].setToggle();
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
