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

#include "bsp_arterytek_at32f415/at32f415.h"
#include "core/arterytek/at32f415/CoreGpio.hpp"

/* ****************************************************************************************
 * Macro
 */  
#define GET_CTRL_DIR(source, shift) ((source & (0x00000003 << (shift << 2)))?1:0)
#define GET_BASE(x)                 ((gpio_type*)x)

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreGpio;
using core::arterytek::at32f415::CorePin;


/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CorePin::CorePin(CoreGpio* base, uint32_t pin){
  this->mBase = base->getBase();
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
  if(this->mPin >= 8)
    return GET_CTRL_DIR(GET_BASE(this->mBase)->cfglr, this->mPin);
  else
    return GET_CTRL_DIR(GET_BASE(this->mBase)->cfghr, (this->mPin-8));
}

/**   
 * Set io direction.
 * 
 * @param dir false = input, true = output.
 */
void CorePin::dir(bool dir){
  if(dir)
    this->setInput();
  
  else  
    this->setOutput();
}

/**
 * 
 */
CorePin::PinMode CorePin::pinMode(void){
  return PinMode::PINMODE_NOT_SUPPORT;
}

/**
 * 
 */
bool CorePin::pinMode(PinMode mode){
  uint8_t shift = ((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~(0x0000000F << shift)); 

  switch(mode){
    //-------------------------------------------------------------------------------------
    case PinMode::PINMODE_NOT_SUPPORT:
      return false;
    
    //-------------------------------------------------------------------------------------
    case PinMode::PINMODE_PUSH_PULL:
      if(!this->dir())
        return false;
      
      *reg = (ctrl | (0x00000003 << shift));
      return true;
    
    //-------------------------------------------------------------------------------------
    case PinMode::PINMODE_PULL_UP:
      if(this->dir())
        return false;
      
      *reg = (ctrl | (0x00000008 << shift));
      GET_BASE(this->mBase)->scr |= (1 << this->mPin);
      return true;
    
    //-------------------------------------------------------------------------------------
    case PinMode::PINMODE_PULL_DOWN:
      if(this->dir())
        return false;
      
      *reg = (ctrl | (0x00000008 << shift));
      GET_BASE(this->mBase)->clr |= (1 << this->mPin);
      return true;      
      
    //-------------------------------------------------------------------------------------
    case PinMode::PINMODE_OPEN_DRAIN:
      if(this->dir())
        *reg = (ctrl | (0x00000007 << shift));
      
      else
        *reg = (ctrl | (0x00000004 << shift));
 
      return true;
      
    //-------------------------------------------------------------------------------------
    default:
      return false;
  }
  
  return false;
} 

/**
 * Set io pin to high.
 */
void CorePin::setHigh(void){
  GET_BASE(this->mBase)->scr |= (1 << this->mPin);
  return;
}

/**
 * Set io direction to input.
 */
void CorePin::setInput(void){
  uint8_t shift = ((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~(0x0000000F << shift));   
  
  *reg = (ctrl | (0x00000040) << shift);
}

/**
 * Set io pin to low.
 */
void CorePin::setLow(void){
  GET_BASE(this->mBase)->clr |= (1 << this->mPin);
}

/**
 * Set io direction to output.
 */
void CorePin::setOutput(void){
  uint8_t shift = ((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~(0x0000000F << shift));   
  
  *reg = (ctrl | (0x00000003) << shift);
}

/**
 * Set io not logic.
 */
void CorePin::setToggle(void){
  GET_BASE(this->mBase)->odt ^= (1 << this->mPin);
}

/**
 * Get io pin.
 *
 * @return false = low, true = high.
 */
bool CorePin::value(void){
	return (GET_BASE(this->mBase)->idt & (1 << this->mPin));
}

/**
 * Set io pin to high or low.
 *
 * @param value false = low, true = high.
 */
void CorePin::value(bool level){
	if(level)
	  GET_BASE(this->mBase)->scr |= (1 << this->mPin);
	else
	  GET_BASE(this->mBase)->clr |= (1 << this->mPin);
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
