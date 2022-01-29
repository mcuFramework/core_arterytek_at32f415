/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

//__asm(".global __use_no_semihosting_swi");
//__asm(".global __use_no_semihosting");

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "start/Main.h"


/* ****************************************************************************************
 * Using
 */  


using mcuf::function::Runnable;
using mcuf::function::ConsumerEvent;

using namespace start;
using namespace mcuf::io;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace mcuf::function;
using namespace core::arterytek::at32f415;


/* ****************************************************************************************
 * Namespace
 */  

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Operator Method
 */

/**
 * Construct.
 */
Main::Main(Memory& memory, Memory& stacker) construct Thread(memory), 
  mStacker(stacker){
    
  this->mStatus = 0;
}

/**
 * Destruct.
 */
Main::~Main(void){
  
}

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 * 
 */
void Main::run(void){
  this->initGPIO();
  

  this->usart = new(this->mStacker)CoreUsart(CoreUsart::REG_UART4, this->mStacker.allocMemory(128));
  usart->init();
  usart->baudrate(128000);
  
  this->txBuffer = new(this->mStacker)ByteBuffer(this->mStacker.allocMemory(64));
  this->rxBuffer = new(this->mStacker)ByteBuffer(this->mStacker.allocMemory(8));
  
  String s = String(this->mStacker.allocMemory(64));
  
  CoreTimer t = CoreTimer(CoreTimer::REG_TMR2);
  t.init();
  t.startAtTime(100000, this);
  
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
 * Public Method <Override> mcuf::hal::Timer::Event
 */

/**
 *
 */
void Main::onTimerEvent(TimerStatus status){
  this->mLED[1]->setToggle();
}
/* ****************************************************************************************
 * Public Method <Override> mcuf::hal::SerialPortEvent::Event
 */
  
/**
 *
 */
void Main::onSerialPortEvent(SerialPortStatus status, mcuf::io::ByteBuffer* byteBuffer){
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

/**
 *
 */
void Main::initGPIO(void){
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLED[i] = new(this->mStacker.allocAlignment32(sizeof(CorePin))) CorePin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
  
  Core::gpioc.configOutput(10, CoreGpio::OutputMode_50M, false, true, true);
  
}

/* ****************************************************************************************
 * End of file
 */ 
