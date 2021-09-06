/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "core/arterytek/at32f415/CoreSPI.hpp"

#include "bsp_arterytek_at32f415/at32f4xx_rcc.h"
#include "bsp_arterytek_at32f415/at32f4xx_spi.h"



/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreSPI;

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

/**
 *
 */
inline void CoreSPI::xferClear(void){
  
}

/**
 * 
 */
inline void CoreSPI::spiEnable(void){
  ((SPI_Type*)this->regAddress)->CTRL1 |= SPI_CTRL1_SPIEN;
}

/**
 * 
 */
inline void CoreSPI::spiDisable(void){
  ((SPI_Type*)this->regAddress)->CTRL1 &= ~SPI_CTRL1_SPIEN;
}

/**
 * 
 */
inline void CoreSPI::isrTransferEnable(void){
  ((SPI_Type*)this->regAddress)->CTRL2 |= (SPI_CTRL2_TEIE);
}

/**
 * 
 */
inline void CoreSPI::isrTransferDisable(void){
  ((SPI_Type*)this->regAddress)->CTRL2 &= ~(SPI_CTRL2_TEIE);
}

/**
 * 
 */
inline void CoreSPI::isrReceiverEnable(void){
  ((SPI_Type*)this->regAddress)->CTRL2 |= (SPI_CTRL2_RNEIE);
}

/**
 * 
 */
inline void CoreSPI::isrReceiverDisable(void){
  ((SPI_Type*)this->regAddress)->CTRL2 &= ~(SPI_CTRL2_RNEIE);
}

/**
 * 
 */
inline void CoreSPI::isrEnable(void){
  ((SPI_Type*)this->regAddress)->CTRL2 |= (SPI_CTRL2_TEIE | SPI_CTRL2_RNEIE);
}

/**
 * 
 */
inline void CoreSPI::isrDisable(void){
  ((SPI_Type*)this->regAddress)->CTRL2 &= ~(SPI_CTRL2_TEIE | SPI_CTRL2_RNEIE);
}

/* ****************************************************************************************
 * End of file
 */ 
