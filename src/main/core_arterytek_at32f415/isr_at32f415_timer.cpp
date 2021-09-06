/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"
#include "core/arterytek/at32f415/bsp/at32f4xx.h"
#include "core/arterytek/at32f415/CoreTimer.hpp"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Struct
 */

/* ****************************************************************************************
 * Static Variable
 */
 
/* ****************************************************************************************
 * Variable
 */

static core::arterytek::at32f415::CoreTimer* isr_at32f415_tmr[7] = {0, 0, 0, 0, 0, 0, 0};

/* ****************************************************************************************
 * List
 */
 
/**
 * Inline function list
 */
 
/**
 * Static function list
 */

/* ****************************************************************************************
 * Inline Function
 */

/* ****************************************************************************************
 * Static Function
 */

/* ****************************************************************************************
 * Function
 */

/**
 * 
 */
core::arterytek::at32f415::CoreTimer* isr_at32f415_tmr_get(void* base){
  switch((uint32_t)base){
    case TMR2_BASE:
      return isr_at32f415_tmr[0];
    
    case TMR3_BASE:
      return isr_at32f415_tmr[1];

    case TMR4_BASE:
      return isr_at32f415_tmr[2];
    
    case TMR5_BASE:
      return isr_at32f415_tmr[3];
    
    case TMR9_BASE:
      return isr_at32f415_tmr[4];
    
    case TMR10_BASE:
      return isr_at32f415_tmr[5];
    
    case TMR11_BASE:
      return isr_at32f415_tmr[6];
    
    default:
      THROW_ERROR("out of enum index");
  }
  
  return nullptr;
}

/**
 * 
 */
void isr_at32f415_tmr_reg(void* base, core::arterytek::at32f415::CoreTimer* mem){
  switch((uint32_t)base){
    case TMR2_BASE:
      isr_at32f415_tmr[0] = mem;
      return;
    
    case TMR3_BASE:
      isr_at32f415_tmr[1] = mem;
      return;
    
    case TMR4_BASE:
      isr_at32f415_tmr[2] = mem;
      return;
    
    case TMR5_BASE:
      isr_at32f415_tmr[3] = mem;
      return;
    
    case TMR9_BASE:
      isr_at32f415_tmr[4] = mem;
      return;
    
    case TMR10_BASE:
      isr_at32f415_tmr[5] = mem;
      return;
    
    case TMR11_BASE:
      isr_at32f415_tmr[6] = mem;
      return;
    
    default:
      THROW_ERROR("out of enum index");
  }
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr2(void){  //isr TMR2
  isr_at32f415_tmr[0]->interruptHandle();
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr3(void){  //isr TMR3
  isr_at32f415_tmr[1]->interruptHandle();
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr4(void){  //isr TMR4
  isr_at32f415_tmr[2]->interruptHandle();
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr5(void){ //isr TMR5
  isr_at32f415_tmr[3]->interruptHandle();
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr9(void){ //isr TMR9
  isr_at32f415_tmr[4]->interruptHandle();
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr10(void){  //isr TMR10
  isr_at32f415_tmr[5]->interruptHandle();
}

/**
 * 
 */
extern "C" void isr_at32f415_tmr11(void){  //isr TMR11
  isr_at32f415_tmr[6]->interruptHandle();
}

/* ****************************************************************************************
 * End of file
 */ 
