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
#include "start/Main.hpp"
#include "start/SpeedReader.hpp"
#include "start/CommandWriteTask.hpp"


/* ****************************************************************************************
 * Using
 */  


using mcuf::lang::managerment::MemoryManager;
using mcuf::function::Runnable;
using mcuf::function::ConsumerEvent;

using namespace start;
using namespace mcuf::io::channel;
using namespace mcuf::lang;
using namespace mcuf::util;
using namespace core::arterytek::at32f415;



/* ****************************************************************************************
 * Namespace
 */  

class PulseGen extends TimerTask{
  private: CorePin* mPin;
  
  public: PulseGen(CorePin* pin){
    this->mPin = pin;
  }
  public: virtual ~PulseGen() = default;
  
  public: void run(void){
    mPin->setToggle();
  }
};

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Operator Method
 */

/**
 * Construct.
 */
Main::Main(void) construct Thread("mainThread"){
  
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
 * Public Method <Override>
 */

/**
 *
 */
void Main::run(void){
  this->initGPIO();
  
  Memory* memory = new HeapMemory(128);
  this->usart = new CoreUSART(CoreUSART::REG_UART4, *memory);
  usart->init();
  
  this->mCommandWriteTask = new CommandWriteTask(*this->usart);
  ByteBuffer* mByteBuffer = new HeapByteBuffer(128);
  mByteBuffer->limit(10);
  this->usart->read(*mByteBuffer, this);
  
  PulseGen *mPulseGen = new PulseGen(this->mLED[1]);
  System::getTimer().scheduleAtFixedRate(*mPulseGen, 10, 10);
  
  
  while(1){
    this->mLED[0]->setToggle();
    this->delay(1000);
    for(int i=0; i<10; i++){
      this->mSpeedReader[i]->recode();
      this->mCommandWriteTask->mData[i] = this->mSpeedReader[i]->getValue();
    }
  }
}

/* ****************************************************************************************
 * Public Method <Override>
 */

/** 
 *
 */
void Main::accept(ByteBuffer& byteBuffer){
  uint8_t* array = byteBuffer.lowerArray();
  if(array[3] == 0x03){
    if(array[2] == 0x00){
      this->mCommandWriteTask->writeConnect();
    }else if(array[2] == 0x01){
      this->mCommandWriteTask->writeData();
    }
  }
  
  byteBuffer.reset();
  byteBuffer.limit(10);
  usart->read(byteBuffer, this);
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
void Main::initGPIO(void){
  Core::gpiob.init();
  Core::gpioc.init();
  Core::afio.init();
  Core::afio.remapDEBUG(Core::afio.DEBUG_JTAGDISABLE);
  
  for(int i=0; i<8; i++){
    this->mLED[i] = new CorePin(&Core::gpiob, i);
    this->mLED[i]->setOutput();
    this->mLED[i]->setLow();
  }
  
  for(int i=0; i<10; i++){
    this->mEXTI[i] = new CorePin(&Core::gpioc, i);
    this->mEXTI[i]->setInput();
    this->mEXTI[i]->pinMode(this->mEXTI[i]->PinMode_Pullup);
    Core::afio.remapEXTI(Core::afio.EXTI_PC, i);
    this->mSpeedReader[i] = new SpeedReader(static_cast<CoreEXTI::Register>(CoreEXTI::REG_EXTI0 + i));
  }
  
  Core::gpioc.configOutput(10, CoreGPIO::OutputMode_50M, false, true, true);
}
 
/* ****************************************************************************************
 * End of file
 */ 
