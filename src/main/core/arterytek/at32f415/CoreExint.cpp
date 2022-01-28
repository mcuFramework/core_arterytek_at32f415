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
#include "bsp_arterytek_at32f415/at32f415.h"
#include "core/arterytek/at32f415/Core.hpp"
#include "core/arterytek/at32f415/CoreExint.hpp"
#include "core/arterytek/at32f415/CoreInterrupt.hpp"
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      struct ConfigCoreExint{
        CoreInterrupt::Irq irq;
      }const configCoreExint[16]{
        {CoreInterrupt::IRQ_EXINT0},
        {CoreInterrupt::IRQ_EXINT1},
        {CoreInterrupt::IRQ_EXINT2},
        {CoreInterrupt::IRQ_EXINT3},
        {CoreInterrupt::IRQ_EXINT4},
        {CoreInterrupt::IRQ_EXINT5},
        {CoreInterrupt::IRQ_EXINT6},
        {CoreInterrupt::IRQ_EXINT7},
        {CoreInterrupt::IRQ_EXINT8},
        {CoreInterrupt::IRQ_EXINT9},
        {CoreInterrupt::IRQ_EXINT10},
        {CoreInterrupt::IRQ_EXINT11},
        {CoreInterrupt::IRQ_EXINT12},
        {CoreInterrupt::IRQ_EXINT13},
        {CoreInterrupt::IRQ_EXINT14},
        {CoreInterrupt::IRQ_EXINT15},
      };
      
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using mcuf::hal::EdgeTrigger;
using mcuf::hal::EdgeTriggerEvent;
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreExint;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                   (configCoreExint[this->mRegister])
#define BASE                     (EXINT)

/* ****************************************************************************************
 * Variable <Static>
 */
uint16_t CoreExint::channelEnable = 0x0000U;
uint16_t CoreExint::channelMode = 0x0000U;
uint16_t CoreExint::channelLevel = 0x0000U;

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
CoreExint::CoreExint(Register reg){
  this->mRegister = reg;
}

/**
 *
 */
CoreExint::~CoreExint(void){
  this->deinit();
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::Base
 */

/**
 * uninitialze hardware.
 */
bool CoreExint::deinit(void){
	if(!(CoreExint::channelEnable & (1 << this->mRegister)))
		return false;
  
  CoreExint::channelEnable &= ~(1 << this->mRegister);
  Core::interrupt.irqEnable(CONFIG.irq, false);
  Core::interrupt.setHandler(CONFIG.irq, nullptr);  
  this->periphReset();
  return true;
}

/**
 * initialze hardware;
 */
bool CoreExint::init(void){
  if(CoreExint::channelEnable & (1 << this->mRegister))
    return false;
  
  CoreExint::channelEnable |= (1 << this->mRegister);
  this->periphReset();
  Core::interrupt.setHandler(CONFIG.irq, this);
  Core::interrupt.irqEnable(CONFIG.irq, true);
  
  return true;
}
  
/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreExint::isInit(void){
  if(CoreExint::channelEnable & (1 << this->mRegister))
		return true;
  
  return false;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::PinEdgeTrigger
 */
   
/**
 * 
 */
void CoreExint::disableAll(void){
  this->periphReset();
}

/**
 * 
 */
void CoreExint::disableFall(void){
	uint32_t mask = (1 << this->mRegister);
	
	if(this->mRunnableRise != nullptr){	        //rise disable fall enable
		CoreExint::channelMode &= (~mask);	        //clear dualmode flag (rise and fall)
		CoreExint::channelLevel |= mask;           //set rise mode flag
		BASE->polcfg2 &= (~mask);                  //disable fall flag
		BASE->polcfg1 |= mask;                     //enable rise flag
		
	}else{  //all disable
		this->periphReset();
	}
	
	return;
}

/**
 * 
 */
void CoreExint::disableRise(void){
	uint32_t mask = (1 << this->mRegister);
	
	if(this->mRunnableFall != nullptr){	        //rise disable fall enable
		CoreExint::channelMode &= (~mask);	        //clear dualmode flag (rise and fall)
		CoreExint::channelLevel &= (~mask);        //set rise mode flag
		BASE->polcfg1 &= (~mask);                  //diasble rise flag;
		BASE->polcfg2 |= mask;                     //enable fall flag;		
		
	}else{  //all disable
		this->periphReset();
	}
	
	return;
}

/**
 * 
 */
bool CoreExint::enableFall(EdgeTriggerEvent* event){
  uint32_t mask = (1 << this->mRegister);
  this->mRunnableFall = event;
  
  if(this->mRunnableRise != nullptr)
    CoreExint::channelMode |= mask;    //set dualmode flag (rise and fall)
  
  else{
    CoreExint::channelMode &= ~mask;   //clear dualmode flag (rise and fall)
    CoreExint::channelLevel &= ~mask;  //set fall mode flag
    BASE->polcfg1 &= ~mask;            //disable rise flag
		BASE->polcfg2 |= mask;             //enable fall flag
		BASE->inten |= mask;              //enable interrupt flag        
  }
  
  return true;
}

/**
 * 
 */
bool CoreExint::enableRise(EdgeTriggerEvent* event){
  uint32_t mask = (1 << this->mRegister);
  this->mRunnableRise = event;
  
  if(this->mRunnableFall != nullptr)
    CoreExint::channelMode |= mask;    //set dualmode flag (rise and fall)
  
  else{
		CoreExint::channelMode &= ~mask;   //clear dualmode flag (rise and fall)
		CoreExint::channelLevel |= mask;   //set rise mode flag
		BASE->polcfg2 &= ~mask;            //disable fall flag
		BASE->polcfg1 |= mask;             //enable rise flag
		BASE->inten |= mask;              //enable interrupt flag
  }
  
  return true;
}
  
/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */
  
/**
 *
 */
void CoreExint::run(void){
	uint32_t mask = (1 << this->mRegister);
	bool levelFlag = (CoreExint::channelLevel & mask);
	
  if(CoreExint::channelMode & mask){
    if(levelFlag){
      BASE->polcfg1 &= (~mask);
      BASE->polcfg2 |= mask;
        
    }else{
      BASE->polcfg1 |= mask;
      BASE->polcfg2 &= (~mask);
    }
    CoreExint::channelLevel ^= mask;
  }
  
	BASE->intsts = mask;
	
	if(levelFlag){  //rise
    this->mRunnableRise->onEdgeTriggerEvent(EdgeTriggerEvent::HAL_EDGETRIGGER_RISE);
	}else{          //fall
    this->mRunnableFall->onEdgeTriggerEvent(EdgeTriggerEvent::HAL_EDGETRIGGER_FALL);
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
void CoreExint::periphReset(void){
  uint8_t ch = this->mRegister;
  
  BASE->inten  &= ~(1 << ch);
  BASE->evten  &= ~(1 << ch);
  BASE->polcfg1 &= ~(1 << ch);
  BASE->polcfg2 &= ~(1 << ch);
  BASE->intsts    |= (1 << ch);
  
  this->mRunnableRise = nullptr;
  this->mRunnableFall = nullptr;  
  return;
}
 
/* ****************************************************************************************
 * End of file
 */ 
