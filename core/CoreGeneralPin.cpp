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
#include "../bsp/package-info.h"  

//-----------------------------------------------------------------------------------------
#include "./CoreGeneralPin.h"
#include "./CoreGeneralPort.h"

/* ****************************************************************************************
 * Macro
 */  
#define GET_CTRL_DIR(source, shift) ((static_cast<int>(source) & (0x00000003 << (shift << 2)))?true:false)
#define BASE                        (GET_BASE(this->mBase))
#define GET_BASE(x)                 (static_cast<gpio_type*>(x))

/* ****************************************************************************************
 * Using
 */  
using core::CoreGeneralPort;
using core::CoreGeneralPin;

using hal::GeneralPin;
using hal::GeneralPinMode;


/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreGeneralPin::CoreGeneralPin(CoreGeneralPort& base, uint32_t pin){
  this->mBase = base.getBase();
  this->mPin = pin;
}

/**
 *
 */
CoreGeneralPin::~CoreGeneralPin(void){
  return;
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
bool CoreGeneralPin::getDir(void){
  if(this->mPin >= 8)
    return GET_CTRL_DIR(BASE->cfglr, this->mPin);
  else
    return GET_CTRL_DIR(BASE->cfghr, (this->mPin-8));
}

/**   
 * Set io direction.
 * 
 * @param dir false = input, true = output.
 */
void CoreGeneralPin::setDir(bool dir){
  if(dir)
    this->setInput();
  
  else  
    this->setOutput();
}

/**
 * 
 */
GeneralPinMode CoreGeneralPin::getPinMode(void){
  return GeneralPinMode::NOT_SUPPORT;
}

/**
 * 
 */
GeneralPinMode CoreGeneralPin::setPinMode(GeneralPinMode mode){
  uint8_t shift = static_cast<uint8_t>((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~static_cast<uint32_t>(0x0000000F << shift)); 

  switch(mode){
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::NOT_SUPPORT:
      return GeneralPinMode::NOT_SUPPORT;
    
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::PUSH_PULL:
      if(!this->getDir())
        return GeneralPinMode::NOT_SUPPORT;
      
      *reg = (ctrl | static_cast<uint32_t>(0x00000003 << shift));
      return mode;
    
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::PULL_UP:
      if(this->getDir())
        return GeneralPinMode::NOT_SUPPORT;
      
      *reg = (ctrl | static_cast<uint32_t>(0x00000008 << shift));
      GET_BASE(this->mBase)->scr |= (1 << this->mPin);
      return mode;
    
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::PULL_DOWN:
      if(this->getDir())
        return GeneralPinMode::NOT_SUPPORT;
      
      *reg = (ctrl | static_cast<uint32_t>(0x00000008 << shift));
      GET_BASE(this->mBase)->clr |= (1 << this->mPin);
      return mode;      
      
    //-------------------------------------------------------------------------------------
    case GeneralPinMode::OPEN_DRAIN:
      if(this->getDir())
        *reg = (ctrl | static_cast<uint32_t>(0x00000007 << shift));
      
      else
        *reg = (ctrl | static_cast<uint32_t>(0x00000004 << shift));
 
      return mode;
  }
  
  return GeneralPinMode::NOT_SUPPORT;
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
  uint8_t shift = static_cast<uint8_t>((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~static_cast<uint32_t>(0x0000000F << shift));   
  
  *reg = (ctrl | static_cast<uint32_t>(0x00000004) << shift);
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
  uint8_t shift = static_cast<uint8_t>((this->mPin & 0x00000007) << 2);
  volatile uint32_t *reg;
  
  if(this->mPin < 8)
    reg = &GET_BASE(this->mBase)->cfglr;
  
  else
    reg = &GET_BASE(this->mBase)->cfghr;
  
  uint32_t ctrl = ((*reg) & ~static_cast<uint32_t>(0x0000000F << shift));   
  
  *reg = (ctrl | static_cast<uint32_t>(0x00000003) << shift);
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
bool CoreGeneralPin::getValue(void){
	return (GET_BASE(this->mBase)->idt & (1 << this->mPin));
}

/**
 * Set io pin to high or low.
 *
 * @param value false = low, true = high.
 */
void CoreGeneralPin::setValue(bool level){
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
