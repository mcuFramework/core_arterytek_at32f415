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
#include "bsp_arterytek_at32f415.h"
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/general/trigger/CoreEdgeTrigger.h"
#include "core/arterytek/at32f415/Core.h"
#include "core/arterytek/at32f415/CoreInterrupt.h"


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
using namespace core::arterytek::at32f415::general::trigger;
using namespace mcuf::hal::general::trigger;

//-----------------------------------------------------------------------------------------
using core::arterytek::at32f415::Core;

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<char>(this->mRegister))
#define CONFIG                   (configCoreExint[REGNUMB])
#define BASE                     (EXINT)

/* ****************************************************************************************
 * Variable <Static>
 */
uint16_t CoreEdgeTrigger::channelEnable = 0x0000U;
uint16_t CoreEdgeTrigger::channelMode = 0x0000U;
uint16_t CoreEdgeTrigger::channelLevel = 0x0000U;

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
CoreEdgeTrigger::CoreEdgeTrigger(CoreEdgeTriggerReg reg){
  this->mRegister = reg;
}

/**
 *
 */
CoreEdgeTrigger::~CoreEdgeTrigger(void){
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
bool CoreEdgeTrigger::deinit(void){
	if(!(CoreEdgeTrigger::channelEnable & (1 << REGNUMB)))
		return false;
  
  CoreEdgeTrigger::channelEnable &= ~(1 << REGNUMB);
  Core::interrupt.irqEnable(CONFIG.irq, false);
  Core::interrupt.setHandler(CONFIG.irq, nullptr);  
  this->periphReset();
  return true;
}

/**
 * initialze hardware;
 */
bool CoreEdgeTrigger::init(void){
  if(CoreEdgeTrigger::channelEnable & (1 << REGNUMB))
    return false;
  
  CoreEdgeTrigger::channelEnable |= (1 << REGNUMB);
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
bool CoreEdgeTrigger::isInit(void){
  if(CoreEdgeTrigger::channelEnable & (1 << REGNUMB))
		return true;
  
  return false;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::PinEdgeTrigger
 */
   
/**
 * 
 */
void CoreEdgeTrigger::disableAll(void){
  this->periphReset();
}

/**
 * 
 */
void CoreEdgeTrigger::disableFall(void){
	uint32_t mask = (1 << REGNUMB);
	
	if(this->mRunnableRise != nullptr){	        //rise disable fall enable
		CoreEdgeTrigger::channelMode &= (~mask);	        //clear dualmode flag (rise and fall)
		CoreEdgeTrigger::channelLevel |= mask;           //set rise mode flag
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
void CoreEdgeTrigger::disableRise(void){
	uint32_t mask = (1 << REGNUMB);
	
	if(this->mRunnableFall != nullptr){	        //rise disable fall enable
		CoreEdgeTrigger::channelMode &= (~mask);	        //clear dualmode flag (rise and fall)
		CoreEdgeTrigger::channelLevel &= (~mask);        //set rise mode flag
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
bool CoreEdgeTrigger::enableFall(EdgeTriggerEvent* event){
  uint32_t mask = (1 << REGNUMB);
  this->mRunnableFall = event;
  
  if(this->mRunnableRise != nullptr)
    CoreEdgeTrigger::channelMode |= mask;    //set dualmode flag (rise and fall)
  
  else{
    CoreEdgeTrigger::channelMode &= ~mask;   //clear dualmode flag (rise and fall)
    CoreEdgeTrigger::channelLevel &= ~mask;  //set fall mode flag
    BASE->polcfg1 &= ~mask;            //disable rise flag
		BASE->polcfg2 |= mask;             //enable fall flag
		BASE->inten |= mask;              //enable interrupt flag        
  }
  
  return true;
}

/**
 * 
 */
bool CoreEdgeTrigger::enableRise(EdgeTriggerEvent* event){
  uint32_t mask = (1 << REGNUMB);
  this->mRunnableRise = event;
  
  if(this->mRunnableFall != nullptr)
    CoreEdgeTrigger::channelMode |= mask;    //set dualmode flag (rise and fall)
  
  else{
		CoreEdgeTrigger::channelMode &= ~mask;   //clear dualmode flag (rise and fall)
		CoreEdgeTrigger::channelLevel |= mask;   //set rise mode flag
		BASE->polcfg2 &= ~mask;            //disable fall flag
		BASE->polcfg1 |= mask;             //enable rise flag
		BASE->inten |= mask;              //enable interrupt flag
  }
  
  return true;
}
  
/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::InterruptEvent
 */
  
/**
 *
 */
void CoreEdgeTrigger::interruptEvent(void){
	uint32_t mask = (1 << REGNUMB);
	bool levelFlag = (CoreEdgeTrigger::channelLevel & mask);
	
  if(CoreEdgeTrigger::channelMode & mask){
    if(levelFlag){
      BASE->polcfg1 &= (~mask);
      BASE->polcfg2 |= mask;
        
    }else{
      BASE->polcfg1 |= mask;
      BASE->polcfg2 &= (~mask);
    }
    CoreEdgeTrigger::channelLevel ^= mask;
  }
  
	BASE->intsts = mask;
	
	if(levelFlag){  //rise
    this->mRunnableRise->onEdgeTriggerEvent(EdgeTriggerStatus::RISE);
	}else{          //fall
    this->mRunnableFall->onEdgeTriggerEvent(EdgeTriggerStatus::FALL);
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
void CoreEdgeTrigger::periphReset(void){
  uint8_t ch = REGNUMB;
  
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
