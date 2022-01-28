/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */ 

#include "bsp_arterytek_at32f415/at32f415.h"

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
        crm_periph_clock_type crmClock;
        CoreInterrupt::Irq irq;
        
      }const coreTimerConfig[8] = {
        {TMR1 , CRM_TMR1_PERIPH_CLOCK , CoreInterrupt::IRQ_TMR1 },
        {TMR2 , CRM_TMR2_PERIPH_CLOCK , CoreInterrupt::IRQ_TMR2 },
        {TMR3 , CRM_TMR3_PERIPH_CLOCK , CoreInterrupt::IRQ_TMR3 },
        {TMR4 , CRM_TMR4_PERIPH_CLOCK , CoreInterrupt::IRQ_TMR4 },
        {TMR5 , CRM_TMR5_PERIPH_CLOCK , CoreInterrupt::IRQ_TMR5 },
        {TMR9 , CRM_TMR9_PERIPH_CLOCK , CoreInterrupt::IRQ_TMR9 },
        {TMR10, CRM_TMR10_PERIPH_CLOCK, CoreInterrupt::IRQ_TMR10},
        {TMR11, CRM_TMR11_PERIPH_CLOCK, CoreInterrupt::IRQ_TMR11},
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
using mcuf::hal::TimerEvent;

/* ****************************************************************************************
 * Macro
 */
#define CONFIG                   (coreTimerConfig[this->mRegister])
#define BASE                     ((tmr_type*)CONFIG.Register)

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
 * Public Method <Override> mcuf::hal::Base
 */

/**
 * uninitialze hardware.
 */
bool CoreTimer::deinit(void){
	if(!this->isInit())
		return false;
	
  this->interruptEnable(false);
  Core::interrupt.setHandler(CONFIG.irq, nullptr);
	return true;
}

/**
 * initialze hardware;
 */
bool CoreTimer::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(CONFIG.crmClock, TRUE);
  Core::interrupt.setHandler(CONFIG.irq, this);
  return false;
}

/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreTimer::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override> mcuf::hal::Timer
 */

/**
 * 
 */
void CoreTimer::cancel(void){
  this->interruptEnable(false);
  tmr_interrupt_enable(BASE, TMR_OVF_INT, FALSE);
  tmr_counter_enable(BASE, FALSE);
  
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
bool CoreTimer::isDone(void){
  if(BASE->ists_bit.ovfif){
		BASE->ists_bit.ovfif = 0;
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
bool CoreTimer::startAtTick(uint32_t tick){
  return this->startAtTick(tick, nullptr);
}

/**
 * 
 */
bool CoreTimer::startAtTick(uint32_t tick, TimerEvent* event){
  if(this->isBusy())
    return false;
  
  if(tick == 0)
    return false;
  
  this->mEvent = event;
  
  this->configTick(tick);
  
  tmr_cnt_dir_set(BASE, TMR_COUNT_UP);
  tmr_clock_source_div_set(BASE, TMR_CLOCK_DIV1);
  
  if(event != nullptr){
    tmr_interrupt_enable(BASE, TMR_OVF_INT, TRUE);
    this->interruptEnable(true);
  }
  
  tmr_counter_enable(BASE, TRUE);
  
  return true;
}


/**
 * 
 */
bool CoreTimer::startAtTime(uint32_t microSecond){
  return this->startAtTick(this->getTickAtMicroSecond(microSecond), nullptr);
}

/**
 * 
 */
bool CoreTimer::startAtTime(uint32_t microSecond, TimerEvent* event){
  return this->startAtTick(this->getTickAtMicroSecond(microSecond), event);
}

/* ****************************************************************************************
 * Public Method <Override> mcuf::function::Runnable
 */

/**
 *
 */
void CoreTimer::run(void){
  if(tmr_flag_get(BASE, TMR_OVF_FLAG) == RESET)
    return;
  
  tmr_flag_clear(BASE, TMR_OVF_FLAG);

  if(this->mEvent == nullptr)
    return;
      
  this->mEvent->onTimerEvent(TimerEvent::HAL_TIMER_TRIGGER);
  return;
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
  
  this->mEvent->onTimerEvent(TimerEvent::HAL_TIMER_TRIGGER);
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
  uint32_t div = 1 + (tick>>16);
  uint32_t period = (tick/div);  
  
  tmr_base_init(BASE, period, div);
  return;
}
  
/**
 *
 */
uint32_t CoreTimer::getTickAtMicroSecond(uint32_t microSecond){
  uint32_t timeUsBase = (Core::getSystemCoreClock()/1000000);
  
  if(microSecond > (0xFFFFFFFF/timeUsBase))
    return 0;

  return (microSecond * timeUsBase);
}

/**
 *
 */
void CoreTimer::interruptEnable(bool enable){
  Core::interrupt.irqEnable(CONFIG.irq, enable);
  return;
}

/* ****************************************************************************************
 * End of file
 */ 
