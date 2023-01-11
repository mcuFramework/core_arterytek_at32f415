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
#include "./CorePulseWidthPin.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using core::CorePulseWidthPin;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */
/**
 * @brief Construct a new Core Pulse Width Pin object
 * 
 * @param corePulseWidthPort 
 * @param channel 
 */
CorePulseWidthPin::CorePulseWidthPin(core::CorePulseWidthPort& corePulseWidthPort, int channel) : 
mCorePulseWidthPort(corePulseWidthPort){
  this->mChannel = channel;
  return;
}
/**
 * @brief Destroy the Core Pulse Width Pin object
 * 
 */
CorePulseWidthPin::~CorePulseWidthPin(void){
  return;
}
/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::PulseWidthPin
 */

/**
 * @brief Get the Period object
 * 
 * @return int 
 */
int CorePulseWidthPin::getPeriod(void){
  return this->mCorePulseWidthPort.getPeriod();
}

/**
 * @brief Get the Duty object
 * 
 * @return float 
 */
float CorePulseWidthPin::getDuty(void){
  return this->mCorePulseWidthPort.getDuty(this->mChannel);
}

/**
 * @brief Get the Frequence object
 * 
 * @return float 
 */
float CorePulseWidthPin::getFrequence(void){
  return this->mCorePulseWidthPort.getFrequence();
}

/**
 * @brief Set the Duty object
 * 
 * @param percent 0 ~ 1.0
 * @return true 
 * @return false 
 */
bool CorePulseWidthPin::setDuty(float percent){
  return this->mCorePulseWidthPort.setDuty(this->mChannel, percent);
}

/**
 * @brief Set the Duty object
 * 
 * @param duty 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPin::setDuty(int duty){
  return this->mCorePulseWidthPort.setDuty(this->mChannel, duty);
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPin::stop(void){
  return this->mCorePulseWidthPort.setDuty(this->mChannel, 0);
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
