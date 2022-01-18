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
#include "mcuf.h"
#include "core_arterytek_at32f415.h"
#include "start/Main.hpp"

/* ****************************************************************************************
 * Using
 */  
using mcuf::lang::System;
using mcuf::lang::Memory;
using mcuf::util::Stacker;
using start::Main;

/* ****************************************************************************************
 * Extern
 */
extern "C" void SystemCoreClockUpdate(void);

/* ****************************************************************************************
 * Variable <Static>
 */
static Main* userMain;
static uint32_t mainMemory[(sizeof(Main)+3)/4];
static uint64_t mainStack[2048/8];
static uint64_t stackerMemory[3072];


/* ****************************************************************************************
 * Construct Method
 */

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

/**
 *
 */
extern "C" int main(void){
  SystemCoreClockUpdate();
  if(1){
    Memory stack = Memory(mainStack, sizeof(mainStack));
    Memory stacker = Memory(stackerMemory, sizeof(stackerMemory));
    userMain = new(mainMemory)Main(stack, stacker);
  }
  
  System::start(userMain);
}


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
