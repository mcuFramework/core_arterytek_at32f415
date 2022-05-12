/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */

#include "arterytek/at32f415/serial/CoreSerialBusSlave.h"

//-----------------------------------------------------------------------------------------
#include "bsp_arterytek_at32f415.h"
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/serial/CoreSerialBus.h"
#include "arterytek/at32f415/Core.h"
#include "arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using arterytek::at32f415::serial::CoreSerialBusSlave;
using arterytek::at32f415::serial::CoreSerialBus;

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<unsigned char>(this->mRegister))
#define CONFIG                   (CoreSerialBus::mConfig[REGNUMB])
#define BASE                     ((i2c_type*)CONFIG.mBase)

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */
/**
 * @brief Construct a new Core Serial Bus Slave object
 * 
 */
CoreSerialBusSlave::CoreSerialBusSlave(arterytek::at32f415::serial::CoreSerialBusReg reg, uint16_t address) : 
mCoreSerialBusSlaveErrorEvent(*this){
  this->mRegister = reg;
  this->mAddress = (address << 1);
  return;
}

/**
 * @brief Destroy the Core Serial Bus Slave object
 * 
 */
CoreSerialBusSlave::~CoreSerialBusSlave(void){
  this->deinit();
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - hal::Base
 */

/**
 * @brief uninitialze hardware.
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialBusSlave::deinit(void){
  if(!this->isInit())
    return false;
  
  Core::interrupt.irqEnable(CONFIG.mIrqEvent, false);
  Core::interrupt.irqEnable(CONFIG.mIrqError, false);
  Core::interrupt.setHandler(CONFIG.mIrqEvent, nullptr);
  Core::interrupt.setHandler(CONFIG.mIrqError, nullptr);
  
  crm_periph_clock_enable(static_cast<crm_periph_clock_type>(CONFIG.mCmr), FALSE);
  
  return true;
}

/**
 * @brief initialze hardware;
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialBusSlave::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(static_cast<crm_periph_clock_type>(CONFIG.mCmr), TRUE);
  Core::interrupt.setHandler(CONFIG.mIrqEvent, this);
  Core::interrupt.setHandler(CONFIG.mIrqError, &this->mCoreSerialBusSlaveErrorEvent);
  
  Core::interrupt.irqEnable(CONFIG.mIrqEvent, true);
  Core::interrupt.irqEnable(CONFIG.mIrqError, true);
  
  i2c_init(BASE, I2C_FSMODE_DUTY_2_1, 100000);
  i2c_own_address1_set(BASE, I2C_ADDRESS_MODE_7BIT, this->mAddress);
  BASE->ctrl1_bit.i2cen = true;
  
  return true;
}

/**
 * @brief get hardware initialzed status.
 * 
 * @return true not init
 * @return false initd
 */
bool CoreSerialBusSlave::isInit(void){
  return CRM_REG(CONFIG.mCmr) & CRM_REG_BIT(CONFIG.mCmr);
}

/* ****************************************************************************************
 * Public Method <Override> - hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreSerialBusSlave::interruptEvent(void){
  i2c_type* base = BASE;  
  
  if(base->sts1_bit.stopf){
    this->onStop();
    this->statusClear();
    base->ctrl1_bit.i2cen = true;
    return;
  }    
    
  if(base->sts1_bit.addr7f){
    base->ctrl1_bit.mackctrl = false;
    this->statusClear();
    this->onStart();
  }
  
  if(base->sts1_bit.tdbe){ //write isr
    base->dt = this->onRead();
  }
  
  if(base->sts1_bit.rdbf){ //read isr
    this->onWrite(base->dt);
  }
}

/* ****************************************************************************************
 * Public Method
 */
/**
 * @brief 
 * 
 */
void CoreSerialBusSlave::start(void){
  i2c_interrupt_enable(BASE, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, TRUE);
  BASE->ctrl1_bit.acken = true;
  return;
}

/**
 * @brief 
 * 
 */
void CoreSerialBusSlave::stop(void){
  i2c_interrupt_enable(BASE, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, FALSE);
  BASE->ctrl1_bit.acken = false;
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
/**
 * @brief 
 * 
 */
void CoreSerialBusSlave::statusClear(void){
  i2c_type* base = BASE;
  __IO uint32_t tmpreg;
  tmpreg = base->sts1;
  tmpreg = base->sts2;
}

/* ****************************************************************************************
 * End of file
 */
