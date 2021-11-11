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

#include "periph/TestCoreEXTI.hpp"

/* ****************************************************************************************
 * Using
 */  
using periph::TestCoreEXTI;
using core::arterytek::at32f415::CorePin;
using core::arterytek::at32f415::CoreEXTI;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
TestCoreEXTI::TestCoreEXTI(CorePin& pin, CoreEXTI::Register reg, TestMode testMode) construct mCoreEXTI(reg){
  this->mPin = &pin;
  this->mTestMode = testMode;
}

/**
 *
 */
TestCoreEXTI::~TestCoreEXTI(void){
  this->mCoreEXTI.deinit();
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */

/**
 *
 */
void TestCoreEXTI::run(void){
  this->mPin->setToggle();
}

/* ****************************************************************************************
 * Public Method <Override> - periph::Test
 */

/**
 *
 */
void TestCoreEXTI::start(void){
  this->mCoreEXTI.init();
  /*
  switch(this->mTestMode){
    case TESTMODE_RISE:
      this->mCoreEXTI.enableRise(*this);
      break;
    
    case TESTMODE_FALL:
      this->mCoreEXTI.enableFall(*this);
      break;
    
    case TESTMODE_ALL:
      this->mCoreEXTI.enableRise(*this);
      this->mCoreEXTI.enableFall(*this);
      break;
  }
  */
}
  
/** 
 *
 */
void TestCoreEXTI::stop(void){
  this->mCoreEXTI.deinit();
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
 
/* ****************************************************************************************
 * End of file
 */ 
