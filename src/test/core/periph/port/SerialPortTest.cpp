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

//-----------------------------------------------------------------------------------------
#include "core/periph/port/SerialPortTest.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using core::periph::port::SerialPortTest;
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using core::arterytek::at32f415::general::port::CoreGeneralPort;
using core::arterytek::at32f415::general::port::OutputMode;
using mcuf::util::Stacker;
using mcuf::lang::Memory;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
SerialPortTest::SerialPortTest(Stacker& stacker) construct mStacker(stacker){
  return;
}

/**
 *
 */
SerialPortTest::~SerialPortTest(void){
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::run
 */

/**
 * @brief
 * 
 */
void SerialPortTest::run(void){
  this->init();
  
  while(true){
    for(int i=0; i<8; ++i){
      this->mLed[i]->setToggle();
      this->delay(500);
    }
  }
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

void SerialPortTest::init(void){
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLed[i] = new(this->mStacker) CoreGeneralPin(&Core::gpiob, i);
    this->mLed[i]->setOutput();
    this->mLed[i]->setLow();
  }
  
  Core::gpioc.configOutput(10, OutputMode::SPEED_50M, false, true, true);
}

/* ****************************************************************************************
 * End of file
 */
