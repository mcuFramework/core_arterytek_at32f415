/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"
#include "core_arterytek_at32f415.h"
#include "periph/usart/UsartNormalTest.h"

/* ****************************************************************************************
 * Macro
 */  

/* ****************************************************************************************
 * Using
 */  

using periph::usart::normal::UsartNormalTest;

using namespace mcuf::function;
using namespace mcuf::hal;
using namespace mcuf::io;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace mcuf::function;
using namespace core::arterytek::at32f415;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * Construct.
 */
UsartNormalTest::UsartNormalTest(Memory& memory, Stacker* stacker) construct Thread(memory){
  this->mStacker = stacker;
}

/**
 * Destruct.
 */
UsartNormalTest::~UsartNormalTest(void){
  
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
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 * 
 */
void UsartNormalTest::run(void){
  this->init();
  

  this->usart = new(*this->mStacker)CoreUsart(CoreUsart::REG_UART4, this->mStacker->allocMemory(128));
  usart->init();
  usart->baudrate(128000);
  
  this->txBuffer = new(*this->mStacker)ByteBuffer(this->mStacker->allocMemory(64));
  this->rxBuffer = new(*this->mStacker)ByteBuffer(this->mStacker->allocMemory(8));
  
  String s = String(this->mStacker->allocMemory(64));
  
  this->txBuffer->put("start\n");
  this->txBuffer->flip();
  this->usart->write(this->txBuffer, this);
  
  while(true){
    this->mLED[0]->setHigh();
    this->delay(500);
    this->mLED[0]->setLow();
    this->delay(500);
  }
}

/* ****************************************************************************************
 * Public Method <Override> mcuf::hal::SerialPortEvent::Event
 */
  
/**
 *
 */
void UsartNormalTest::onSerialPortEvent(SerialPortStatus status, mcuf::io::ByteBuffer* byteBuffer){
  switch(status){
    case HAL_SERIALPORT_WRITE_SUCCESSFUL:
      this->mLED[2]->setToggle();
      this->rxBuffer->reset();
      this->usart->read(this->rxBuffer, this);
      break;
    
    case HAL_SERIALPORT_WRITE_FAIL:
      this->mLED[3]->setToggle();
      break;
    
    case HAL_SERIALPORT_WRITE_ABROT:
      this->mLED[4]->setToggle();
      break;
    
    case HAL_SERIALPORT_READ_SUCCESSFUL:
      this->mLED[5]->setToggle();
      byteBuffer->flip();
      this->txBuffer->reset();
      this->txBuffer->put("rx is:");
      this->txBuffer->put(*byteBuffer);
      this->txBuffer->put("\n");
      this->txBuffer->flip();
      this->usart->write(this->txBuffer, this);
      break;
    
    case HAL_SERIALPORT_READ_FAIL:
      this->mLED[6]->setToggle();
      break;
    
    case HAL_SERIALPORT_READ_ABROT:
      this->mLED[7]->setToggle();
      break;
    
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
 
/**
 *
 */
void UsartNormalTest::init(void){
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLED[i] = new(this->mStacker->allocAlignment32(sizeof(CorePin))) CorePin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
  Core::gpioc.configOutput(10, CoreGpio::OutputMode_50M, false, true, true);
} 
 
/* ****************************************************************************************
 * End of file
 */ 
