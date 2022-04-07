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
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "tool/BoardPeriph.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using tool::BoardPeriph;
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreIomux;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using hal::general::GeneralPinMode;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
BoardPeriph::BoardPeriph(void) construct 
  led{CoreGeneralPin(&Core::gpiob, 0), 
      CoreGeneralPin(&Core::gpiob, 1),
      CoreGeneralPin(&Core::gpiob, 2),
      CoreGeneralPin(&Core::gpiob, 3),
      CoreGeneralPin(&Core::gpiob, 4),
      CoreGeneralPin(&Core::gpiob, 5),
      CoreGeneralPin(&Core::gpiob, 6),
      CoreGeneralPin(&Core::gpiob, 7)},
  wakeup(&Core::gpioa, 0),
  function(&Core::gpioa, 1){
    
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::gpiod.init();
  Core::gpiof.init();
  Core::iomux.init();
  Core::iomux.remapSWDIO(CoreIomux::MapSWDIO::JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->led[i].setOutput();
    this->led[i].setLow();
  }
  
  this->wakeup.setInput();
  this->wakeup.pinMode(GeneralPinMode::PULL_UP);
  this->function.setInput();
  this->function.pinMode(GeneralPinMode::PULL_UP);
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
