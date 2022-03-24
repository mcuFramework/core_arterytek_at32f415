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
  
  Core::gpiob.setFunction(6, true);
  Core::gpiob.setFunction(7, true);
  
  CoreSerialBus coreSerialBus = CoreSerialBus(CoreSerialBusReg::REG_IIC1);
  coreSerialBus.init();
  
  uint8_t buffer[4];
  ByteBuffer byteBuffer = ByteBuffer(Memory(buffer, 4));
  byteBuffer << "1234";
  byteBuffer.remaining();
  
  while(true){
    coreSerialBus.write(0xAA, byteBuffer, nullptr, nullptr);
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
