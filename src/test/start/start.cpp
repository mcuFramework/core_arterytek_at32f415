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
#include "cmsis_rtos/cmsis_os2.h"
#include "cmsis_rtos/rtx_os.h"


#include "mcuf.h"
#include "core_arterytek_at32f415.h"
#include "bsp_arterytek_at32f415/at32f4xx.h"


/* ****************************************************************************************
 * Macro
 */  
#define HEAP_SIZE_KB 16

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




void thread_a(void* args){
  while(1){
    b[0]->setToggle();
    osDelay(500);
  }
}


void thread_b(void* args){
  while(1){
    b[1]->setToggle();
    osDelay(250);
  }
}


static osRtxThread_t thread_mem_a;
static osRtxThread_t thread_mem_b;
static uint64_t stack_a[32];
static uint64_t stack_b[32];


/**
 *
 */
void start(void){
  SystemCoreClockUpdate();
  //mcuf_at32f415_interrupt_priority();
  start_mcuf();
  
  
  Core::afio.init();
  Core::afio.remapDEBUG(Core::afio.DEBUG_JTAGDISABLE);
  Core::gpiob.init();
  
  
  
  for(int i=0; i<8; i++){
    b[i] = new CorePin(&Core::gpiob, i);
    b[i]->setOutput();
    b[i]->setLow();
  }
  
  
  
  osKernelInitialize();
  
  
  osThreadAttr_t attr;
  
  attr.cb_mem = &thread_mem_a;
  attr.cb_size = sizeof(thread_mem_a);
  attr.stack_mem = &stack_a[0];
  attr.stack_size = sizeof(stack_a);
  attr.attr_bits = osThreadDetached;
  attr.priority = osPriorityNormal;
  attr.reserved = 0;
  
  
  
  
  osThreadNew(thread_a, nullptr, &attr);
  
  //osThreadNew(thread_b, nullptr, nullptr);
  
  
  osKernelStart();
  for(;;);
  
  
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
