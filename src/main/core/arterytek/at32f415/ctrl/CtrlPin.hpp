/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef MCUF_AT32F415_A26CB9ED_5F49_452E_9399_0F6C1815D5A1
#define MCUF_AT32F415_A26CB9ED_5F49_452E_9399_0F6C1815D5A1

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"

#include "core/arterytek/at32f415/CoreGPIO.hpp"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace ctrl{
        class CtrlPin;
        class CtrlGPIO;
      }
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::ctrl::CtrlPin :
  public mcuf::lang::Object{

  
  friend CtrlGPIO;
  /* **************************************************************************************
   * Subclass
   */
  
  /* **************************************************************************************
   * Struct RegIocon
   */
  public: struct RegIocon{
    uint8_t pin[16];
    uint16_t pull;
  };

  /* **************************************************************************************
   * Union Pin
   */
  
  /* **************************************************************************************
   * Enum Mode
   */
  public: enum Mode{
    MODE_INACTIVE,      //output push-pull; input open
    MODE_OPEN,          //output open; input open
    MODE_ANALOG,        //output open; input analog
    MODE_PULLDOWN,      //output push-pull; input pulldown
    MODE_PULLUP         //output push-pull; input pullup
  };
  
  /* **************************************************************************************
   * Enum Opt
   */  
  public: enum Opt{
    OPT_2M,
    OPT_10M,
    OPT_50M
  };
  
  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: static RegIocon regIocon[6];

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */

  /**
   * Construct.
   */
  private: CtrlPin(void) = default;

  /**
   * Disconstruct.
   */
  public: virtual ~CtrlPin(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /**
   *
   */
  public: static RegIocon* getRegIocon(core::arterytek::at32f415::CoreGPIO::Registor gpioBase);

  /**
   * 
   */
  public: static void setConfig(RegIocon* reg, uint8_t pin, Mode mode, Opt opt, bool func);

  /**
   * 
   */
  public: static void setFunc(RegIocon* reg, uint8_t pin, bool enable);

  /**
   * 
   */
  public: static void setMode(RegIocon* reg, uint8_t pin, Mode mode);

  /**
   * 
   */
  public: static void reset(RegIocon* reg);

  /**
   * 
   */
  public: static void setInput(RegIocon* reg, uint8_t pin);

  /**
   * 
   */
  public: static void setOutput(RegIocon* reg, uint8_t pin);


  /* **************************************************************************************
   * Public Method <Override>
   */

  /* **************************************************************************************
   * Public Method
   */

  /* **************************************************************************************
   * Protected Method <Static>
   */

  /* **************************************************************************************
   * Protected Method <Override>
   */

  /* **************************************************************************************
   * Protected Method
   */

  /* **************************************************************************************
   * Private Method <Static>
   */
   
  /**
   * 
   */
  private: static inline void funcConfig(uint8_t* reg, bool enable);

  /**
   * 
   */
  private: static void* getBase(uint8_t port);

  /**
   * 
   */
  private: static void modeConfig(Pin pin, uint8_t* reg, uint16_t* regPull, Mode mode);

  /**
   * 
   */
  private: static void optConfig(uint8_t* reg, Opt opt);

  /**
   * 
   */
  private: static void regReset(void);
  
  /* **************************************************************************************
   * Private Method <Override>
   */
   
  /* **************************************************************************************
   * Private Method
   */  
};



/* *****************************************************************************************
 * End of file
 */ 

#endif /* MCUF_AT32F415_A26CB9ED_5F49_452E_9399_0F6C1815D5A1 */
