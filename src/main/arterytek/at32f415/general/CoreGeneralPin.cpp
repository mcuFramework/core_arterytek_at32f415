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

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/general/CoreGeneralPin.h"
#include "arterytek/at32f415/general/CoreGeneralPort.h"

/* ****************************************************************************************
 * Macro
 */  
#define GET_CTRL_DIR(source, shift) ((source & (0x00000003 << (shift << 2)))?1:0)
#define GET_BASE(x)                 ((gpio_type*)x)

/* ****************************************************************************************
 * Using
 */  
using arterytek::at32f415::general::CoreGeneralPort;
using arterytek::at32f415::general::CoreGeneralPin;

using hal::general::GeneralPin;
using hal::general::GeneralPinMode;


/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreGeneralPin::CoreGeneralPin(CoreGeneralPort* base, uint32_t pin){
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
bool CoreGeneralPin::dir(void){
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
void CoreGeneralPin::dir(bool dir){
  if(dir)
    this->setInput();
  
  else  
    this->setOutput();
}

/**
 * 
 */
GeneralPinMode CoreGeneralPin::pinMode(void){
  return GeneralPinMode::NOT_SUPPORT;
}

/**
 * 
 */
bool CoreGeneralPin::pinMode(GeneralPinMode mode){
  uint8_t shift = ((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~(0x0000000F << shift)); 

  switch(mode){
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::NOT_SUPPORT:
      return false;
    
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::PUSH_PULL:
      if(!this->dir())
        return false;
      
      *reg = (ctrl | (0x00000003 << shift));
      return true;
    
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::PULL_UP:
      if(this->dir())
        return false;
      
      *reg = (ctrl | (0x00000008 << shift));
      GET_BASE(this->mBase)->scr |= (1 << this->mPin);
      return true;
    
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::PULL_DOWN:
      if(this->dir())
        return false;
      
      *reg = (ctrl | (0x00000008 << shift));
      GET_BASE(this->mBase)->clr |= (1 << this->mPin);
      return true;      
      
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::OPEN_DRAIN:
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
void CoreGeneralPin::setHigh(void){
  GET_BASE(this->mBase)->scr |= (1 << this->mPin);
  return;
}

/**
 * Set io direction to input.
 */
void CoreGeneralPin::setInput(void){
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
void CoreGeneralPin::setLow(void){
  GET_BASE(this->mBase)->clr |= (1 << this->mPin);
}

/**
 * Set io direction to output.
 */
void CoreGeneralPin::setOutput(void){
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
void CoreGeneralPin::setToggle(void){
  GET_BASE(this->mBase)->odt ^= (1 << this->mPin);
}

/**
 * Get io pin.
 *
 * @return false = low, true = high.
 */
bool CoreGeneralPin::value(void){
	return (GET_BASE(this->mBase)->idt & (1 << this->mPin));
}

/**
 * Set io pin to high or low.
 *
 * @param value false = low, true = high.
 */
void CoreGeneralPin::value(bool level){
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
