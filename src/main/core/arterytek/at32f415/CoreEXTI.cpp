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
#include "bsp_arterytek_at32f415/at32f4xx.h"
#include "core/arterytek/at32f415/Core.hpp"
#include "core/arterytek/at32f415/CoreEXTI.hpp"
#include "core/arterytek/at32f415/CoreInterrupt.hpp"
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      struct ConfigCoreEXTI{
        CoreInterrupt::Irq irq;
      }const configCoreEXTI[16]{
        {CoreInterrupt::IRQ_EXTI0},
        {CoreInterrupt::IRQ_EXTI1},
        {CoreInterrupt::IRQ_EXTI2},
        {CoreInterrupt::IRQ_EXTI3},
        {CoreInterrupt::IRQ_EXTI4},
        {CoreInterrupt::IRQ_EXTI5},
        {CoreInterrupt::IRQ_EXTI6},
        {CoreInterrupt::IRQ_EXTI7},
        {CoreInterrupt::IRQ_EXTI8},
        {CoreInterrupt::IRQ_EXTI9},
        {CoreInterrupt::IRQ_EXTI10},
        {CoreInterrupt::IRQ_EXTI11},
        {CoreInterrupt::IRQ_EXTI12},
        {CoreInterrupt::IRQ_EXTI13},
        {CoreInterrupt::IRQ_EXTI14},
        {CoreInterrupt::IRQ_EXTI15},
      };
      
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using mcuf::hal::PinEdgeTrigger;
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreEXTI;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                   (configCoreEXTI[this->mRegister])
#define BASE                     (EXTI)

/* ****************************************************************************************
 * Variable <Static>
 */
uint16_t CoreEXTI::channelEnable = 0x0000U;
uint16_t CoreEXTI::channelMode = 0x0000U;
uint16_t CoreEXTI::channelLevel = 0x0000U;

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
CoreEXTI::CoreEXTI(Register reg){
  this->mRegister = reg;
}

/**
 *
 */
CoreEXTI::~CoreEXTI(void){
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
bool CoreEXTI::deinit(void){
	if(!(CoreEXTI::channelEnable & (1 << this->mRegister)))
		return false;
  
  CoreEXTI::channelEnable &= ~(1 << this->mRegister);
  Core::interrupt.irqHandler(CONFIG.irq, false);
  Core::interrupt.setHandler(CONFIG.irq, nullptr);  
  this->periphReset();
  return true;
}

/**
 * initialze hardware;
 */
bool CoreEXTI::init(void){
  if(CoreEXTI::channelEnable & (1 << this->mRegister))
    return false;
  
  CoreEXTI::channelEnable |= (1 << this->mRegister);
  this->periphReset();
  Core::interrupt.setHandler(CONFIG.irq, this);
  Core::interrupt.irqHandler(CONFIG.irq, true);
  
  return true;
}
  
/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreEXTI::isInit(void){
  if(CoreEXTI::channelEnable & (1 << this->mRegister))
		return true;
  
  return false;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::PinEdgeTrigger
 */
   
/**
 * 
 */
void CoreEXTI::disableAll(void){
  this->periphReset();
}

/**
 * 
 */
void CoreEXTI::disableFall(void){
	uint32_t mask = (1 << this->mRegister);
	
	if(this->mRunnableRise != nullptr){	        //rise disable fall enable
		CoreEXTI::channelMode &= (~mask);	        //clear dualmode flag (rise and fall)
		CoreEXTI::channelLevel |= mask;           //set rise mode flag
		BASE->FTRSEL &= (~mask);                  //disable fall flag
		BASE->RTRSEL |= mask;                     //enable rise flag
		
	}else{  //all disable
		this->periphReset();
	}
	
	return;
}

/**
 * 
 */
void CoreEXTI::disableRise(void){
	uint32_t mask = (1 << this->mRegister);
	
	if(this->mRunnableFall != nullptr){	        //rise disable fall enable
		CoreEXTI::channelMode &= (~mask);	        //clear dualmode flag (rise and fall)
		CoreEXTI::channelLevel &= (~mask);        //set rise mode flag
		BASE->RTRSEL &= (~mask);                  //diasble rise flag;
		BASE->FTRSEL |= mask;                     //enable fall flag;		
		
	}else{  //all disable
		this->periphReset();
	}
	
	return;
}

/**
 * 
 */
bool CoreEXTI::enableFall(PinEdgeTrigger::Event* event){
  uint32_t mask = (1 << this->mRegister);
  this->mRunnableFall = event;
  
  if(this->mRunnableRise != nullptr)
    CoreEXTI::channelMode |= mask;    //set dualmode flag (rise and fall)
  
  else{
    CoreEXTI::channelMode &= ~mask;   //clear dualmode flag (rise and fall)
    CoreEXTI::channelLevel &= ~mask;  //set fall mode flag
    BASE->RTRSEL &= ~mask;            //disable rise flag
		BASE->FTRSEL |= mask;             //enable fall flag
		BASE->INTEN |= mask;              //enable interrupt flag        
  }
  
  return true;
}

/**
 * 
 */
bool CoreEXTI::enableRise(PinEdgeTrigger::Event* event){
  uint32_t mask = (1 << this->mRegister);
  this->mRunnableRise = event;
  
  if(this->mRunnableFall != nullptr)
    CoreEXTI::channelMode |= mask;    //set dualmode flag (rise and fall)
  
  else{
		CoreEXTI::channelMode &= ~mask;   //clear dualmode flag (rise and fall)
		CoreEXTI::channelLevel |= mask;   //set rise mode flag
		BASE->FTRSEL &= ~mask;            //disable fall flag
		BASE->RTRSEL |= mask;             //enable rise flag
		BASE->INTEN |= mask;              //enable interrupt flag
  }
  
  return true;
}
  
/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */
  
/**
 *
 */
void CoreEXTI::run(void){
	uint32_t mask = (1 << this->mRegister);
	bool levelFlag = (CoreEXTI::channelLevel & mask);
	
  if(CoreEXTI::channelMode & mask){
    if(levelFlag){
      EXTI->RTRSEL &= (~mask);
      EXTI->FTRSEL |= mask;
        
    }else{
      EXTI->RTRSEL |= mask;
      EXTI->FTRSEL &= (~mask);
    }
    CoreEXTI::channelLevel ^= mask;
  }
  
	EXTI->PND = mask;
	
	if(levelFlag){  //rise
    this->mRunnableRise->onPinEdgeTriggerEvent(Event::RISE);
	}else{          //fall
    this->mRunnableFall->onPinEdgeTriggerEvent(Event::FALL);
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
void CoreEXTI::periphReset(void){
  uint8_t ch = this->mRegister;
  
  EXTI->INTEN  &= ~(1 << ch);
  EXTI->EVTEN  &= ~(1 << ch);
  EXTI->RTRSEL &= ~(1 << ch);
  EXTI->FTRSEL &= ~(1 << ch);
  EXTI->PND    |= (1 << ch);
  
  this->mRunnableRise = nullptr;
  this->mRunnableFall = nullptr;  
  return;
}
 
/* ****************************************************************************************
 * End of file
 */ 
