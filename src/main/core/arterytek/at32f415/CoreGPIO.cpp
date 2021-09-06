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
#include "core/arterytek/at32f415/ctrl/CtrlPin.hpp"
#include "core/arterytek/at32f415/ctrl/CtrlGPIO.hpp"

#include "bsp_arterytek_at32f415/at32f4xx.h"
 
/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::ctrl::CtrlPin;
using core::arterytek::at32f415::ctrl::CtrlGPIO;
using core::arterytek::at32f415::CoreGPIO;
using core::arterytek::at32f415::CorePin;

/* ****************************************************************************************
 * Macro
 */
#define GET_BASE(x) ((GPIO_Type*)(CoreGPIO::regBase[x]))

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
	
	RCC_APB2PeriphClockCmd((RCC_APB2PERIPH_GPIOA | RCC_APB2PERIPH_GPIOB | RCC_APB2PERIPH_GPIOC | 
	                        RCC_APB2PERIPH_GPIOD | RCC_APB2PERIPH_GPIOF | RCC_APB2PERIPH_AFIO), 
	                       DISABLE);
	
	return true;
}

/**
 * dir
 */
uint32_t CoreGPIO::dir(uint32_t port){
  return CtrlGPIO::getDir(port);
}

/**
 * dir
 */
void CoreGPIO::dir(uint32_t port, uint32_t value){
  CtrlGPIO::setDir(port, value);
}

/**
 * 
 */
void CoreGPIO::dirClear(uint32_t port, uint32_t mask){
  uint16_t origDir = CtrlGPIO::getDir(port);
  CtrlGPIO::setDir(port, (origDir & (~mask)));
}

/**
 * 
 */
void CoreGPIO::dirSet(uint32_t port, uint32_t mask){
  uint16_t origDir = CtrlGPIO::getDir(port);
  CtrlGPIO::setDir(port, (origDir | mask));
}

/**
 * initialze hardware;
 */
bool CoreGPIO::init(void){
  if(this->isInit())
    return false;
	
  RCC_APB2PeriphClockCmd((RCC_APB2PERIPH_GPIOA | RCC_APB2PERIPH_GPIOB | 
	                      RCC_APB2PERIPH_GPIOC | RCC_APB2PERIPH_GPIOD | 
	                      RCC_APB2PERIPH_GPIOF | RCC_APB2PERIPH_AFIO), ENABLE);

  GPIO_Reset(GPIOA);
  GPIO_Reset(GPIOB);
  GPIO_Reset(GPIOC);
  GPIO_Reset(GPIOD);
  GPIO_Reset(GPIOF);
  GPIO_AFIOReset();
  GPIO_PinsRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  return true;
}

/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreGPIO::isInit(void){
  return false;
}

/**
 * 
 * @param port GPIO port.
 */
uint32_t CoreGPIO::pin(uint32_t port){
	return ((uint16_t)GET_BASE(port)->IPTDT);
}

/**
 *
 * @param port GPIO port.
 * @param value GPIO write value.
 */
void CoreGPIO::pin(uint32_t port, uint32_t value){
  uint16_t origDir = CtrlGPIO::getDir(port);
  GET_BASE(port)->BSRE = (((uint16_t)value) & origDir);
}

/**
 * setting io output pin to push-pull low at mask.
 *
 * @param port io port.
 * @param mask bit high = active.
 */
void CoreGPIO::pinClear(uint32_t port, uint32_t mask){
  uint16_t origDir = CtrlGPIO::getDir(port);
  GET_BASE(port)->BRE = (((uint16_t)mask) & origDir);
  return;
}

/**
 *
 * @param port GPIO port.
 * @param mask GPIO write value.
 */
void CoreGPIO::pinSet(uint32_t port, uint32_t mask){
  uint16_t origDir = CtrlGPIO::getDir(port);
  GET_BASE(port)->BSRE = (((uint16_t)mask) & origDir);
  return;
}

/**
 * 
 */
void CoreGPIO::pinToggle(uint32_t port, uint32_t mask){
	uint16_t origDir = CtrlGPIO::getDir(port);
	GET_BASE(port)->OPTDT ^= (((uint16_t)mask) & origDir);
	return;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 * 
 */
CoreGeneralPurposePin CoreGPIO::getPin(uint32_t port, uint32_t pin){
  return CoreGeneralPurposePin(GET_BASE(port), pin);
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
 
/* ****************************************************************************************
 * End of file
 */ 
