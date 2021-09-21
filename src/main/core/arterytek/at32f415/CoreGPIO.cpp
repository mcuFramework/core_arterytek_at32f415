/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "CoreGPIO.hpp"

#include "bsp_arterytek_at32f415/at32f4xx.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      struct ConfigCoreGPIO{
        void* Register;
        uint32_t clockMask;
      }const configCoreGPIO[5]{
        {GPIOA, RCC_APB2PERIPH_GPIOA},
        {GPIOB, RCC_APB2PERIPH_GPIOB},
        {GPIOC, RCC_APB2PERIPH_GPIOC},
        {GPIOD, RCC_APB2PERIPH_GPIOD},
        {GPIOF, RCC_APB2PERIPH_GPIOF},
      };
      
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreGPIO;
using core::arterytek::at32f415::CorePin;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                      (configCoreGPIO[this->mRegister])
#define BASE                        ((GPIO_Type*)CONFIG.Register)
#define GET_CTRL_DIR(source, shift) ((source & (0x00000003 << (shift << 2)))?1:0)
#define GET_BIT(source, bit)        ((source & (1 << (bit)))?1:0)

/* ****************************************************************************************
 * Variable
 */


/* ****************************************************************************************
 * Construct Method
 */
 
/**
 *
 */
CoreGPIO::CoreGPIO(Register reg){
  this->mRegister = reg;
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
 * uninitialze hardware.
 */
bool CoreGPIO::deinit(void){
	if(!this->isInit())
		return false;
	
  RCC->APB2EN &= ~CONFIG.clockMask;
	
	return true;
}

/**
 * dir
 */
uint32_t CoreGPIO::dir(uint32_t port){
  if(port)
    return 0x00000000;
  
  GPIO_Type* base = BASE;
  
  uint32_t result = 0x00000000;
  
  for(uint32_t i=0; i<8; ++i){
    uint32_t mask = (0x00000003 << (i << 2));
    
    if(base->CTRLL & ~mask)
      result |= (1 << i);     
    
    if(base->CTRLH & ~mask)
      result |= (1 << (8+i));   
  }
  
  return result;
}

/**
 * dir
 */
void CoreGPIO::dir(uint32_t port, uint32_t value){
  if(port)
    return;
  
  GPIO_Type* base = BASE;
  
  value &= 0x0000FFFF;
  
  uint32_t regMaskCONF;
  
  
  for(uint32_t i=0; i<8; ++i){
    regMaskCONF = (0x00000003 << (i<<2));
    
    if(base->CTRLL & regMaskCONF){  //hardware is output
      if(!GET_BIT(value, i))                          //value flag is low?
        base->CTRLL &= ~regMaskCONF; //set input
        
    }else{                                            //hardware is input
      if(GET_BIT(value, i))                           //value flag is high?
        base->CTRLL |= regMaskCONF;  //set output 50M
    }
    
    if(base->CTRLH & regMaskCONF){  //hardware is output
      if(!GET_BIT(value, 8+i))                        //value flag is low?
        base->CTRLH &= ~regMaskCONF; //set input
        
    }else{                                            //hardware is input
      if(GET_BIT(value, 8+i))                         //value flag is high?
        base->CTRLH |= regMaskCONF;  //set output 50M
    }
  }
  
  return;
}

/**
 * 
 */
void CoreGPIO::dirClear(uint32_t port, uint32_t mask){
  if(port)
    return;

  this->dir(0, (this->dir(0) & ~mask));
  
  return;
}

/**
 * 
 */
void CoreGPIO::dirSet(uint32_t port, uint32_t mask){
  if(port)
    return;

  this->dir(0, (this->dir(0) | mask));
  
  return;
}

/**
 * initialze hardware;
 */
bool CoreGPIO::init(void){
  if(this->isInit())
    return false;
  
	RCC->APB2EN |= CONFIG.clockMask;
  return false;
}

/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreGPIO::isInit(void){
  return RCC->APB2EN & CONFIG.clockMask;
}

/**
 * 
 * @param port GPIO port.
 */
uint32_t CoreGPIO::pin(uint32_t port){
  if(port)
    return 0x00000000;
  
  GPIO_Type* base = BASE;
  
	return base->IPTDT;
}

/**
 *
 * @param port GPIO port.
 * @param value GPIO write value.
 */
void CoreGPIO::pin(uint32_t port, uint32_t value){
  if(port)
    return;
  
  GPIO_Type* base = BASE;
  uint32_t dir = this->dir(0);
  
  base->BSRE = (value & dir);
}

/**
 * setting io output pin to push-pull low at mask.
 *
 * @param port io port.
 * @param mask bit high = active.
 */
void CoreGPIO::pinClear(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  GPIO_Type* base = BASE;
  uint32_t dir = this->dir(0);
  
  base->BRE = (((uint16_t)mask) & dir);
  return;
}

/**
 *
 * @param port GPIO port.
 * @param mask GPIO write value.
 */
void CoreGPIO::pinSet(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  GPIO_Type* base = BASE;
  uint32_t dir = this->dir(0);
  
  base->BSRE = (((uint16_t)mask) & dir);
  return;
}

/**
 * 
 */
void CoreGPIO::pinToggle(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  GPIO_Type* base = BASE;
  
  uint32_t dir = this->dir(0);
  
	base->OPTDT ^= (((uint16_t)mask) & dir);
	return;
}

/* ****************************************************************************************
 * Public Method
 */
  
/**
 *
 */
bool CoreGPIO::configInput(uint32_t pin, InputMode mode){
  if(pin >= 16)
    return false;
  
  GPIO_Type* base = BASE;
  
  uint8_t shift = ((pin & 0x00000007) << 2);
  volatile uint32_t* reg;
  uint32_t ctrl;
  
  if(pin < 8)  // 0~7pin
    reg = &base->CTRLL;
    
  else        // 8~15pin
    reg = &base->CTRLH;
  
  ctrl = ((*reg) & (0x0000000F << shift));
  
  switch(mode){
    case InputMode_Open:
      *reg = (ctrl | (0x00000004 << shift));
      base->BRE |= (1 << pin);
      return true;
      
    case InputMode_Analog:
      *reg = ctrl;
      base->BRE |= (1 << pin);
      return true;
    
    case InputMode_Pulldown:
      *reg = (ctrl | (0x00000008 << shift));
      base->BRE |= (1 << pin);
      return true;
      
    case InputMode_Pullup:
      *reg = (ctrl | (0x00000008 << shift));
      base->BSRE |= (1 << pin);
      return true;
    
    default:
      return false;
  }
  
  return false;
}
  
/**
 *
 */
bool CoreGPIO::configOutput(uint32_t pin, OutputMode mode, bool opendrain, bool function, bool value){
  if(pin >= 16)
    return false;
  
  GPIO_Type* base = BASE;
  
  uint8_t shift = ((pin & 0x00000007) << 2);
  volatile uint32_t* reg;
  uint32_t ctrl;
  
  if(pin < 8)  // 0~7pin
    reg = &base->CTRLL;
    
  else        // 8~15pin
    reg = &base->CTRLH;
  
  ctrl = ((*reg) & ~(0x0000000F << shift));
  
  if(opendrain)
    ctrl |= (0x00000004 << shift);
  
  if(function)
    ctrl |= (0x00000008 << shift);
  
  
  switch(mode){
    case OutputMode_2M:
      *reg = (ctrl | (0x00000002 << shift));
      break;
    
    case OutputMode_10M:
      *reg = (ctrl | (0x00000001 << shift));
      break;
    
    case OutputMode_50M:
      *reg = (ctrl | (0x00000003 << shift));
      break;
    
    default:
      return false;
  }
  
  base->BSRE |= (1<<pin);
  
  return false;
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

/**
 *
 */
void* CoreGPIO::getBase(void){
  return BASE;
}

/* ****************************************************************************************
 * End of file
 */ 
