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

/**
 * @brief 
 * 
 * @param enable 
 */
void CoreIomux::enableSWDIO(bool enable){
  if(enable)
    this->remapSWDIO(MapSWDIO::FULL);
  else
    this->remapSWDIO(MapSWDIO::ALLDISABLE);
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapCAN(MapCAN map){
  this->remap(&IOMUX->remap6,
               static_cast<uint32_t>(MapCAN::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapCOMP(MapCOMP map){
  this->remap(&IOMUX->remap2,
               static_cast<uint32_t>(MapCOMP::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapSWDIO(MapSWDIO map){
  this->remap(&IOMUX->remap7,
               static_cast<uint32_t>(MapSWDIO::MASK), 
               static_cast<uint32_t>(map));
}


/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapI2C1(MapI2C1 map){
  this->remap(&IOMUX->remap5,
               static_cast<uint32_t>(MapI2C1::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapI2C2(MapI2C2 map){
  this->remap(&IOMUX->remap5,
               static_cast<uint32_t>(MapI2C2::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapSDIO(MapSDIO map){
  this->remap(&IOMUX->remap6,
               static_cast<uint32_t>(MapSDIO::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapSPI1(MapSPI1 map){
  this->remap(&IOMUX->remap5,
               static_cast<uint32_t>(MapSPI1::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapSPI2(MapSPI2 map){
  this->remap(&IOMUX->remap5,
               static_cast<uint32_t>(MapSPI2::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR1(MapTMR1 map){
  this->remap(&IOMUX->remap4,
               static_cast<uint32_t>(MapTMR1::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR2(MapTMR2 map){
  this->remap(&IOMUX->remap4,
               static_cast<uint32_t>(MapTMR2::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR3(MapTMR3 map){
  this->remap(&IOMUX->remap4,
               static_cast<uint32_t>(MapTMR3::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR5(MapTMR5 map){
  this->remap(&IOMUX->remap4,
               static_cast<uint32_t>(MapTMR5::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR9(MapTMR9 map){
  this->remap(&IOMUX->remap3,
               static_cast<uint32_t>(MapTMR9::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR10(MapTMR10 map){
  this->remap(&IOMUX->remap3,
               static_cast<uint32_t>(MapTMR10::MASK), 
               static_cast<uint32_t>(map));
}

/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapTMR11(MapTMR11 map){
  this->remap(&IOMUX->remap3,
               static_cast<uint32_t>(MapTMR11::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapUSART1(MapUSART1 map){
  this->remap(&IOMUX->remap6,
               static_cast<uint32_t>(MapUSART1::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapUSART3(MapUSART3 map){
  this->remap(&IOMUX->remap6,
               static_cast<uint32_t>(MapUSART3::MASK), 
               static_cast<uint32_t>(map));
}
/**
 * @brief 
 * 
 * @param map 
 */
void CoreIomux::remapUART4(MapUART4 map){
  this->remap(&IOMUX->remap6,
               static_cast<uint32_t>(MapUART4::MASK), 
               static_cast<uint32_t>(map));
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
