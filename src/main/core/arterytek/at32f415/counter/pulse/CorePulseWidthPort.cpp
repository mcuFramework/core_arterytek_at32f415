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
#include "mcuf.h"
#include "bsp_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/counter/pulse/CorePulseWidthPort.h"

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<char>(this->mRegister))
#define CONFIG                   (corePulseWidthPortConfig[REGNUMB])
#define BASE                     ((tmr_type*)CONFIG.Register)

/* ****************************************************************************************
 * Namespace
 */ 
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace counter{
        namespace pulse{
        
          struct CorePulseWidthPortConfig{
            void* Register;
            crm_periph_clock_type crmClock;
            
          }const corePulseWidthPortConfig[8] = {
            {TMR1 , CRM_TMR1_PERIPH_CLOCK},
            {TMR2 , CRM_TMR2_PERIPH_CLOCK},
            {TMR3 , CRM_TMR3_PERIPH_CLOCK},
            {TMR4 , CRM_TMR4_PERIPH_CLOCK},
            {TMR5 , CRM_TMR5_PERIPH_CLOCK},
            {TMR9 , CRM_TMR9_PERIPH_CLOCK },
            {TMR10, CRM_TMR10_PERIPH_CLOCK},
            {TMR11, CRM_TMR11_PERIPH_CLOCK},
          };
          
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using core::arterytek::at32f415::counter::pulse::CorePulseWidthPort;
using core::arterytek::at32f415::counter::pulse::CorePulseWidthReg;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Pulse Width Port:: Core Pulse Width Port object
 * 
 * @param reg 
 */
CorePulseWidthPort::CorePulseWidthPort(CorePulseWidthReg reg){
  this->mRegister = reg;
}

/**
 * @brief Destroy the Core Pulse Width Port:: Core Pulse Width Port object
 * 
 */
CorePulseWidthPort::~CorePulseWidthPort(void){
  this->deinit();
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
bool CorePulseWidthPort::deinit(void){
	if(!this->isInit())
		return false;
	
  crm_periph_clock_enable(CONFIG.crmClock, FALSE);
	return true;
}

/**
 * initialze hardware;
 */
bool CorePulseWidthPort::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(CONFIG.crmClock, TRUE);
  tmr_base_init(BASE, 500, 500);
  tmr_cnt_dir_set(BASE, TMR_COUNT_UP);
  tmr_clock_source_div_set(BASE, TMR_CLOCK_DIV1);
  
  tmr_counter_enable(BASE, TRUE);
  tmr_period_buffer_enable(BASE, TRUE);
  return true;
}

/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CorePulseWidthPort::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::counter::pulse::PulseWidthPort
 */

/**
 * @brief Set the Frequence object
 * 
 * @param hz 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPort::setFrequence(float hz){
  double tick = (Core::getSystemCoreClock() >> 1);
  tick /= hz;
  if(tick > 0xFFFFFFFF)
    return false;
  
  this->setDivider(tick);
  
  return true;
}

/**
 * @brief Get the Frequence object
 * 
 * @return float 
 */
float CorePulseWidthPort::getFrequence(void){
  uint32_t tick = BASE->pr * BASE->div;
  return ((float)Core::getSystemCoreClock() / tick);
}

/**
 * @brief Get the Period object
 * 
 * @return int 
 */
int CorePulseWidthPort::getPeriod(void){
  return (BASE->pr + 1);
}

/**
 * @brief Get the Duty object
 * 
 * @param pin 
 * @return float 
 */
float CorePulseWidthPort::getDuty(int pin){
  uint32_t value;
  
  switch(pin){
    case 0:
      value = BASE->c1dt;
      break;
    
    case 1:
      value = BASE->c2dt;
      break;
    
    case 2:
      value = BASE->c3dt;
      break;
    
    case 3:
      value = BASE->c4dt;
      break;
    
    default:
      return 0;
  }
  
  return ((float)this->getPeriod() / value);
}

/**
 * @brief Get the Duty Tick object
 * 
 * @param pin 
 * @return int 
 */
int CorePulseWidthPort::getDutyTick(int pin){
  switch(pin){
    case 0:
      return BASE->c1dt;
    
    case 1:
      return BASE->c2dt;
    
    case 2:
      return BASE->c3dt;
    
    case 3:
      return BASE->c4dt;
    
    default:
      return 0;
  }
}

/**
 * @brief Set the Duty object
 * 
 * @param pin 
 * @param percent 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPort::setDuty(int pin, float percent){
  if((pin >= 0) && (pin < 4)){
    return this->setDutyTick(pin, this->getPeriod() * percent);
  }
  
  return false;
}

/**
 * @brief Set the Duty Tick object
 * 
 * @param pin 
 * @param duty 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPort::setDutyTick(int pin, int duty){
  if(duty > this->getPeriod())
      return false;
  
  tmr_channel_select_type channel;
  
  switch(pin){
    case 0:
      channel = TMR_SELECT_CHANNEL_1;
      break;
    
    case 1:
      channel = TMR_SELECT_CHANNEL_2;
      break;
    
    case 2:
      channel = TMR_SELECT_CHANNEL_3;
      break;
    
    case 3:
      channel = TMR_SELECT_CHANNEL_4;
      break;
    
    default:
      return false;
  
  }
  
  tmr_channel_value_set(BASE, channel, duty);
  
  return false;
}

/**
 * @brief 
 * 
 * @param pin 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPort::disable(int pin){
  switch(pin){
    case TMR_SELECT_CHANNEL_1:
      BASE->cm1_output_bit.c1octrl = TMR_OUTPUT_CONTROL_OFF;
      return true;

    case TMR_SELECT_CHANNEL_2:
      BASE->cm1_output_bit.c2octrl = TMR_OUTPUT_CONTROL_OFF;
      return true;

    case TMR_SELECT_CHANNEL_3:
      BASE->cm2_output_bit.c3octrl = TMR_OUTPUT_CONTROL_OFF;
      return true;

    case TMR_SELECT_CHANNEL_4:
      BASE->cm2_output_bit.c4octrl = TMR_OUTPUT_CONTROL_OFF;
      return true;

    default:
      return false;
  }
}

/**
 * @brief 
 * 
 * @param pin 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPort::enable(int pin){
  tmr_channel_select_type channel;
  
  switch(pin){
    case 0:
      channel = TMR_SELECT_CHANNEL_1;
      break;
    
    case 1:
      channel = TMR_SELECT_CHANNEL_2;
      break;
    
    case 2:
      channel = TMR_SELECT_CHANNEL_3;
      break;
    
    case 3:
      channel = TMR_SELECT_CHANNEL_4;
      break;
    
    default:
      return false;
  }
  
  tmr_output_config_type tmr_oc_init_structure;
  tmr_output_default_para_init(&tmr_oc_init_structure);
  tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_oc_init_structure.oc_idle_state = FALSE;
  tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_oc_init_structure.oc_output_state = TRUE;
  tmr_output_channel_config(BASE, channel, &tmr_oc_init_structure);
  tmr_channel_value_set(BASE, channel, 0);
  tmr_output_channel_buffer_enable(BASE, channel, TRUE);
  return true;
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
void CorePulseWidthPort::setDivider(uint32_t tick){
  uint32_t div = 1 + (tick>>16);
  uint32_t period = (tick/div);  
  
  tmr_base_init(BASE, period, div);
}

/* ****************************************************************************************
 * End of file
 */
