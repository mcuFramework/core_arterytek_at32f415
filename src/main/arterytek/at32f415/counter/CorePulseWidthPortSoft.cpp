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
#include "arterytek/at32f415/counter/CorePulseWidthPortSoft.h"

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<char>(this->mRegister))
#define CONFIG                   (corePulseWidthPortSoftConfig[REGNUMB])
#define BASE                     ((tmr_type*)CONFIG.Register)

/* ****************************************************************************************
 * Namespace
 */ 

namespace arterytek{
  namespace at32f415{
    namespace counter{  
      struct CorePulseWidthPortSoftConfig{
        void* Register;
        CoreInterrupt::Irq irq;
            
      }const corePulseWidthPortSoftConfig[8] = {
        {TMR1  , CoreInterrupt::IRQ_TMR1 },
        {TMR2  , CoreInterrupt::IRQ_TMR2 },
        {TMR3  , CoreInterrupt::IRQ_TMR3 },
        {TMR4  , CoreInterrupt::IRQ_TMR4 },
        {TMR5  , CoreInterrupt::IRQ_TMR5 },
        {TMR9  , CoreInterrupt::IRQ_TMR9 },
        {TMR10 , CoreInterrupt::IRQ_TMR10},
        {TMR11 , CoreInterrupt::IRQ_TMR11},
      };
          
    }
  }
}


/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using arterytek::at32f415::counter::CorePulseWidthPortSoft;
using arterytek::at32f415::counter::CorePulseWidthPort;
using arterytek::at32f415::counter::CorePulseWidthReg;
using arterytek::at32f415::Core;
using arterytek::at32f415::CoreInterrupt;
using hal::general::GeneralPin;

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
 * @brief Construct a new Core Pulse Width Port:: Core Pulse Width Port object
 * 
 * @param reg 
 */
CorePulseWidthPortSoft::CorePulseWidthPortSoft(CorePulseWidthReg reg) : CorePulseWidthPort(reg){
}

/**
 * @brief Destroy the Core Pulse Width Port:: Core Pulse Width Port object
 * 
 */
CorePulseWidthPortSoft::~CorePulseWidthPortSoft(void){
  this->deinit();
}

/* ****************************************************************************************
 * Public Method <Static> 
 */

/* ****************************************************************************************
 * Public Method <Override> - arterytek::at32f415::counter::CorePulseWidthPort
 */

/**
 * @brief uninitialze hardware.
 * 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPortSoft::deinit(void){
  if(CorePulseWidthPort::isInit()){
    tmr_interrupt_enable(BASE, TMR_C1_INT | TMR_C2_INT | TMR_C3_INT | TMR_C4_INT | TMR_OVF_INT, FALSE);
    Core::interrupt.irqEnable(CONFIG.irq, false);
    Core::interrupt.setHandler(CONFIG.irq, nullptr);
  }
  
  bool result = CorePulseWidthPort::deinit();
  
  return result;
}

/**
 * @brief initialze hardware
 * 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPortSoft::init(void){
  bool result = CorePulseWidthPort::init();
  
  if(result){
    Core::interrupt.irqEnable(CONFIG.irq, true);
    Core::interrupt.setHandler(CONFIG.irq, this);
    tmr_interrupt_enable(BASE, TMR_OVF_INT, TRUE);
  }
  
  return result;
}
  
/**
 * @brief 
 * 
 * @param pin 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPortSoft::enable(int pin){
  tmr_channel_select_type channel;
  uint32_t tmr_interrupt;
  
  switch(pin){
    case 0:
      channel = TMR_SELECT_CHANNEL_1;
      tmr_interrupt = TMR_C1_INT;
      break;
    
    case 1:
      channel = TMR_SELECT_CHANNEL_2;
      tmr_interrupt = TMR_C2_INT;
      break;
    
    case 2:
      channel = TMR_SELECT_CHANNEL_3;
      tmr_interrupt = TMR_C3_INT;
      break;
    
    case 3:
      channel = TMR_SELECT_CHANNEL_4;
      tmr_interrupt = TMR_C4_INT;
      break;
    
    default:
      return false;
  }
  
  tmr_output_config_type tmr_oc_init_structure;
  tmr_output_default_para_init(&tmr_oc_init_structure);
  tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_OFF;
  tmr_oc_init_structure.oc_idle_state = FALSE;
  tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_oc_init_structure.oc_output_state = TRUE;
  tmr_output_channel_config(BASE, channel, &tmr_oc_init_structure);
  tmr_channel_value_set(BASE, channel, 0);
  tmr_output_channel_buffer_enable(BASE, channel, TRUE);
  
  tmr_interrupt_enable(BASE, tmr_interrupt, TRUE);
  return true;
}
  
/**
 * @brief 
 * 
 * @param pin 
 * @return true 
 * @return false 
 */
bool CorePulseWidthPortSoft::disable(int pin){
  
  switch(pin){
    case TMR_SELECT_CHANNEL_1:
      tmr_interrupt_enable(BASE, TMR_C1_INT, FALSE);
      return true;

    case TMR_SELECT_CHANNEL_2:
      tmr_interrupt_enable(BASE, TMR_C2_INT, FALSE);
      return true;

    case TMR_SELECT_CHANNEL_3:
      tmr_interrupt_enable(BASE, TMR_C3_INT, FALSE);
      return true;

    case TMR_SELECT_CHANNEL_4:
      tmr_interrupt_enable(BASE, TMR_C4_INT, FALSE);
      return true;

    default:
      return false;
  }
}

/* ****************************************************************************************
 * Public Method <Override> - hal::InterruptEvent
 */

/**
 *
 */
void CorePulseWidthPortSoft::interruptEvent(void){
  tmr_type* base = BASE;
  
  if(tmr_flag_get(base, TMR_C1_FLAG) != RESET){
    tmr_flag_clear(base, TMR_C1_FLAG );
    if(this->mGeneralPin[0])
      this->mGeneralPin[0]->setLow();
    
  }
  
  if(tmr_flag_get(base, TMR_C2_FLAG) != RESET){
    tmr_flag_clear(base, TMR_C2_FLAG);
    if(this->mGeneralPin[1])
      this->mGeneralPin[1]->setLow();
    
  }
  
  if(tmr_flag_get(base, TMR_C3_FLAG) != RESET){
    tmr_flag_clear(base, TMR_C3_FLAG);
    if(this->mGeneralPin[2])
      this->mGeneralPin[2]->setLow();

  }
  
  if(tmr_flag_get(base, TMR_C4_FLAG) != RESET){
    tmr_flag_clear(base, TMR_C4_FLAG);
    if(this->mGeneralPin[3])
      this->mGeneralPin[3]->setLow();

  }
  
  if(tmr_flag_get(base, TMR_OVF_FLAG)){
    tmr_flag_clear(base, TMR_OVF_FLAG);
    
    if(base->iden_bit.c1ien){
      if(this->mGeneralPin[0])
        this->mGeneralPin[0]->setHigh();
    }
    
    if(base->iden_bit.c2ien){
      if(this->mGeneralPin[1])
        this->mGeneralPin[1]->setHigh();
    }
    
    if(base->iden_bit.c3ien){
      if(this->mGeneralPin[2])
        this->mGeneralPin[2]->setHigh();
    }
    
    if(base->iden_bit.c4ien){
      if(this->mGeneralPin[3])
        this->mGeneralPin[3]->setHigh();
    }
  }
}

/* ****************************************************************************************
 * Public Method <Override> - hal::InterruptEvent
 */

/* ****************************************************************************************
 * Public Method
 */

/**
 *
 */
bool CorePulseWidthPortSoft::setPin(int pin, GeneralPin* generalPin){
  if((pin >= 0) && (pin < 4)){
    this->mGeneralPin[pin] = generalPin;
    return true;
  }
  
  return false;
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

/* ****************************************************************************************
 * End of file
 */
