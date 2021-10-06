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

#include "start/SpeedReader.hpp"

/* ****************************************************************************************
 * Using
 */  
using start::SpeedReader;
using namespace core::arterytek::at32f415;
using namespace mcuf::lang;

/* ****************************************************************************************
 * Using
 */  

/* ****************************************************************************************
 * Macro
 */
 
/* ****************************************************************************************
 * Variable
 */

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/**
 * Construct.
 */
SpeedReader::SpeedReader(CoreEXTI::Register reg) construct mCoreEXTI(reg){
  this->mValue = 0;
  this->mCache = 0;
  this->mTotal = 0;
  this->mCoreEXTI.init();
  this->mCoreEXTI.enableRise(*this);
}

/**
 * Destruct.
 */
SpeedReader::~SpeedReader(void){
  this->mCoreEXTI.deinit();
}

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */

/**
 *
 */
void SpeedReader::run(void){
  ++this->mCache;
  ++this->mTotal;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void SpeedReader::recode(void){
  this->mValue = this->mCache;
  this->mCache = 0;
}

/**
 *
 */
uint32_t SpeedReader::getValue(void){
  return this->mValue;
}

/**
 *
 */
uint32_t SpeedReader::getTotal(void){
  return this->mTotal;
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
 * Private Method <Static>
 */
 
/* ****************************************************************************************
 * Private Method
 */
 
/* ****************************************************************************************
 * End of file
 */ 
