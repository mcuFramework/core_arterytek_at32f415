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
#include "core/counter/pulse/PulseWidthTest.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------
using namespace tool;

//-----------------------------------------------------------------------------------------
using core::counter::pulse::PulseWidthTest;
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::general::pin::CoreGeneralPin;
using core::arterytek::at32f415::general::port::CoreGeneralPort;
using core::arterytek::at32f415::general::port::OutputMode;
using core::arterytek::at32f415::counter::pulse::CorePulseWidthPort;
using core::arterytek::at32f415::counter::pulse::CorePulseWidthPortSoft;
using core::arterytek::at32f415::counter::pulse::CorePulseWidthReg;
using mcuf::util::Stacker;
using mcuf::lang::Memory;
using mcuf::lang::System;

using mcuf::io::SerialPortOutputStream;
using mcuf::io::OutputStreamBuffer;
using mcuf::io::PrintStream;
using mcuf::io::ByteBuffer;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */
 
/**
 *
 */
PulseWidthTest::PulseWidthTest(Stacker& stacker) construct mStacker(stacker){
  return;
}

/**
 *
 */
PulseWidthTest::~PulseWidthTest(void){
  return;
}

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */

/**
 *
 */
void PulseWidthTest::run(void){
  this->init();
  this->mCorePulseWidthPortSoft->init();
  this->mCorePulseWidthPortSoft->setPin(0, this->mPulseFanOut);
  this->mCorePulseWidthPortSoft->setPin(1, this->mPulseMT3608);
  
  uint32_t hz = 50000;
  
  this->mCorePulseWidthPortSoft->setFrequence(hz);
  this->mCorePulseWidthPortSoft->enable(0);
  this->mCorePulseWidthPortSoft->setDuty(0, 0.5);
  this->mCorePulseWidthPortSoft->enable(1);
  this->mCorePulseWidthPortSoft->setDuty(1, 0.1);

 
  
  while(true){
    /**
    this->mLedPowerG->setHigh();
    this->delay(500);
    this->mLedPowerG->setLow();
    this->mLedPowerR->setHigh();
    this->delay(500);
    this->mLedPowerR->setLow();
    this->mLedPowerB->setHigh();
    this->delay(500);
    this->mLedPowerB->setLow();
    this->mLedStatusG->setHigh();
    this->delay(500);
    this->mLedStatusG->setLow();
    this->mLedStatusR->setHigh();
    this->delay(500);
    this->mLedStatusR->setLow();
    this->mLedStatusB->setHigh();
    this->delay(500);
    this->mLedStatusB->setLow();
    */
    
    for(int i=0; i<8; ++i){
      this->mCorePulseWidthPortSoft->setDuty(1, 0.05 * (1 + i));
      this->mLedPowerG->setToggle();
      this->delay(500);
    }
    
    for(int i=0; i<8; ++i){
      this->mCorePulseWidthPortSoft->setDuty(1, 0.05 * (9 - i));
      this->mLedPowerR->setToggle();
      this->delay(500);
    }
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
void PulseWidthTest::init(void){
  //this->mBoardPeriph = new(this->mStacker) BoardPeriph();
  //this->mConsole = new(this->mStacker) Console();

  Core::gpioa.init();
  Core::gpiob.init();
  Core::gpioc.init();
  Core::gpiod.init();
  Core::gpiof.init();
  Core::iomux.init();
  Core::iomux.remapDEBUG(Core::iomux.DEBUG_JTAGDISABLE);
  
  this->mCorePulseWidthPortSoft = new(this->mStacker) CorePulseWidthPortSoft(CorePulseWidthReg::REG_TMR3);
  
  this->mPulseFanOut = new(this->mStacker) CoreGeneralPin(&Core::gpiob, 0);
  this->mPulseFanOut->setOutput();
  this->mPulseFanOut->setLow();
  
  this->mPulseMT3608 = new(this->mStacker) CoreGeneralPin(&Core::gpioc, 5);
  this->mPulseMT3608->setOutput();
  this->mPulseMT3608->setLow();
  
  this->mLedPowerG   = new(this->mStacker) CoreGeneralPin(&Core::gpiob, 12);
  this->mLedPowerG->setOutput();
  this->mLedPowerG->setLow();
  
  this->mLedPowerR   = new(this->mStacker) CoreGeneralPin(&Core::gpiob, 13);
  this->mLedPowerR->setOutput();
  this->mLedPowerR->setLow();
  
  this->mLedPowerB   = new(this->mStacker) CoreGeneralPin(&Core::gpiob, 14);
  this->mLedPowerB->setOutput();
  this->mLedPowerB->setLow();
  
  this->mLedStatusG   = new(this->mStacker) CoreGeneralPin(&Core::gpioc, 4);
  this->mLedStatusG->setOutput();
  this->mLedStatusG->setLow();
  
  this->mLedStatusR   = new(this->mStacker) CoreGeneralPin(&Core::gpioa, 6);
  this->mLedStatusR->setOutput();
  this->mLedStatusR->setLow();
  
  this->mLedStatusB   = new(this->mStacker) CoreGeneralPin(&Core::gpioa, 7);
  this->mLedStatusB->setOutput();
  this->mLedStatusB->setLow();
}

/* ****************************************************************************************
 * End of file
 */
