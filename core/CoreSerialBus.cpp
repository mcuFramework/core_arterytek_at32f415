/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */

#include "./CoreSerialBus.h"

//-----------------------------------------------------------------------------------------
#include "../bsp/package-info.h"  
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./Core.h"
#include "./CoreInterrupt.h"

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<unsigned char>(this->mRegister))
#define CONFIG                   (CoreSerialBus::mConfig[REGNUMB])
#define BASE                     ((i2c_type*)CONFIG.mBase)

/* ****************************************************************************************
 * Using
 */

using core::CoreSerialBus;

//-----------------------------------------------------------------------------------------
using namespace hal;

//-----------------------------------------------------------------------------------------
using core::CoreSerialBusReg;
using core::CoreSerialBusConfig;
using mcuf::OutputBuffer;
using mcuf::InputBuffer;


/* ****************************************************************************************
 * Variable <Static>
 */
const CoreSerialBusConfig CoreSerialBus::mConfig[2] = {
  {I2C1 , CRM_I2C1_PERIPH_CLOCK , CoreInterrupt::IRQ_I2C1_EVT,  CoreInterrupt::IRQ_I2C1_ERR},
  {I2C2 , CRM_I2C2_PERIPH_CLOCK , CoreInterrupt::IRQ_I2C2_EVT,  CoreInterrupt::IRQ_I2C2_ERR},
};

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Serial Bus object
 * 
 * @param reg 
 */
CoreSerialBus::CoreSerialBus(CoreSerialBusReg reg) : 
  mCoreSerialBusErrorEvent(*this){
  this->mRegister = reg;
  this->mWriteBuffer = nullptr;
  this->mReadBuffer = nullptr;
  this->mResult = 0;
}

/**
 * @brief Destroy the Core Serial Bus object
 * 
 */
CoreSerialBus::~CoreSerialBus(void){
  this->deinit();
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - func::Runnable
 */
 
/**
 *
 */
void CoreSerialBus::run(void){
  SerialBusEvent* event = this->mEvent;
  SerialBusStatus status = this->mStatus;
  int result = this->mResult;
  
  if(event)
    event->onSerialBusEvent(status, *this);
}  

/* ****************************************************************************************
 * Public Method <Override> - hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreSerialBus::interruptEvent(void){
  i2c_type* base = BASE;
  
  if(base->ctrl2_bit.dataien){
    if(base->sts1_bit.tdbe){ //write isr
      char cache;
      if(this->mWriteBuffer->getByte(cache)){
        base->dt = cache;
        ++this->mResult;
      
      }else{
        if(base->sts1_bit.tdc){
          if(this->mReadBuffer){
            this->afterRead();
              
          }else{
            base->ctrl1_bit.genstop = true;
            base->ctrl2 &= ~static_cast<uint32_t>(I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT);
            this->mStatus = SerialBusStatus::WRITE_SUCCESSFUL;
            mcuf::System::execute(*this);
          }
        }
      }
    }
  }
  
  if(base->sts1_bit.rdbf){ //read isr
    char cache = base->dt;
    this->mReadBuffer->putByte(cache);
        
    if(this->mReadBuffer->remaining() == 1){
      base->ctrl1_bit.acken = false;
      base->ctrl1_bit.genstop = true;
          
    }else if(this->mReadBuffer->isFull()){ //read successful
      if(this->mStatus == SerialBusStatus::TRANSFER_FAIL_READ)
        this->mStatus = SerialBusStatus::TRANSFER_SUCCESSFUL;
      
      else
        this->mStatus = SerialBusStatus::READ_SUCCESSFUL;
      
      base->ctrl1_bit.genstop = true;
      base->ctrl2 &= ~static_cast<uint32_t>(I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT);
      mcuf::System::execute(*this);
        
    }
  }
   
  if(base->ctrl2_bit.evtien){
    if(base->sts1_bit.startf){  //address
      if(this->mDirect == Direct::WRITE)  //write
        base->dt = (this->mAddress & 0xFE);
    
      else  //read
        base->dt = (this->mAddress | 0x01);
      
    }else if(base->sts1_bit.addr7f){
      if(this->mDirect == Direct::WRITE) //enable receiver
        base->ctrl1_bit.acken = false;
      
      else
        base->ctrl1_bit.acken = true;
      
      this->statusClear();
    
    }
  }
}   

/* ****************************************************************************************
 * Public Method <Override> - hal::Base
 */

/**
 * @brief uninitialze hardware.
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialBus::deinit(void){
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
bool CoreSerialBus::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(static_cast<crm_periph_clock_type>(CONFIG.mCmr), TRUE);
  Core::interrupt.setHandler(CONFIG.mIrqEvent, this);
  Core::interrupt.setHandler(CONFIG.mIrqError, &this->mCoreSerialBusErrorEvent);
  
  Core::interrupt.irqEnable(CONFIG.mIrqEvent, true);
  Core::interrupt.irqEnable(CONFIG.mIrqError, true);
  
  i2c_init(BASE, I2C_FSMODE_DUTY_2_1, 100000);
  i2c_own_address1_set(BASE, I2C_ADDRESS_MODE_7BIT, 0x00);
  BASE->ctrl1_bit.i2cen = true;
  
  return true;
}

/**
 * @brief get hardware initialzed status.
 * 
 * @return true not init
 * @return false initd
 */
bool CoreSerialBus::isInit(void){
  return CRM_REG(CONFIG.mCmr) & CRM_REG_BIT(CONFIG.mCmr);
}

/* ****************************************************************************************
 * Public Method <Override> - hal::SerialBusControl
 */

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreSerialBus::getClockRate(void){
  if(!this->isInit())
    return 0;
  
  uint32_t result = 0;
  uint32_t i2c_clock = BASE->ctrl2_bit.clkfreq * 500000;
  result = i2c_clock /= BASE->clkctrl_bit.speed;
  return result;
}

/**
 * @brief 
 * 
 * @param clock 
 * @return uint32_t 
 */
uint32_t CoreSerialBus::setClockRate(uint32_t clock){
  if(!this->isInit())
    return 0;
  
  if(this->isBusy())
    return 0;
  
  BASE->ctrl1_bit.i2cen = false;
  uint32_t i2c_clock = BASE->ctrl2_bit.clkfreq * 1000000;
  BASE->clkctrl_bit.speed = (uint16_t)(i2c_clock / (clock << 1));
  BASE->ctrl1_bit.i2cen = true;
  return this->getClockRate();
}

/**
 * @brief 設定讀寫地址
 * 
 * @param address 讀寫地址
 * @return uint16_t 實際設定之讀寫地址
 */
uint16_t CoreSerialBus::setAddress(uint16_t address){
  if(!this->isBusy())
    this->mAddress = (address & 0x00FF);
  
  return this->mAddress;
}

/**
 * @brief 取得已被設定之讀寫地址
 * 
 * @return uint16_t 地址
 */
uint16_t CoreSerialBus::getAddress(void){
  return this->mAddress;
}
  
/**
 * @brief Set the Write Buffer object
 * 
 * @param writeBuffer 
 * @return mcuf::ByteBuffer* 
 */
mcuf::ByteBuffer* CoreSerialBus::setWriteBuffer(mcuf::ByteBuffer* writeBuffer){
  mcuf::ByteBuffer* result = this->mWriteBuffer;
  
  if(!this->isBusy())
    this->mWriteBuffer = writeBuffer;
  
  return result;
}
  
/**
 * @brief Get the Write Buffer object
 * 
 * @return mcuf::ByteBuffer* 
 */
mcuf::ByteBuffer* CoreSerialBus::getWriteBuffer(void){
  return this->mWriteBuffer;
}

/**
 * @brief Set the Read Buffer object
 * 
 * @param readBuffer 
 * @return mcuf::ByteBuffer* 
 */
mcuf::ByteBuffer* CoreSerialBus::setReadBuffer(mcuf::ByteBuffer* readBuffer){
  mcuf::ByteBuffer* result = this->mReadBuffer;
  
  if(!this->isBusy())
    this->mReadBuffer = readBuffer;
  
  return result;
}

/**
 * @brief Get the Read Buffer object
 * 
 * @return mcuf::ByteBuffer* 
 */
mcuf::ByteBuffer* CoreSerialBus::getReadBuffer(void){
  return this->mReadBuffer;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialBus::abort(void){
  if(this->isBusy())
    return false;
  
  BASE->ctrl1_bit.acken = false;
  BASE->ctrl1_bit.genstop = true;
  
  i2c_interrupt_enable(BASE, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, FALSE); 
  this->statusClear();
  BASE->sts1 = 0;
  
  System::execute(*this);
  return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialBus::isBusy(void){
  return false;
}

/**
 * @brief 
 * 
 * @param address 
 * @param receiver 
 * @param event 
 */
bool CoreSerialBus::read(SerialBusEvent* event){
  return this->handlerConfig(event);
}
/**
 * @brief 
 * 
 * @param address 
 * @param receiver 
 * @param event 
 */
bool CoreSerialBus::write(SerialBusEvent* event){
  return this->handlerConfig(event);
}

/**
 * @brief 
 * 
 * @param address 
 * @param transfer 
 * @param receiver 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreSerialBus::transfer(SerialBusEvent* event){
  return this->handlerConfig(event);
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

/**
 * @brief 
 * 
 * @param address 
 * @param out 
 * @param in 
 * @param attachment 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreSerialBus::handlerConfig(SerialBusEvent* event){
  
  this->mEvent = event;
  
  if((this->mWriteBuffer != nullptr) && (this->mReadBuffer != nullptr)){
    this->mStatus = SerialBusStatus::TRANSFER_FAIL_WRITE;
    if(this->mWriteBuffer->avariable() <= 0)
      return false;
    
    if(this->mReadBuffer->remaining() <= 0)
      return false;
    
    this->mDirect = Direct::WRITE;
  
  }else if(this->mWriteBuffer != nullptr){
    this->mStatus = SerialBusStatus::WRITE_FAIL;
    if(this->mWriteBuffer->avariable() <= 0)
      return false;
    
    this->mDirect = Direct::WRITE;
    
  }else if(this->mReadBuffer != nullptr){
    this->mStatus = SerialBusStatus::READ_FAIL;
    if(this->mReadBuffer->remaining() <= 0)
      return false;
    
    this->mDirect = Direct::READ;
  }
  
  if(this->begin())
    return true;
  
  BASE->ctrl1_bit.acken = false;
  BASE->ctrl1_bit.genstop = true;
  
  System::execute(*this);
  return false;  
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialBus::begin(void){
  i2c_interrupt_enable(BASE, I2C_EVT_INT | I2C_DATA_INT | I2C_ERR_INT, TRUE);
  BASE->ctrl1_bit.acken = false;
  BASE->ctrl1_bit.genstart = true;
  return true;
}

/**
 * @brief 
 * 
 */
void CoreSerialBus::statusClear(void){
  i2c_type* base = BASE;
  __IO uint32_t tmpreg;
  tmpreg = base->sts1;
  tmpreg = base->sts2;
}

/**
 * @brief 
 * 
 */
void CoreSerialBus::afterRead(void){
  this->mStatus = SerialBusStatus::TRANSFER_FAIL_READ;
  this->mDirect = Direct::READ;
  this->begin();
}

/* ****************************************************************************************
 * End of file
 */
