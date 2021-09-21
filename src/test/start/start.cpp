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
#include "bsp_arterytek_at32f415/at32f4xx.h"


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

using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreAFIO;
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


CorePin* b[8];
uint8_t lop[2] = {0, 0};

void tmrH(void* attachment){
  lop[0] = (++lop[0] & 0x07);
  b[lop[0]]->setToggle();
}

void tmrH2(void* attachment){
  lop[1] = (++lop[1] & 0x07);
  b[lop[1]]->setToggle();
}

/**
 *
 */
void start(void){
  SystemCoreClockUpdate();
  //mcuf_at32f415_interrupt_priority();
  start_mcuf();
  
  CoreGPIO gb = CoreGPIO(CoreGPIO::REG_GPIOB);
  gb.init();
  
  Core::afio.init();
  Core::afio.remapDEBUG(Core::afio.DEBUG_JTAGDISABLE);
  
  
  
  for(int i=0; i<8; i++){
    b[i] = new CorePin(&gb, i);
    b[i]->setOutput();
    b[i]->setLow();
  }
  
  CoreTimer coreTimer = CoreTimer(CoreTimer::REG_TMR10);
  coreTimer.init();
  ConsumerEvent<void*> event = ConsumerEvent<void*>(tmrH);
  coreTimer.startAtTime(500*1000, 0x00000000, &event);
  
  CoreTimer coreTimer2 = CoreTimer(CoreTimer::REG_TMR1);
  coreTimer2.init();
  ConsumerEvent<void*> event2 = ConsumerEvent<void*>(tmrH2);
  coreTimer2.startAtTime(250*1000, 0x00000000, &event2);
  
  while(1);
  
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
