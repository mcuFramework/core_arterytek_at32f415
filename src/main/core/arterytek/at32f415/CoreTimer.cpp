/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */ 

#include "bsp_arterytek_at32f415/at32f4xx_tim.h"

#include "core/arterytek/at32f415/ctrl/CtrlInterrupt.hpp"
#include "core/arterytek/at32f415/CoreTimer.hpp"
 
/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreTimer;
using core::arterytek::at32f415::ctrl::CtrlInterrupt;
using mcuf::function::Consumer;

/* ****************************************************************************************
 * Macro
 */
#define GET_BASE()               ((TMR_Type*)this->mRegAddress)
#define BASE_CLEAR_PENDING(x, y) (x->STS=(uint16_t)~y)
#define BASE_GET_FLAG(x, y)      (((x->STS & y) != (uint16_t)RESET)?SET:RESET)

/* ****************************************************************************************
 * Extern
 */
extern CoreTimer* isr_at32f415_tmr_get(void* base);
extern void isr_at32f415_tmr_reg(void* base, core::arterytek::at32f415::CoreTimer* mem);

/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreTimer::CoreTimer(Registor reg){
  switch(reg){
    case CoreTimer::REG_TMR2:
      this->mRegAddress = TMR2;
      break;
    
    case CoreTimer::REG_TMR3:
      this->mRegAddress = TMR3;
      break;
    
    case CoreTimer::REG_TMR4:
      this->mRegAddress = TMR4;
      break;
    
    case CoreTimer::REG_TMR5:
      this->mRegAddress = TMR5;
      break;
    
    case CoreTimer::REG_TMR9:
      this->mRegAddress = TMR9;
      break;
    
    case CoreTimer::REG_TMR10:
      this->mRegAddress = TMR10;
      break;
    
    case CoreTimer::REG_TMR11:
      this->mRegAddress = TMR11;
      break;
    
    default:
      THROW_ERROR("out of enum index");
  }
  
  this->mAttachment = nullptr;
  this->mExecute = nullptr;
  return;
}

/**
 * 
 */
CoreTimer::~CoreTimer(void){
  return;
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

/**
 *
 */
bool CoreTimer::deinit(void){
  if(!this->isInit())
    return false;
  
  this->cancel();
  this->clockEnable(false);
  
  isr_at32f415_tmr_reg(this->mRegAddress, nullptr);
  return true;
}

/**
 * 
 */
void CoreTimer::cancel(void){
  this->interruptEnable(false);
  TMR_INTConfig(GET_BASE(), TMR_INT_Overflow, DISABLE);
  TMR_Cmd(GET_BASE(), DISABLE);
  
}

/**
 * 
 */
bool CoreTimer::isBusy(void){
  return false;
}

/**
 *
 */
bool CoreTimer::init(void){
  if(this->isInit())
    return false;
  
  this->clockEnable(true);
  TMR_Reset(GET_BASE());
  isr_at32f415_tmr_reg(GET_BASE(), this);
  return true;
}
  
/**
 *
 */
bool CoreTimer::isInit(void){
  return (isr_at32f415_tmr_get(this->mRegAddress) != nullptr);
}

/**
 * 
 */
bool CoreTimer::isDone(void){
  if(GET_BASE()->STS & TMR_STS_UEVIF){
		GET_BASE()->STS &= ~TMR_STS_UEVIF;
    return true;
  }
  
  return false;
}

/**
 * 
 */
uint32_t CoreTimer::getTickBaseMilliSecond(void){
  return (SystemCoreClock/100);
}

/**
 * 
 */
bool CoreTimer::startAtTick(uint32_t tick){
  if(this->isBusy())
    return false;
  
  this->mAttachment = nullptr;
  this->mExecute = nullptr;
  
  this->configTick(tick);
  
  TMR_Cmd(GET_BASE(), ENABLE);
  return true;
}

/**
 * 
 */
bool CoreTimer::startAtTick(uint32_t tick, void* attachment, Consumer<void*>* execute){
  if(this->isBusy())
    return false;
  
  this->mAttachment = attachment;
  this->mExecute = execute;
  
  this->configTick(tick);
  
  TMR_INTConfig(GET_BASE(), TMR_INT_Overflow, ENABLE);
  this->interruptEnable(true);
  TMR_Cmd(GET_BASE(), ENABLE);
  
  return true;
}


/**
 * 
 */
bool CoreTimer::startAtTime(uint32_t microSecond){
  if(this->isBusy())
    return false;
  
  this->mAttachment = nullptr;
  this->mExecute = nullptr;
  
  if(!this->configTime(microSecond))
    return false;
  
  TMR_Cmd(GET_BASE(), ENABLE);
  
  
  return true;
}

/**
 * 
 */
bool CoreTimer::startAtTime(uint32_t microSecond, void* attachment, Consumer<void*>* execute){
  if(this->isBusy())
    return false;
  
  this->mAttachment = attachment;
  this->mExecute = execute;
  
  if(!this->configTime(microSecond)){
    this->mAttachment = nullptr;
    this->mExecute = nullptr;
    return false;
  }
  
  TMR_INTConfig(GET_BASE(), TMR_INT_Overflow, ENABLE);
  this->interruptEnable(true);
  TMR_Cmd(GET_BASE(), ENABLE);
  
  return true;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreTimer::execute(void){
  if(this->mExecute == nullptr)
    return;
  
  this->mExecute->accept(this->mAttachment);
  return;
}

/**
 *
 */
void CoreTimer::interruptHandle(void){
  if(BASE_GET_FLAG(GET_BASE(), TMR_FLAG_Update) == RESET)
    return;
  
  BASE_CLEAR_PENDING(GET_BASE(), TMR_FLAG_Update);

  if(this->mExecute == nullptr)
    return;
      
  this->mExecute->accept(this->mAttachment);
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
 *
 */
void CoreTimer::clockEnable(bool enable){
  uint32_t mask;
  uint8_t busSel;
  
    switch((uint32_t)this->mRegAddress){
    case TMR1_BASE:
      mask = RCC_APB2PERIPH_TMR1;
      busSel = 1;
      break;
    
    case TMR2_BASE:
      mask = RCC_APB1PERIPH_TMR2;
      busSel = 0;
      break;
    
    case TMR3_BASE:
      mask = RCC_APB1PERIPH_TMR3;
      busSel = 0;
      break;
    
    case TMR4_BASE:
      mask = RCC_APB1PERIPH_TMR4;
      busSel = 0;
      break;
    
    case TMR5_BASE:
      mask = RCC_APB1PERIPH_TMR5;
      busSel = 0;
      break;
    
    case TMR9_BASE:
      mask = RCC_APB2PERIPH_TMR9;
      busSel = 1;
      break;
    
    case TMR10_BASE:
      mask = RCC_APB2PERIPH_TMR10;
      busSel = 1;
      break;
    
    case TMR11_BASE:
      mask = RCC_APB2PERIPH_TMR11;
      busSel = 1;
      break;
    
    default:
      THROW_ERROR("out of enum index");
  }
  
  if(busSel)
    RCC_APB2PeriphClockCmd(mask, (FunctionalState)enable);
  
  else
    RCC_APB1PeriphClockCmd(mask, (FunctionalState)enable);
  
  return;
}

/**
 *
 */
void CoreTimer::configTick(uint32_t tick){
  TMR_TimerBaseInitType config;
  TMR_TimeBaseStructInit(&config);
  config.TMR_DIV = 1 + (tick>>16);
  config.TMR_Period = (tick/config.TMR_DIV);
  config.TMR_ClockDivision = 0;
  config.TMR_CounterMode = TMR_CounterDIR_Up;
  
  TMR_TimeBaseInit(GET_BASE(), &config);
  return;
}
  
/**
 *
 */
bool CoreTimer::configTime(uint32_t microSecond){
  uint32_t timeUsBase = (SystemCoreClock/1000000);
  
  if(microSecond > (0xFFFFFFFF/timeUsBase))
    return false;
  
  this->configTick(microSecond * timeUsBase);
  return true;
}

/**
 *
 */
void CoreTimer::interruptEnable(bool enable){
  switch((uint32_t)this->mRegAddress){
    case TMR2_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR2, enable);
      return;
    
    case TMR3_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR3, enable);
      return;
    
    case TMR4_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR4, enable);
      return;
    
    case TMR5_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR5, enable);
      return;
    
    case TMR9_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR9, enable);
      return;
    
    case TMR10_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR10, enable);
      return;
    
    case TMR11_BASE:
      CtrlInterrupt::timer(CtrlInterrupt::IRQ_TMR11, enable);
      return;
    
    default:
      THROW_ERROR("out of enum index");
  }
}

/* ****************************************************************************************
 * End of file
 */ 
