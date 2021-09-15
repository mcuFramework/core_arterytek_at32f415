/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "core/arterytek/at32f415/CoreGPIO.hpp"

#include "bsp_arterytek_at32f415/at32f4xx.h"
 
/* ****************************************************************************************
 * Using
 */  
 
using core::arterytek::at32f415::CoreGPIO;
using core::arterytek::at32f415::CorePin;

/* ****************************************************************************************
 * Macro
 */
#define GET_CTRL_DIR(source, shift) ((source & (0x00000003 << (shift << 2)))?1:0)
#define GET_BIT(source, bit)        ((source & (1 << (bit)))?1:0)
#define GET_BASE(x)                 ((GPIO_Type*)x)

/* ****************************************************************************************
 * Variable
 */


/* ****************************************************************************************
 * Construct Method
 */

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

  uint32_t mask;
  
  switch((uint32_t)this->mBase){
    case GPIOA_BASE:
      mask = RCC_APB2PERIPH_GPIOA;
      break;
    
    case GPIOB_BASE:
      mask = RCC_APB2PERIPH_GPIOB;
      break;
    
    case GPIOC_BASE:
      mask = RCC_APB2PERIPH_GPIOC;
      break;
    
    case GPIOD_BASE:
      mask = RCC_APB2PERIPH_GPIOD;
      break;
    
    case GPIOF_BASE:
      mask = RCC_APB2PERIPH_GPIOF;
      break;
    
    default:
      return false;  
  };
	
  RCC->APB2EN &= ~mask;
	
	return true;
}

/**
 * dir
 */
uint32_t CoreGPIO::dir(uint32_t port){
  if(port)
    return 0x00000000;
  
  uint32_t result = 0x00000000;
  
  for(uint32_t i=0; i<8; ++i){
    uint32_t mask = (0x00000003 << (i << 2));
    
    if(GET_BASE(this->mBase)->CTRLL & ~mask)
      result |= (1 << i);     
    
    if(GET_BASE(this->mBase)->CTRLH & ~mask)
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
  
  value &= 0x0000FFFF;
  
  uint32_t regMaskCONF;
  
  
  for(uint32_t i=0; i<8; ++i){
    regMaskCONF = (0x00000003 << (i<<2));
    
    if(GET_BASE(this->mBase)->CTRLL & ~regMaskCONF){  //hardware is output
      if(!GET_BIT(value, i))                          //value flag is low?
        GET_BASE(this->mBase)->CTRLL &= ~regMaskCONF; //set input
        
    }else{                                            //hardware is input
      if(GET_BIT(value, i))                           //value flag is high?
        GET_BASE(this->mBase)->CTRLL |= regMaskCONF;  //set output 50M
    }
    
    if(GET_BASE(this->mBase)->CTRLH & ~regMaskCONF){  //hardware is output
      if(!GET_BIT(value, 8+i))                        //value flag is low?
        GET_BASE(this->mBase)->CTRLH &= ~regMaskCONF; //set input
        
    }else{                                            //hardware is input
      if(GET_BIT(value, 8+i))                         //value flag is high?
        GET_BASE(this->mBase)->CTRLH |= regMaskCONF;  //set output 50M
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
	
  switch((uint32_t)this->mBase){
    case GPIOA_BASE:
      RCC->APB2EN |= RCC_APB2PERIPH_GPIOA;
      break;
    
    case GPIOB_BASE:
      RCC->APB2EN |= RCC_APB2PERIPH_GPIOB;
      break;
    
    case GPIOC_BASE:
      RCC->APB2EN |= RCC_APB2PERIPH_GPIOC;
      break;
    
    case GPIOD_BASE:
      RCC->APB2EN |= RCC_APB2PERIPH_GPIOD;
      break;
    
    case GPIOF_BASE:
      RCC->APB2EN |= RCC_APB2PERIPH_GPIOF;
      break;
    
    default:
      return false;  
  };
  
  return false;
}

/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreGPIO::isInit(void){
  switch((uint32_t)this->mBase){
    case GPIOA_BASE:
      return (RCC->APB2EN & RCC_APB2PERIPH_GPIOA);
    
    case GPIOB_BASE:
      return (RCC->APB2EN & RCC_APB2PERIPH_GPIOB);
    
    case GPIOC_BASE:
      return (RCC->APB2EN & RCC_APB2PERIPH_GPIOB);
    
    case GPIOD_BASE:
      return (RCC->APB2EN & RCC_APB2PERIPH_GPIOB);
    
    case GPIOF_BASE:
      return (RCC->APB2EN & RCC_APB2PERIPH_GPIOB);
    
    default:
      return false;  
  };
}

/**
 * 
 * @param port GPIO port.
 */
uint32_t CoreGPIO::pin(uint32_t port){
  if(port)
    return 0x00000000;
  
	return GET_BASE(this->mBase)->IPTDT;
}

/**
 *
 * @param port GPIO port.
 * @param value GPIO write value.
 */
void CoreGPIO::pin(uint32_t port, uint32_t value){
  if(port)
    return;
  
  uint32_t dir = this->dir(0);
  GET_BASE(this->mBase)->BSRE = (value & dir);
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
  
  uint32_t dir = this->dir(0);
  
  GET_BASE(this->mBase)->BRE = (((uint16_t)mask) & dir);
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
  
  uint32_t dir = this->dir(0);
  
  GET_BASE(this->mBase)->BSRE = (((uint16_t)mask) & dir);
  return;
}

/**
 * 
 */
void CoreGPIO::pinToggle(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  uint32_t dir = this->dir(0);
  
	GET_BASE(port)->OPTDT ^= (((uint16_t)mask) & dir);
	return;
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
