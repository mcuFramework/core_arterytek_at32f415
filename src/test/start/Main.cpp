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
#include "core/analog/package-info.h"
#include "core/serial/package-info.h"
#include "core/counter/package-info.h"
#include "tool/package-info.h"

/* ****************************************************************************************
 * Using
 */  
using namespace start;

using namespace core::arterytek::at32f415;
using namespace core::arterytek::at32f415::general::pin;
using namespace core::arterytek::at32f415::serial::bus;

using namespace core::analog::input;
using namespace core::counter::pulse;
using namespace core::serial::port;
using namespace core::serial::periph;
using namespace tool;

using namespace mcuf::io;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace mcuf::hal::general::pin;
using namespace mcuf::hal::serial::bus;

//-----------------------------------------------------------------------------------------
using mcuf::function::Runnable;
using mcuf::lang::Memory;

using mcuf::hal::general::pin::GeneralPinMode;

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
Main::Main(Memory& memory, Memory& stacker) construct Thread(memory), mStacker(stacker){
}

/**
 * Destruct.
 */
Main::~Main(void){
}


/* ****************************************************************************************
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 *
 */
void Main::onSerialBusEvent(SerialBusStatus status, int result, void* attachment){
  switch(status){
    case SerialBusStatus::WRITE_SUCCESSFUL:
      this->mLed[0]->setHigh();
      break;
    case SerialBusStatus::WRITE_FAIL:
      this->mLed[1]->setHigh();
      break;
    case SerialBusStatus::READ_SUCCESSFUL:
      this->mLed[2]->setHigh();
      break;
    case SerialBusStatus::READ_FAIL:
      this->mLed[3]->setHigh();
      break;
  }
}

/**
 * 
 */
void Main::run(void){
  //Runnable* runnable = new(this->mStacker) PulseWidthTest(this->mStacker);
  //Runnable* runnable = new(this->mStacker) CoreAnalogInputTest(this->mStacker);
  //Runnable* runnable = new(this->mStacker) SerialPortTest(this->mStacker);
  //Runnable* runnable = new(this->mStacker) SerialPeriphTest(this->mStacker);
  
  //runnable->run();
  
  Core::iomux.init();
  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::gpiod.init();
  Core::gpiof.init();
  Core::iomux.remapSWDIO(CoreIomux::MapSWDIO::JTAGDISABLE);
  
  for(int i=0; i<6; ++i){
    this->mLed[i] = new(this->mStacker) CoreGeneralPin(&Core::gpiob, i);
    this->mLed[i]->setOutput();
    this->mLed[i]->setLow();
  }

  CoreGeneralPin wak = CoreGeneralPin(&Core::gpioa, 0);
  wak.setInput();
  wak.pinMode(GeneralPinMode::PULL_UP);
  
  Core::gpiob.setFunction(6, true);
  Core::gpiob.setFunction(7, true);
  
  coreSerialBus = new(this->mStacker)CoreSerialBus(CoreSerialBusReg::REG_IIC1);
  coreSerialBus->init();
  
  uint8_t buffer[16];
  uint8_t buffer_read[16];
  ByteBuffer byteBuffer = ByteBuffer(Memory(buffer, 16));
  byteBuffer << "12345678";
  byteBuffer.flip();
  
  ByteBuffer byteBufferRead = ByteBuffer(Memory(buffer_read, 16));
  byteBufferRead.limit(8);
  
  while(true){

    this->mLed[5]->setHigh();
    
    while(true){
      if(wak.value() == 0)
        break;
    }
    
    for(int i=0; i<6; ++i){
      this->mLed[i]->setLow();
    }
    
    byteBuffer = 0;
    byteBufferRead = 0;
    coreSerialBus->writeAfterRead(0xA0, byteBuffer, byteBufferRead, nullptr, this);
    //coreSerialBus->read(0xA0, byteBufferRead, nullptr, this);
    this->delay(1000);
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

/* ****************************************************************************************
 * End of file
 */ 
