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
#include "core/arterytek/at32f415/general/port/CoreGeneralPort.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace general{
        namespace port{
          
          struct ConfigCoreGeneralPort{
            void* reg;
            crm_periph_clock_type crmClock;
          }const configCoreGeneralPort[5]{
            {GPIOA, CRM_GPIOA_PERIPH_CLOCK},
            {GPIOB, CRM_GPIOB_PERIPH_CLOCK},
            {GPIOC, CRM_GPIOC_PERIPH_CLOCK},
            {GPIOD, CRM_GPIOD_PERIPH_CLOCK},
            {GPIOF, CRM_GPIOF_PERIPH_CLOCK},
          };
          
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Using
 */  
using namespace core::arterytek::at32f415::general::port;

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                     (static_cast<char>(this->mRegister))
#define CONFIG                      (configCoreGeneralPort[REGNUMB])
#define BASE                        ((gpio_type*)CONFIG.reg)
#define GET_CTRL_DIR(source, shift) ((source & (0x00000003 << (shift << 2)))?1:0)
#define GET_BIT(source, bit)        ((source & (1 << (bit)))?1:0)

/* ****************************************************************************************
 * Variable
 */


/* ****************************************************************************************
 * Construct Method
 */
 
/**
 *
 */
CoreGeneralPort::CoreGeneralPort(CoreGeneralPortReg reg){
  this->mRegister = reg;
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
bool CoreGeneralPort::deinit(void){
	if(!this->isInit())
		return false;
	
  crm_periph_clock_enable(CONFIG.crmClock, FALSE);
	return true;
}

/**
 * initialze hardware;
 */
bool CoreGeneralPort::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(CONFIG.crmClock, TRUE);
  return false;
}

/**
 * get hardware initialzed status.
 * 
 * @return false = not init, true = initd
 */
bool CoreGeneralPort::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override> mcuf::hal::GeneralPort
 */

/**
 * dir
 */
uint32_t CoreGeneralPort::dir(uint32_t port){
  if(port)
    return 0x00000000;
  
  gpio_type* base = BASE;
  
  uint32_t result = 0x00000000;
  
  for(uint32_t i=0; i<8; ++i){
    uint32_t mask = (0x00000003 << (i << 2));
    
    if(base->cfglr & ~mask)
      result |= (1 << i);     
    
    if(base->cfghr & ~mask)
      result |= (1 << (8+i));   
  }
  
  return result;
}

/**
 * dir
 */
void CoreGeneralPort::dir(uint32_t port, uint32_t value){
  if(port)
    return;
  
  gpio_type* base = BASE;
  
  value &= 0x0000FFFF;
  
  uint32_t regMaskCONF;
  
  
  for(uint32_t i=0; i<8; ++i){
    regMaskCONF = (0x00000003 << (i<<2));
    
    if(base->cfglr & regMaskCONF){  //hardware is output
      if(!GET_BIT(value, i))                          //value flag is low?
        base->cfglr &= ~regMaskCONF; //set input
        
    }else{                                            //hardware is input
      if(GET_BIT(value, i))                           //value flag is high?
        base->cfglr |= regMaskCONF;  //set output 50M
    }
    
    if(base->cfghr & regMaskCONF){  //hardware is output
      if(!GET_BIT(value, 8+i))                        //value flag is low?
        base->cfghr &= ~regMaskCONF; //set input
        
    }else{                                            //hardware is input
      if(GET_BIT(value, 8+i))                         //value flag is high?
        base->cfghr |= regMaskCONF;  //set output 50M
    }
  }
  
  return;
}

/**
 * 
 */
void CoreGeneralPort::dirClear(uint32_t port, uint32_t mask){
  if(port)
    return;

  this->dir(0, (this->dir(0) & ~mask));
  
  return;
}

/**
 * 
 */
void CoreGeneralPort::dirSet(uint32_t port, uint32_t mask){
  if(port)
    return;

  this->dir(0, (this->dir(0) | mask));
  
  return;
}

/**
 * 
 * @param port GPIO port.
 */
uint32_t CoreGeneralPort::pin(uint32_t port){
  if(port)
    return 0x00000000;
  
  gpio_type* base = BASE;
  
	return base->idt;
}

/**
 *
 * @param port GPIO port.
 * @param value GPIO write value.
 */
void CoreGeneralPort::pin(uint32_t port, uint32_t value){
  if(port)
    return;
  
  gpio_type* base = BASE;
  uint32_t dir = this->dir(0);
  
  base->scr = (value & dir);
}

/**
 * setting io output pin to push-pull low at mask.
 *
 * @param port io port.
 * @param mask bit high = active.
 */
void CoreGeneralPort::pinClear(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  gpio_type* base = BASE;
  uint32_t dir = this->dir(0);
  
  base->clr = (((uint16_t)mask) & dir);
  return;
}

/**
 *
 * @param port GPIO port.
 * @param mask GPIO write value.
 */
void CoreGeneralPort::pinSet(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  gpio_type* base = BASE;
  uint32_t dir = this->dir(0);
  
  base->scr = (((uint16_t)mask) & dir);
  return;
}

/**
 * 
 */
void CoreGeneralPort::pinToggle(uint32_t port, uint32_t mask){
  if(port)
    return;
  
  gpio_type* base = BASE;
  
  uint32_t dir = this->dir(0);
  
	base->odt ^= (((uint16_t)mask) & dir);
	return;
}

/* ****************************************************************************************
 * Public Method
 */
  
/**
 *
 */
bool CoreGeneralPort::configInput(uint32_t pin, InputMode mode){
  if(pin >= 16)
    return false;
  
  gpio_type* base = BASE;
  
  uint8_t shift = ((pin & 0x00000007) << 2);
  volatile uint32_t* reg;
  uint32_t ctrl;
  
  if(pin < 8)  // 0~7pin
    reg = &base->cfglr;
    
  else         // 8~15pin
    reg = &base->cfghr;
  
  ctrl = ((*reg) & ~(0x0000000F << shift));
  
  switch(mode){
    case InputMode::OPEN:
      *reg = (ctrl | (0x00000004 << shift));
      base->clr |= (1 << pin);
      return true;
      
    case InputMode::ANALOG:
      *reg = ctrl;
      base->clr |= (1 << pin);
      return true;
    
    case InputMode::PULLDOWN:
      *reg = (ctrl | (0x00000008 << shift));
      base->clr |= (1 << pin);
      return true;
      
    case InputMode::PULLUP:
      *reg = (ctrl | (0x00000008 << shift));
      base->scr |= (1 << pin);
      return true;
    
    default:
      return false;
  }
  
  return false;
}
  
/**
 *
 */
bool CoreGeneralPort::configOutput(uint32_t pin, OutputMode mode, bool opendrain, bool function, bool value){
  if(pin >= 16)
    return false;
  
  gpio_type* base = BASE;
  
  uint8_t shift = ((pin & 0x00000007) << 2);
  volatile uint32_t* reg;
  uint32_t ctrl;
  
  if(pin < 8)  // 0~7pin
    reg = &base->cfglr;
    
  else        // 8~15pin
    reg = &base->cfghr;
  
  ctrl = ((*reg) & ~(0x0000000F << shift));
  
  if(opendrain)
    ctrl |= (0x00000004 << shift);
  
  if(function)
    ctrl |= (0x00000008 << shift);
  
  
  switch(mode){
    case OutputMode::SPEED_2M:
      *reg = (ctrl | (0x00000002 << shift));
      break;
    
    case OutputMode::SPEED_10M:
      *reg = (ctrl | (0x00000001 << shift));
      break;
    
    case OutputMode::SPEED_50M:
      *reg = (ctrl | (0x00000003 << shift));
      break;
    
    default:
      return false;
  }
  
  base->scr |= (1<<pin);
  
  return false;
}

/**
 * @brief 
 * 
 * @param pin 
 * @param opendrain 
 * @return true 
 * @return false 
 */
bool CoreGeneralPort::setFunction(uint32_t pin, bool opendrain){
  return this->configOutput(pin, OutputMode::SPEED_50M, opendrain, true, true);
}

/**
 * @brief 
 * 
 * @param pin 
 * @return true 
 * @return false 
 */
bool CoreGeneralPort::setAnalog(uint32_t pin){
  return this->configInput(pin, InputMode::ANALOG);
}

/**
 *
 */
void* CoreGeneralPort::getBase(void){
  return BASE;
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
