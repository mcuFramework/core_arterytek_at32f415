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
#include "bsp_arterytek_at32f415/at32f4xx.h"
#include "core_arterytek_at32f415.h"

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreAFIO;
using core::arterytek::at32f415::CoreGPIO;
using core::arterytek::at32f415::CoreInterrupt;

/* ****************************************************************************************
 * Variable <Static>
 */
CoreInterrupt Core::interrupt = CoreInterrupt();
CoreAFIO Core::afio = CoreAFIO();

CoreGPIO Core::gpioa = CoreGPIO(CoreGPIO::REG_GPIOA);
CoreGPIO Core::gpiob = CoreGPIO(CoreGPIO::REG_GPIOB);
CoreGPIO Core::gpioc = CoreGPIO(CoreGPIO::REG_GPIOC);
CoreGPIO Core::gpiod = CoreGPIO(CoreGPIO::REG_GPIOD);
CoreGPIO Core::gpiof = CoreGPIO(CoreGPIO::REG_GPIOF);

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
uint32_t Core::getSystemCoreClock(void){
  return SystemCoreClock;
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
 * Private Method
 */
 
/* ****************************************************************************************
 * End of file
 */ 
