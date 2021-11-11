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

#include "core/arterytek/at32f415/Core.hpp"
#include "core/arterytek/at32f415/CoreInterrupt.hpp"
#include "core/arterytek/at32f415/CoreTimer.hpp"

/* ****************************************************************************************
 * Namespace
 */ 
namespace core{
  namespace arterytek{
    namespace at32f415{
      
      struct CoreTimerConfig{
        void* Register;
        volatile uint32_t* clock;
        uint32_t clockMask;
        CoreInterrupt::Irq irq;
        
      }const coreTimerConfig[8] = {
        {TMR1 , &RCC->APB2EN, RCC_APB2PERIPH_TMR1 , CoreInterrupt::IRQ_TMR1 },
        {TMR2 , &RCC->APB1EN, RCC_APB1PERIPH_TMR2 , CoreInterrupt::IRQ_TMR2 },
        {TMR3 , &RCC->APB1EN, RCC_APB1PERIPH_TMR3 , CoreInterrupt::IRQ_TMR3 },
        {TMR4 , &RCC->APB1EN, RCC_APB1PERIPH_TMR4 , CoreInterrupt::IRQ_TMR4 },
        {TMR5 , &RCC->APB1EN, RCC_APB1PERIPH_TMR5 , CoreInterrupt::IRQ_TMR5 },
        {TMR9 , &RCC->APB2EN, RCC_APB2PERIPH_TMR9 , CoreInterrupt::IRQ_TMR9 },
        {TMR10, &RCC->APB2EN, RCC_APB2PERIPH_TMR10, CoreInterrupt::IRQ_TMR10},
        {TMR11, &RCC->APB2EN, RCC_APB2PERIPH_TMR11, CoreInterrupt::IRQ_TMR11},
      };
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreInterrupt;
using core::arterytek::at32f415::CoreTimer;
using mcuf::function::Consumer;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                   (coreTimerConfig[this->mRegister])
#define BASE                     ((TMR_Type*)CONFIG.Register)
#define BASE_CLEAR_PENDING(x, y) (x->STS=(uint16_t)~y)
#define BASE_GET_FLAG(x, y)      (((x->STS & y) != (uint16_t)RESET)?SET:RESET)

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreTimer::CoreTimer(Register reg){
  this->mRegister = reg;
  this->mEvent = nullptr;
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
  
  *CONFIG.clock &= ~CONFIG.clockMask;
  return true;
}

/**
 * 
 */
void CoreTimer::cancel(void){
  this->interruptEnable(false);
  TMR_INTConfig(BASE, TMR_INT_Overflow, DISABLE);
  TMR_Cmd(BASE, DISABLE);
  
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

  *CONFIG.clock |= CONFIG.clockMask;
  Core::interrupt.setHandler(CONFIG.irq, this);
  return true;
}
  
/**
 *
 */
bool CoreTimer::isInit(void){
  return *CONFIG.clock & CONFIG.clockMask;
}

/**
 * 
 */
bool CoreTimer::isDone(void){
  if(BASE->STS & TMR_STS_UEVIF){
		BASE->STS &= ~TMR_STS_UEVIF;
    return true;
  }
  
  return false;
}

/**
 * 
 */
uint32_t CoreTimer::getTickBaseMilliSecond(void){
  return (Core::getSystemCoreClock()/100);
}

/**
 *
 */
void CoreTimer::run(void){
  if(BASE_GET_FLAG(BASE, TMR_FLAG_Update) == RESET)
    return;
  
  BASE_CLEAR_PENDING(BASE, TMR_FLAG_Update);

  if(this->mEvent == nullptr)
    return;
      
  this->mEvent->onTimerEvent(Event::TRIGGER);
  return;
}

/**
 * 
 */
bool CoreTimer::startAtTick(uint32_t tick){
  if(this->isBusy())
    return false;
  
  this->mEvent = nullptr;
  
  this->configTick(tick);
  
  TMR_Cmd(BASE, ENABLE);
  return true;
}

/**
 * 
 */
bool CoreTimer::startAtTick(uint32_t tick, Event* event){
  if(this->isBusy())
    return false;
  
  this->mEvent = event;
  
  this->configTick(tick);
  
  TMR_INTConfig(BASE, TMR_INT_Overflow, ENABLE);
  this->interruptEnable(true);
  TMR_Cmd(BASE, ENABLE);
  
  return true;
}


/**
 * 
 */
bool CoreTimer::startAtTime(uint32_t microSecond){
  if(this->isBusy())
    return false;
  
  this->mEvent = nullptr;
  
  if(!this->configTime(microSecond))
    return false;
  
  TMR_Cmd(BASE, ENABLE);
  
  return true;
}

/**
 * 
 */
bool CoreTimer::startAtTime(uint32_t microSecond, Event* event){
  if(this->isBusy())
    return false;
  
  this->mEvent = event;
  
  if(!this->configTime(microSecond)){
    this->mEvent = nullptr;
    return false;
  }
  
  TMR_INTConfig(BASE, TMR_INT_Overflow, ENABLE);
  this->interruptEnable(true);
  TMR_Cmd(BASE, ENABLE);
  
  return true;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
void CoreTimer::execute(void){
  if(this->mEvent == nullptr)
    return;
  
  this->mEvent->onTimerEvent(Event::TRIGGER);
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
void CoreTimer::configTick(uint32_t tick){
  TMR_TimerBaseInitType config;
  TMR_TimeBaseStructInit(&config);
  config.TMR_DIV = 1 + (tick>>16);
  config.TMR_Period = (tick/config.TMR_DIV);
  config.TMR_ClockDivision = 0;
  config.TMR_CounterMode = TMR_CounterDIR_Up;
  
  TMR_TimeBaseInit(BASE, &config);
  return;
}
  
/**
 *
 */
bool CoreTimer::configTime(uint32_t microSecond){
  uint32_t timeUsBase = (Core::getSystemCoreClock()/1000000);
  
  if(microSecond > (0xFFFFFFFF/timeUsBase))
    return false;
  
  this->configTick(microSecond * timeUsBase);
  return true;
}

/**
 *
 */
void CoreTimer::interruptEnable(bool enable){
  Core::interrupt.irqHandler(CONFIG.irq, enable);
  return;
}

/* ****************************************************************************************
 * End of file
 */ 
