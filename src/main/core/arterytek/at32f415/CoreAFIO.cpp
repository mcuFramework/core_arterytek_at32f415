/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */ 
#include "CoreAFIO.hpp"

#include "bsp_arterytek_at32f415/at32f4xx.h"

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreAFIO;

/* ****************************************************************************************
 * Variable <Static>
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
 *
 */
bool CoreAFIO::deinit(void){
  if(!this->isInit())
    return false;
  
  RCC->APB2EN &= ~RCC_APB2PERIPH_AFIO;
  return true;
}

/**
 *
 */
bool CoreAFIO::init(void){
  if(this->isInit())
    return false;
  
  RCC->APB2EN |= RCC_APB2PERIPH_AFIO;
  return true;
}

/**
 *
 */
bool CoreAFIO::isInit(void){
  return (RCC->APB2EN & RCC_APB2PERIPH_AFIO); 
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreAFIO::remapCAN(MapCAN map){
  this->remap(&AFIO->MAP6, MapCAN::CAN_MASK, map);
}

/**
 *
 */
void CoreAFIO::remapCOMP(MapCOMP map){
  this->remap(&AFIO->MAP6, MapCOMP::COMP_MASK, map);
}

/**
 *
 */
void CoreAFIO::remapDEBUG(MapDEBUG map){
  this->remap(&AFIO->MAP7, MapDEBUG::DEBUG_MASK, map);
}

/**
 *
 */
void CoreAFIO::remapEXTI(MapEXTI map, uint8_t pin){
  if(pin >= 16)
    return;
  
  uint8_t array = (pin >> 2);  //pin/4
  uint8_t shift = ((pin & 0x00000003) << 2);  //(pin%4)*4
  
  this->remap(&AFIO->EXTIC[array], (0x0000000F << shift), (map << shift));
  return;
}

/**
 *
 */
void CoreAFIO::remapI2C1(MapI2C1 map){
  this->remap(&AFIO->MAP5, MapI2C1::I2C1_MASK, map);
}

/**
 *
 */
void CoreAFIO::remapI2C2(MapI2C2 map){
  this->remap(&AFIO->MAP5, MapI2C2::I2C2_MASK, map);
}


/**
 *
 */
void CoreAFIO::remapSDIO(MapSDIO map){
  this->remap(&AFIO->MAP6, MapSDIO::SDIO_MASK, map);
}


/**
 *
 */
void CoreAFIO::remapSPI1(MapSPI1 map){
  this->remap(&AFIO->MAP5, MapSPI1::SPI1_MASK, map);
}


/**
 *
 */
void CoreAFIO::remapSPI2(MapSPI2 map){
  this->remap(&AFIO->MAP5, MapSPI2::SPI2_MASK, map);
}


/**
 *
 */
void CoreAFIO::remapUSART1(MapUSART1 map){
  this->remap(&AFIO->MAP6, MapUSART1::USART1_MASK, map);
}


/**
 *
 */
void CoreAFIO::remapUSART3(MapUSART3 map){
  this->remap(&AFIO->MAP6, MapUSART3::USART3_MASK, map);
}


/**
 *
 */
void CoreAFIO::remapUART4(MapUART4 map){
  this->remap(&AFIO->MAP6, MapUART4::UART4_MASK, map);
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
void CoreAFIO::remap(volatile uint32_t* reg, uint32_t mask, uint32_t value){
  uint32_t cache = (*reg & ~mask);
  *reg = (cache | value);
  return;
}
 
/* ****************************************************************************************
 * End of file
 */ 
