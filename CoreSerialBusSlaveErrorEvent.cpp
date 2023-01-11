/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */

#include "./CoreSerialBusSlaveErrorEvent.h"

//-----------------------------------------------------------------------------------------
#include "bsp_arterytek_at32f415/package-info.h" 
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreSerialBusSlave.h"
#include "./CoreSerialBus.h"

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<unsigned char>(this->mBase.mRegister))
#define CONFIG                   (CoreSerialBus::mConfig[REGNUMB])
#define BASE                     ((i2c_type*)CONFIG.mBase)

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using core::CoreSerialBusSlaveErrorEvent;
using core::CoreSerialBusSlave;
using core::CoreSerialBusErrorCode;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */
/**
 * @brief Construct a new Core Serial Bus Slave Error Event object
 * 
 * @param coreSerialBusSlave 
 */
CoreSerialBusSlaveErrorEvent::CoreSerialBusSlaveErrorEvent(CoreSerialBusSlave& coreSerialBusSlave) : 
mBase(coreSerialBusSlave){
  return;
}

/**
 * @brief Destroy the Core Serial Bus Slave Error Event object
 * 
 */
CoreSerialBusSlaveErrorEvent::~CoreSerialBusSlaveErrorEvent(void){
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreSerialBusSlaveErrorEvent::interruptEvent(void){
  i2c_type* base = BASE;
  
  /* buserr */
  if(i2c_flag_get(base, I2C_BUSERR_FLAG) != RESET){
    i2c_flag_clear(base, I2C_BUSERR_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::BUSERR);
  }

  /* arlost */
  if(i2c_flag_get(base, I2C_ARLOST_FLAG) != RESET){
    i2c_flag_clear(base, I2C_ARLOST_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::ARLOST);
  }

  /* ackfail */
  if(i2c_flag_get(base, I2C_ACKFAIL_FLAG) != RESET){
    i2c_flag_clear(base, I2C_ACKFAIL_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::ACKFAIL);
  }

  /* ouf */
  if(i2c_flag_get(base, I2C_OUF_FLAG) != RESET){
    i2c_flag_clear(base, I2C_OUF_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::OVER);
  }

  /* pecerr */
  if(i2c_flag_get(base, I2C_PECERR_FLAG) != RESET){
    i2c_flag_clear(base, I2C_PECERR_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::PECERR);
  }

  /* tmout */
  if(i2c_flag_get(base, I2C_TMOUT_FLAG) != RESET){
    i2c_flag_clear(base, I2C_TMOUT_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::TMOUT);
  }

  /* alertf */
  if(i2c_flag_get(base, I2C_ALERTF_FLAG) != RESET){
    i2c_flag_clear(base, I2C_ALERTF_FLAG);
    this->mBase.onError(CoreSerialBusErrorCode::ALERTF);
  }

  return;
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
