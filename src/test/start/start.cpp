/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include <stdint.h>

#include "mcuf.h"
#include "core_arterytek_at32f415.h"


/* ****************************************************************************************
 * Macro
 */  
#define HEAP_SIZE_KB 24

/* ****************************************************************************************
 * Using
 */  

using mcuf::lang::System;
using mcuf::lang::Memory;
using mcuf::lang::managerment::MemoryManager;
using mcuf::function::ConsumerEvent;

using core::arterytek::at32f415::CorePin;
using core::arterytek::at32f415::CoreGPIO;
using core::arterytek::at32f415::CoreTimer;

/* ****************************************************************************************
 * Variable
 */ 

static struct{
	uint32_t heapBuffer[(HEAP_SIZE_KB*256)];
	uint8_t memoryManagerMemory[sizeof(MemoryManager)];
}start_memory;


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
void start_mcuf(){
  Memory memory = Memory(start_memory.heapBuffer, sizeof(start_memory.heapBuffer));
	MemoryManager* memoryManager = new(start_memory.memoryManagerMemory) MemoryManager(memory);
	System::component.memoryManager(memoryManager);
}


/**
 *
 */
void start(void){
  start_mcuf();
  
  
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
