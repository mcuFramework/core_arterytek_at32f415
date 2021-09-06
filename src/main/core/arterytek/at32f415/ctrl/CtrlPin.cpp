/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "core/arterytek/at32f415/ctrl/CtrlPin.hpp"
#include "core/arterytek/at32f415/ctrl/CtrlGPIO.hpp"

#include "bsp_arterytek_at32f415/at32f4xx_gpio.h"

 
/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::ctrl::CtrlPin;
using core::arterytek::at32f415::ctrl::CtrlGPIO;

/* ****************************************************************************************
 * Macro
 */
#define CORE_IOCON_OUTPUT_MASK           0x0F

#define CORE_IOCON_OUTPUT_MDE_SHIFT      0UL
#define CORE_IOCON_OUTPUT_MDE_MASK      (0x3 << CORE_IOCON_OUTPUT_MDE_SHIFT)
#define CORE_IOCON_OUTPUT_MDE_10M       (0x1 << CORE_IOCON_OUTPUT_MDE_SHIFT)
#define CORE_IOCON_OUTPUT_MDE_2M        (0x2 << CORE_IOCON_OUTPUT_MDE_SHIFT)
#define CORE_IOCON_OUTPUT_MDE_50M       (0x3 << CORE_IOCON_OUTPUT_MDE_SHIFT)

#define CORE_IOCON_OUTPUT_CONF_OPEN_ENABLE    (0x1 << 2U)
#define CORE_IOCON_OUTPUT_CONF_FUNC_ENABLE    (0x1 << 3U)

#define CORE_IOCON_INPUT_MASK           0xF0
 
#define CORE_IOCON_INPUT_CONF_SHIFT     6UL
#define CORE_IOCON_INPUT_CONF_MASK     (0x3 << CORE_IOCON_INPUT_CONF_SHIFT)
#define CORE_IOCON_INPUT_CONF_ANALOG   (0x0 << CORE_IOCON_INPUT_CONF_SHIFT)
#define CORE_IOCON_INPUT_CONF_OPEN     (0x1 << CORE_IOCON_INPUT_CONF_SHIFT)
#define CORE_IOCON_INPUT_CONF_PULL     (0x2 << CORE_IOCON_INPUT_CONF_SHIFT)

/* ****************************************************************************************
 * Variable
 */

CtrlPin::RegIocon CtrlPin::regIocon[6] = {
  {0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x83, 0x83, 0x83, 0xBFFF},
  {0x43, 0x43, 0x43, 0x43, 0x83, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0xFFFF},
  {0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0xFFFF},
  {0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0xFFFF},
  {0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0xFFFF},
  {0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0xFFFF},
};

/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/**
 * 
 */
void CtrlPin::setConfig(Pin pin, Mode mode, Opt opt, bool func){
  uint8_t* reg = &CtrlPin::regIocon[pin.group.port].pin[pin.group.pin];
  uint16_t* reg_pull = &CtrlPin::regIocon[pin.group.port].pull;
  
  CtrlPin::modeConfig(pin, reg, reg_pull, mode);
  CtrlPin::optConfig(reg, opt);
  CtrlPin::funcConfig(reg, func);
  CtrlGPIO::refreshPin(pin.group.port, pin.group.pin);
}

/**
 * 
 */
void CtrlPin::setFunc(Pin pin, bool enable){
  uint8_t* reg = &CtrlPin::regIocon[pin.group.port].pin[pin.group.pin];
  
  CtrlPin::funcConfig(reg, enable);

  CtrlGPIO::refreshPin(pin.group.port, pin.group.pin);
}

/**
 * 
 */
void CtrlPin::setIointMux(Pin pin){
  GPIO_EXTILineConfig(pin.group.port, pin.group.pin);
  return;
}

/**
 * 
 */
void CtrlPin::setMode(Pin pin, Mode mode){
  uint8_t* reg = &CtrlPin::regIocon[pin.group.port].pin[pin.group.pin];
  uint16_t* reg_pull = &CtrlPin::regIocon[pin.group.port].pull;
  
  CtrlPin::modeConfig(pin, reg, reg_pull, mode);
  
  CtrlGPIO::refreshPin(pin.group.port, pin.group.pin);
}

/**
 * 
 */
void CtrlPin::reset(void){
  CtrlPin::reset();
  return;
}

/**
 * 
 */
void CtrlPin::setInput(Pin pin){
  CtrlGPIO::setPinDir(pin.group.port, pin.group.pin, false);
  return;
}

/**
 * 
 */
void CtrlPin::setOutput(Pin pin){
  CtrlGPIO::setPinDir(pin.group.port, pin.group.pin, true);
  return;
}

/**
 * 
 */
void CtrlPin::swdio(bool enable){
  if(enable)
    GPIO_PinsRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  else
    GPIO_PinsRemapConfig(GPIO_Remap_SWJ_AllDisable, ENABLE);
}


/* ****************************************************************************************
 * Public Method <Override>
 */

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
inline void CtrlPin::funcConfig(uint8_t* reg, bool enable){
  if(enable)
    *reg |= CORE_IOCON_OUTPUT_CONF_FUNC_ENABLE;
  else
    *reg &= ~CORE_IOCON_OUTPUT_CONF_FUNC_ENABLE;
}

/**
 * 
 */
void* CtrlPin::getBase(uint8_t port){
  switch(port){
    case 0:
      return GPIOA;
    
    case 1:
      return GPIOB;
    
    case 2:
      return GPIOC;
    
    case 3:
      return GPIOD;
    
    case 5:
      return GPIOF;
    
    default:
      THROW_ERROR("out of enum index");
  }
  
  return nullptr;
}

/**
 * 
 */
void CtrlPin::modeConfig(Pin pin, uint8_t* reg, uint16_t* regPull, Mode mode){
  //clear input flag
  *reg &= ~CORE_IOCON_INPUT_MASK;
  
  switch(mode){
    case CtrlPin::MODE_INACTIVE:
      //set input opendrain
      *reg |= CORE_IOCON_INPUT_CONF_OPEN;
      //set output push-pull
      *reg &= ~CORE_IOCON_OUTPUT_CONF_OPEN_ENABLE;
      break;
    case CtrlPin::MODE_OPEN:
      //set input opendrain; output open-drain
      *reg |= (CORE_IOCON_INPUT_CONF_OPEN | CORE_IOCON_OUTPUT_CONF_OPEN_ENABLE);
      break;
    case CtrlPin::MODE_ANALOG:
      //set input analog; output open-drain
      *reg |= (CORE_IOCON_INPUT_CONF_ANALOG | CORE_IOCON_OUTPUT_CONF_OPEN_ENABLE);
      break;
    case CtrlPin::MODE_PULLDOWN:
      //set input pull-down
      *reg |= CORE_IOCON_INPUT_CONF_PULL;
      *regPull &= ~(1<<pin.group.pin);
      //set output push-pull
      *reg &= ~CORE_IOCON_OUTPUT_CONF_OPEN_ENABLE;
      break;
    case CtrlPin::MODE_PULLUP:
      //set input pull-down
      *reg |= CORE_IOCON_INPUT_CONF_PULL;
      *regPull |= (1<<pin.group.pin);
      //set output push-pull
      *reg &= ~CORE_IOCON_OUTPUT_CONF_OPEN_ENABLE;
      break;
  }
}

/**
 * 
 */
void CtrlPin::optConfig(uint8_t* reg, Opt opt){
  *reg &= ~CORE_IOCON_OUTPUT_MDE_MASK;
  
  switch(opt){
    case OPT_2M:
      *reg |= CORE_IOCON_OUTPUT_MDE_2M;
      break;
    case OPT_50M:
      *reg |= CORE_IOCON_OUTPUT_MDE_50M;
      break;
    default:
      *reg |= CORE_IOCON_OUTPUT_MDE_10M;
      break;
  }
}

/**
 * 
 */
void CtrlPin::regReset(void){
  memset((void*)&CtrlPin::regIocon[0], 0x43, sizeof(CtrlPin::regIocon));
  CtrlPin::regIocon[0].pin[13] = 0x83;
  CtrlPin::regIocon[0].pin[14] = 0x83;
  CtrlPin::regIocon[0].pin[15] = 0x83;
  CtrlPin::regIocon[1].pin[4]  = 0x83;
  
  CtrlPin::regIocon[0].pull = 0xBFFF;
  CtrlPin::CtrlPin::regIocon[1].pull = 0xFFFF;
  CtrlPin::regIocon[2].pull = 0xFFFF;
  CtrlPin::regIocon[3].pull = 0xFFFF;
  CtrlPin::regIocon[4].pull = 0xFFFF;
  CtrlPin::regIocon[5].pull = 0xFFFF;
}

/* ****************************************************************************************
 * End of file
 */ 
