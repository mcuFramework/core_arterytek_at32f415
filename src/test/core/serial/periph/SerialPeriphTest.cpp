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
#include "core/serial/periph/SerialPeriphTest.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------
using namespace tool;
using namespace core::arterytek::at32f415::serial::periph;
using namespace mcuf::hal::serial::periph;
//-----------------------------------------------------------------------------------------
using core::serial::periph::SerialPeriphTest;

using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreIomux;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using core::arterytek::at32f415::general::port::OutputMode;

using mcuf::io::ByteBuffer;

using mcuf::util::Stacker;




/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 *
 */
SerialPeriphTest::SerialPeriphTest(Stacker& stacker) construct
  mStacker(stacker){
}
  
/**
 *
 */
SerialPeriphTest::~SerialPeriphTest(void){
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 *
 */
void SerialPeriphTest::run(void){
  this->init();
  
  this->mConsole->out().format("memory using :");
  this->mConsole->out().println(mStacker.size());
  
  SerialPeriphPacket packet;
  packet.tx = this->mTransferByteBuffer;
  packet.rx = this->mReceiverByteBuffer;
  packet.clock = 10000000;
  packet.polarity = SerialPeriphPolarity::ACTIVE_LOW;
  packet.phase = SerialPeriphPhase::SECOND_EDGE;
  packet.significantBit = SerialPeriphSignificantBit::MSB;
  
  
  while(true){
    this->delay(1000);
    this->formatBuffer();
    this->mBoardPeriph->led[0].setToggle();
    this->mConsole->out().println("SPI2 Write");
    this->mCoreSerialPeriph->transfer(0, &packet, this);
  }

}

/* ****************************************************************************************
 * Public Method <Override> mcuf::hal::serial::periph::SerialPeriphEvent
 */

/**
 * @brief 
 * 
 * @param status 
 * @param transfer 
 * @param receiver 
 */
void SerialPeriphTest::onSerialPeriphEvent(SerialPeriphStatus status, 
                                           ByteBuffer* transfer, 
                                           ByteBuffer* receiver){

  if(status == SerialPeriphStatus::SUCCESSFUL){
    this->mConsole->out().println("SPI2 Write successful");
    this->showBuffer();
  }else{
    this->mConsole->out().println("SPI2 Write fail");
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
void SerialPeriphTest::init(void){
  this->mBoardPeriph = new(this->mStacker) BoardPeriph();
  this->mConsole = new(this->mStacker) Console();
  
  this->mTransferByteBuffer = new(this->mStacker) ByteBuffer(this->mStacker.allocMemoryAlignment32(16));
  this->mReceiverByteBuffer = new(this->mStacker) ByteBuffer(this->mStacker.allocMemoryAlignment32(16));
  
  this->mCoreSerialPeriph = new(this->mStacker) CoreSerialPeriph(CoreSerialPeriphReg::REG_SPI1);
  this->mCoreSerialPeriph->init();
  
  for(int i=0; i<4; ++i){
    this->mChipSelectPin[i] = new(this->mStacker) CoreGeneralPin(&Core::gpiob, 8 + i);
    this->mChipSelectPin[i]->setOutput();
    this->mChipSelectPin[i]->setHigh();
    this->mCoreSerialPeriph->setChipSelectPin(i, this->mChipSelectPin[i]);
  }
  Core::iomux.remapSPI2(CoreIomux::MapSPI2::PB12_PB13_PB14_PB15_PC06);
  Core::gpioa.setFunction(5, false);
  Core::gpioa.setFunction(7, false);
}

/**
 *
 */
void SerialPeriphTest::formatBuffer(void){
  this->mTransferByteBuffer->clear();
  this->mTransferByteBuffer->put("12345678");
  this->mTransferByteBuffer->flip();
  this->mTransferByteBuffer->mark();
  
  this->mReceiverByteBuffer->clear();
  this->mReceiverByteBuffer->limit(this->mTransferByteBuffer->limit() - 4);
  this->mReceiverByteBuffer->mark();
}

/**
 *
 */
void SerialPeriphTest::showBuffer(void){
  this->mTransferByteBuffer->reset();
  this->mConsole->out().format("Transfer buffer (%d) :\n", this->mTransferByteBuffer->remaining());
  
  while(this->mTransferByteBuffer->hasRemaining()){
    char cache;
    this->mTransferByteBuffer->getByte(cache);
    this->mConsole->out().format("0x%02X ", cache);
  }
  
  this->mConsole->out().println();
  
  this->mReceiverByteBuffer->reset();
  this->mConsole->out().format("Receiver buffer (%d) :\n", this->mReceiverByteBuffer->remaining());
  
  while(this->mReceiverByteBuffer->hasRemaining()){
    char cache;
    this->mReceiverByteBuffer->getByte(cache);
    this->mConsole->out().format("0x%02X ", cache);
  }
  
  this->mConsole->out().println();  
}

/* ****************************************************************************************
 * End of file
 */
