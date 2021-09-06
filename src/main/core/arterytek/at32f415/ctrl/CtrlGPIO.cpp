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

#include "core/arterytek/at32f415/ctrl/CtrlPin.hpp"
#include "core/arterytek/at32f415/ctrl/CtrlGPIO.hpp"

#include "bsp_arterytek_at32f415/at32f4xx_gpio.h"

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::ctrl::CtrlGPIO;

/* ****************************************************************************************
 * Macro
 */

#define GET_BASE(x)  ((GPIO_Type*)CtrlGPIO::getBase(x))
#define GET_PORT(x)  CtrlGPIO::getPort(x)
 
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

/**
 *
 */
void CtrlGPIO::refresh(void* base){
  CtrlPin::RegIocon* regIocon = &CtrlPin::regIocon[GET_PORT(base)];

  CtrlGPIO::ctrlRefreshPinMask(base, regIocon, 0xFFFF);
  return;
}

/**
 *
 */
void CtrlGPIO::refresh(uint16_t port){
  GPIO_Type* pBase = GET_BASE(port);
  CtrlPin::RegIocon* regIocon = &CtrlPin::regIocon[port];
  
  CtrlGPIO::ctrlRefreshPinMask(pBase, regIocon, 0xFFFF);
  return;
}

/**
 *
 */
void CtrlGPIO::refreshPin(uint16_t port, uint16_t pin){
  bool dir = CtrlGPIO::getPinDir(port, pin);
  CtrlGPIO::setPinDir(port, pin, dir);
  return;
}

/**
 *
 */
void CtrlGPIO::refreshPin(void* base, uint16_t pin){
  uint16_t port = GET_PORT(base);
  bool dir = CtrlGPIO::getPinDir(port, pin);
  CtrlGPIO::setPinDir(port, pin, dir);
  return;
}

/**
 *
 */
void CtrlGPIO::refreshPinMask(uint16_t port, uint16_t pinMask){
  ASSERT_THROW_ERROR((port < 6), "port >= 6");
  
  GPIO_Type* base = GET_BASE(port);
  if(!pinMask)
    return;
  
  uint32_t ctrll = base->CTRLL;
  uint32_t ctrlh = base->CTRLH;
  
  CtrlPin::RegIocon* regIocon = &CtrlPin::regIocon[port];
  uint16_t origDir = CtrlGPIO::getFullDir(ctrll, ctrlh);
  
  int i;
  int regShift;
  
  uint16_t cache = 0;
  uint16_t pullMask = 0;
  uint16_t mask;
  uint16_t maskPullUp;
  uint16_t maskPullDown;
  
  if(pinMask & 0x00FF){
    for(i=0, regShift=0; i<8; i++, regShift+=4){
      mask = (1 << i);
      
      if(pinMask & mask){
        if(origDir & mask)
          cache = (regIocon->pin[i] & 0x0F);//set output
        
        else{
          cache = ((regIocon->pin[i] >> 4) & 0x0C); //set input
          if(cache == 0x08)
            pullMask |= mask;
        }
        
        ctrll |= (cache << regShift);
      }
    }
    base->CTRLL = ctrll;
  }
  
  if(pinMask & 0xFF00){
    for(i=0, regShift=0; i<8; i++, regShift+=4){
      mask = (1 << (i+8));
      if(pinMask & mask){
        if(origDir & mask)
          cache = (regIocon->pin[i+8] & 0x0F); //set output
        
        else{
          cache = ((regIocon->pin[i+8] >> 4) & 0x0C); //set input
          if(cache == 0x08)
            pullMask |= mask;
        }
        
        ctrlh |= (cache << regShift);
      }
    }
    base->CTRLH = ctrlh;
  }
  
  maskPullUp   = (pullMask & regIocon->pull);
  maskPullDown = (pullMask & (~regIocon->pull));
  
  base->BSRE = (maskPullUp | (maskPullDown << 16));
}

/**
 *
 */
void CtrlGPIO::setDir(uint16_t port, uint16_t dir){
  ASSERT_THROW_ERROR((port < 6), "port >= 6");
  
  GPIO_Type* base = GET_BASE(port);
  CtrlPin::RegIocon* regIocon = &CtrlPin::regIocon[port];
  
  CtrlGPIO::ConfigDir configDir;
  configDir = CtrlGPIO::getCtrlRemix(base->CTRLL, base->CTRLH, dir, regIocon);
  
  base->BSRE = (configDir.maskPullUp | (configDir.maskPullDown << 16));
  base->CTRLH = configDir.ctrlh;
  base->CTRLL = configDir.ctrll;
}

/**
 *
 */
uint16_t CtrlGPIO::getDir(void* base){
  GPIO_Type* pBase = (GPIO_Type*)base;
  return CtrlGPIO::getFullDir(pBase->CTRLL, pBase->CTRLH);
}

/**
 *
 */
uint16_t CtrlGPIO::getDir(uint16_t port){
  ASSERT_THROW_ERROR((port < 6), "port >= 6");
  GPIO_Type* base = GET_BASE(port);
  
  return CtrlGPIO::getFullDir(base->CTRLL, base->CTRLH);
}

/**
 *
 */
bool CtrlGPIO::getPinDir(void* base, uint16_t pin){
  GPIO_Type* pBase = (GPIO_Type*)base;
  
  if(pin<8)
    return (pBase->CTRLL & (0x03 << (pin*4)));
  
  else
    return (pBase->CTRLH & (0x03 << ((pin & 0x07)*4)));
  
}

/**
 *
 */
bool CtrlGPIO::getPinDir(uint16_t port, uint16_t pin){
  ASSERT_THROW_ERROR((port < 6), "port >= 6");
  ASSERT_THROW_ERROR((pin < 16), "pin >= 16");
  
  GPIO_Type* base = GET_BASE(port);
  return CtrlGPIO::getPinDir(base, pin);
}

/**
 *
 */
void CtrlGPIO::setPinDir(void* base, uint8_t pin, bool dir){
  ASSERT_THROW_ERROR((pin < 16), "pin >= 16");
  
  uint16_t port = GET_PORT(base);
  CtrlPin::RegIocon* regIocon = &CtrlPin::regIocon[port];
  
  CtrlGPIO::ctrlSetPinDir(base, regIocon, pin, dir);
  return;
}

/**
 *
 */
void CtrlGPIO::setPinDir(uint16_t port, uint8_t pin, bool dir){
  ASSERT_THROW_ERROR((port < 6), "port >= 6");
  ASSERT_THROW_ERROR((pin < 16), "pin >= 16");
  
  GPIO_Type* base = GET_BASE(port);
  CtrlPin::RegIocon* regIocon = &CtrlPin::regIocon[port];
  
  CtrlGPIO::ctrlSetPinDir(base, regIocon, pin, dir);
  return;
}

/* ****************************************************************************************
 * Public Method <Override>
 */

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
 * Private Method <Static>
 */

/**
 *
 */
void CtrlGPIO::ctrlRefreshPinMask(void* base, void* reg, uint16_t pinMask){
  
  GPIO_Type* pGPIO = (GPIO_Type*)base;
  if(!pinMask)
    return;
  
  uint32_t ctrll = pGPIO->CTRLL;
  uint32_t ctrlh = pGPIO->CTRLH;
  
  CtrlPin::RegIocon* regIocon = (CtrlPin::RegIocon*)reg;
  uint16_t origDir = CtrlGPIO::getFullDir(ctrll, ctrlh);
  
  int i;
  int regShift;
  
  uint16_t cache = 0;
  uint16_t pullMask = 0;
  uint16_t mask;
  uint16_t maskPullUp;
  uint16_t maskPullDown;
  
  if(pinMask & 0x00FF){
    for(i=0, regShift=0; i<8; i++, regShift+=4){
      mask = (1 << i);
      
      if(pinMask & mask){
        if(origDir & mask)
          cache = (regIocon->pin[i] & 0x0F);//set output
        
        else{
          cache = ((regIocon->pin[i] >> 4) & 0x0C); //set input
          if(cache == 0x08)
            pullMask |= mask;
        }
        
        ctrll |= (cache << regShift);
      }
    }
    pGPIO->CTRLL = ctrll;
  }
  
  if(pinMask & 0xFF00){
    for(i=0, regShift=0; i<8; i++, regShift+=4){
      mask = (1 << (i+8));
      if(pinMask & mask){
        if(origDir & mask)
          cache = (regIocon->pin[i+8] & 0x0F); //set output
        
        else{
          cache = ((regIocon->pin[i+8] >> 4) & 0x0C); //set input
          if(cache == 0x08)
            pullMask |= mask;
        }
        
        ctrlh |= (cache << regShift);
      }
    }
    pGPIO->CTRLH = ctrlh;
  }
  
  maskPullUp   = (pullMask & regIocon->pull);
  maskPullDown = (pullMask & (~regIocon->pull));
  
  pGPIO->BSRE = (maskPullUp | (maskPullDown << 16));
}

/**
 *
 */
void CtrlGPIO::ctrlSetPinDir(void* base, void* reg, uint16_t pin, bool dir){

  GPIO_Type* pBase = (GPIO_Type*)base;
  CtrlPin::RegIocon* regIocon = (CtrlPin::RegIocon*)reg;
  
  uint32_t ctrl;
  uint8_t pullMod;
  uint8_t cache;
  
  if(pin<8){ //ctrll
    ctrl = pBase->CTRLL;
    ctrl &= ~(0xF << (pin*4)); //clear reg
    
    if(dir){
      ctrl |= ((regIocon->pin[pin] & 0x0F) << (pin*4));//set output
      
    }else{
      cache = ((regIocon->pin[pin] >> 4) & 0x0C); //set input
      ctrl |= (cache << (pin*4));
      if(cache == 0x08)//pull mode
        pullMod = true;
    }
    
    pBase->CTRLL = ctrl;
  }else{ //ctrlh
    ctrl = pBase->CTRLH;
    ctrl &= ~(0xF << ((pin & 0x07)*4)); //clear reg
    
    if(dir)
      ctrl |= ((regIocon->pin[pin] & 0x0F) << ((pin & 0x07)*4));//set output
    
    else{
      cache = ((regIocon->pin[pin] >> 4) & 0x0C); //set input
      ctrl |= (cache << ((pin & 0x07)*4));
      if(cache == 0x08)//pull mode
        pullMod = true;
    }
    
    pBase->CTRLH = ctrl;
  }
  
  if(pullMod){
    if(regIocon->pull & (1 << pin)){ //pullup
      pBase->BSRE = (1 << pin);
    }else{ //pulldown
      pBase->BRE = (1 << pin);
    }
  }
}

/**
 * 
 */
void CtrlGPIO::ctrlSetDir(void* base, void* reg, uint16_t dir){
  GPIO_Type* pBase = (GPIO_Type*)base;
  CtrlPin::RegIocon* regIocon = (CtrlPin::RegIocon*)reg;
  
  CtrlGPIO::ConfigDir configDir;
  configDir = CtrlGPIO::getCtrlRemix(pBase->CTRLL, pBase->CTRLH, dir, regIocon);
  
  pBase->BSRE = (configDir.maskPullUp | (configDir.maskPullDown << 16));
  pBase->CTRLH = configDir.ctrlh;
  pBase->CTRLL = configDir.ctrll;
  return;
}


/**
 * 
 */
void* CtrlGPIO::getBase(uint16_t port){
  switch(port){
    case 0:
      return GPIOA;
    
    case 1:
      return GPIOB;
    
    case 2:
      return GPIOC;
    
    case 3:
      return GPIOD;
    
    case 5:
      return GPIOF;
    
    default:
      THROW_ERROR("out of enum index");
  }
  
  return nullptr;
}

uint16_t CtrlGPIO::getPort(void* base){
  switch((uint32_t)base){
    case GPIOA_BASE:
      return 0;
    
    case GPIOB_BASE:
      return 1;
    
    case GPIOC_BASE:
      return 2;
    
    case GPIOD_BASE:
      return 3;
    
    case GPIOF_BASE:
      return 5;
    
    default:
      THROW_ERROR("out of enum index");
      
  }
  
  return 0xFFFF;
}

/**
 *
 */
uint8_t CtrlGPIO::getHelfDir(uint32_t ctrl){
  uint8_t result = 0;
  int i;
  ctrl &= 0x33333333;
  
  for(i=0; i<8; i++){
    if(ctrl & (0xF << i*4))
      result |= (1<<i);
  }
  
  return result;
}

/**
 *
 */
uint16_t CtrlGPIO::getFullDir(uint32_t ctrll, uint32_t ctrlh){
  return (CtrlGPIO::getHelfDir(ctrll) | (CtrlGPIO::getHelfDir(ctrlh) << 8));
}

/**
 *
 */
CtrlGPIO::ConfigDir CtrlGPIO::getCtrlRemix(uint32_t ctrll, uint32_t ctrlh, uint16_t dir, void* reg){
  CtrlPin::RegIocon* regIocon = (CtrlPin::RegIocon*)reg;
  ConfigDir result = {0};
  result.ctrll = ctrll;
  result.ctrlh = ctrlh;
  
  uint16_t origDir = CtrlGPIO::getFullDir(ctrll, ctrlh);
  uint16_t pullMask = 0;
  uint32_t cache;
  uint32_t mask;
  uint16_t changeDir = 0;
  int i, regShift;
  
  //remix CTRLL
  for(i=0, regShift=0; i<8; i++, regShift+=4){
    mask = (1 << i);
    if((origDir & mask) != (dir & mask)){ //dir change
        
      changeDir |= (1 << i);
      result.ctrll &= ~(0xF << regShift); //clear reg
          
      if((dir & mask))  
        cache = (regIocon->pin[i] & 0x0F);//set output
      else{
        cache = ((regIocon->pin[i] >> 4) & 0x0C); //set input
        if(cache == 0x08)
          pullMask |= (1 << i);
      }
      
      result.ctrll |= (cache << regShift);
    }
  }
  
  //remix CTRLH
  for(i=0, regShift=0; i<8; i++, regShift+=4){
        mask = (1 << (i+8));
    if((origDir & mask) != (dir & mask)){ //dir change
      
      changeDir |= (1 << (i+8));//clear reg  
      result.ctrlh &= ~(0xF << regShift);
      
      if((dir & mask))  
        cache = (regIocon->pin[i+8] & 0x0F); //set output
      else{
        cache = ((regIocon->pin[i+8] >> 4) & 0x0C); //set input
        if(cache == 0x08)
          pullMask |= (1 << (i+8));
      }
        
      result.ctrlh |= (cache << regShift);
    }
  }
  
  result.maskPullUp   = (changeDir & regIocon->pull) & pullMask;
  result.maskPullDown = (changeDir & (~regIocon->pull)) & pullMask;
  
  return result;
}

/* ****************************************************************************************
 * Private Method
 */

/* ****************************************************************************************
 * End of file
 */ 