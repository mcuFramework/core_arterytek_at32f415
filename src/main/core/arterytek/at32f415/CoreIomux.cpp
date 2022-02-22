/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */ 
#include "CoreIomux.h"

#include "bsp_arterytek_at32f415/at32f415.h"

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreIomux;

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
bool CoreIomux::deinit(void){
  if(!this->isInit())
    return false;
  
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, FALSE);
  return true;
}

/**
 *
 */
bool CoreIomux::init(void){
  if(this->isInit())
    return false;
  
   crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  return true;
}

/**
 *
 */
bool CoreIomux::isInit(void){
  return CRM_REG(CRM_IOMUX_PERIPH_CLOCK) & CRM_REG_BIT(CRM_IOMUX_PERIPH_CLOCK);
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreIomux::remapCAN(MapCAN map){
  this->remap(&IOMUX->remap6, MapCAN::CAN_MASK, map);
}

/**
 *
 */
void CoreIomux::remapCOMP(MapCOMP map){
  this->remap(&IOMUX->remap6, MapCOMP::COMP_MASK, map);
}

/**
 *
 */
void CoreIomux::remapDEBUG(MapDEBUG map){
  this->remap(&IOMUX->remap7, MapDEBUG::DEBUG_MASK, map);
}

/**
 *
 */
void CoreIomux::remapEXTI(MapEXTI map, uint8_t pin){
  if(pin >= 16)
    return;
  
  uint8_t array = (pin >> 2);  //pin/4
  uint8_t shift = ((pin & 0x00000003) << 2);  //(pin%4)*4
  volatile uint32_t* reg = &IOMUX->exintc1;
  this->remap(&reg[array], (0x0000000F << shift), (map << shift));
  return;
}

/**
 *
 */
void CoreIomux::remapI2C1(MapI2C1 map){
  this->remap(&IOMUX->remap5, MapI2C1::I2C1_MASK, map);
}

/**
 *
 */
void CoreIomux::remapI2C2(MapI2C2 map){
  this->remap(&IOMUX->remap5, MapI2C2::I2C2_MASK, map);
}


/**
 *
 */
void CoreIomux::remapSDIO(MapSDIO map){
  this->remap(&IOMUX->remap6, MapSDIO::SDIO_MASK, map);
}


/**
 *
 */
void CoreIomux::remapSPI1(MapSPI1 map){
  this->remap(&IOMUX->remap5, MapSPI1::SPI1_MASK, map);
}


/**
 *
 */
void CoreIomux::remapSPI2(MapSPI2 map){
  this->remap(&IOMUX->remap5, MapSPI2::SPI2_MASK, map);
}


/**
 *
 */
void CoreIomux::remapUSART1(MapUSART1 map){
  this->remap(&IOMUX->remap6, MapUSART1::USART1_MASK, map);
}


/**
 *
 */
void CoreIomux::remapUSART3(MapUSART3 map){
  this->remap(&IOMUX->remap6, MapUSART3::USART3_MASK, map);
}


/**
 *
 */
void CoreIomux::remapUART4(MapUART4 map){
  this->remap(&IOMUX->remap6, MapUART4::UART4_MASK, map);
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
void CoreIomux::remap(volatile uint32_t* reg, uint32_t mask, uint32_t value){
  uint32_t cache = (*reg & ~mask);
  *reg = (cache | value);
  return;
}
 
/* ****************************************************************************************
 * End of file
 */ 
