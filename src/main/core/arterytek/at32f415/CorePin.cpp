/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "CorePin.hpp"

#include "core/arterytek/at32f415/ctrl/CtrlPin.hpp"
#include "core/arterytek/at32f415/ctrl/CtrlGPIO.hpp"
#include "core/arterytek/at32f415/core/core_io.h"
#include "core/arterytek/at32f415/core/core_iocon.h"
#include "core/arterytek/at32f415/core/core_ioconGpio.h"

#include "bsp_arterytek_at32f415/at32f4xx.h"

/* ****************************************************************************************
 * Macro
 */  
#define GET_BASE(x) ((GPIO_Type*)x)

/* ****************************************************************************************
 * Using
 */  
 
using core::arterytek::at32f415::CorePin;


/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CorePin::CorePin(void* base, uint32_t pin){
  this->mBase = base;
  this->mPin = pin;
}


/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override>
 */

/**
 * Get io direction.
 * 
 * @return false = input, true = output.
 */
bool CorePin::dir(void){
  return core_iocon_gpio_getPinDir(GET_BASE(this->mBase), this->mPin);
}

/**   
 * Set io direction.
 * 
 * @param dir false = input, true = output.
 */
void CorePin::dir(bool dir){
  core_iocon_gpio_setPinDir(GET_BASE(this->mBase), this->mPin, dir);
}

/**
 * 
 */
CorePin::PinMode CorePin::pinMode(void){
  return PinMode::NOT_SUPPORT;
}

/**
 * 
 */
bool CorePin::pinMode(PinMode mode){
  return false;
} 

/**
 * Set io pin to high.
 */
void CorePin::setHigh(void){
  if(!core_iocon_gpio_getPinDir(GET_BASE(this->mBase), this->mPin))
    return;
  
  GET_BASE(this->mBase)->BSRE |= (1 << this->mPin);
  return;
}

/**
 * Set io direction to input.
 */
void CorePin::setInput(void){
  core_iocon_gpio_setPinDir(GET_BASE(this->mBase), this->mPin, false);
}

/**
 * Set io pin to low.
 */
void CorePin::setLow(void){
  if(!core_iocon_gpio_getPinDir(GET_BASE(this->mBase), this->mPin))
    return;

  GET_BASE(this->mBase)->BRE |= (1 << this->mPin);
}

/**
 * Set io direction to output.
 */
void CorePin::setOutput(void){
  core_iocon_gpio_setPinDir(GET_BASE(this->mBase), this->mPin, true);
}

/**
 * Set io not logic.
 */
void CorePin::setToggle(void){
  GET_BASE(this->mBase)->OPTDT ^= (1 << this->mPin);
}

/**
 * Get io pin.
 *
 * @return false = low, true = high.
 */
bool CorePin::value(void){
	if(GET_BASE(this->mBase)->IPTDT & (1 << this->mPin))
		return true;
	else
		return false;
}

/**
 * Set io pin to high or low.
 *
 * @param value false = low, true = high.
 */
void CorePin::value(bool level){
  if(!core_iocon_gpio_getPinDir(GET_BASE(this->mBase), this->mPin))
    return;

	if(level)
	  GET_BASE(this->mBase)->BSRE |= (1 << this->mPin);
	else
	  GET_BASE(this->mBase)->BRE |= (1 << this->mPin);
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
