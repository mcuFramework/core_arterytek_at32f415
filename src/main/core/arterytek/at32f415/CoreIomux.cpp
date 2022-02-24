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
volatile void* const CoreIomux::regAddress = IOMUX;

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

void CoreIomux::enableHEXT(bool enable){
  if(enable)
    IOMUX->remap7_bit.pd01_gmux = false;
  
  else
    IOMUX->remap7_bit.pd01_gmux = true;
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
  this->remap(&reg[array], (0x0000000F << shift), ((uint32_t)map << shift));
  return;
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
