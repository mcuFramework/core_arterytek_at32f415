/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_ECE02CDF_DC7C_4FF3_A0C5_DE8A6C0F1776
#define CORE_ARTERYTEK_AT32F415_ECE02CDF_DC7C_4FF3_A0C5_DE8A6C0F1776

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CoreGPIO;
      class CorePin;
    }
  }
}



/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreGPIO :
      public mcuf::hal::GeneralPurposeIO{

        
  friend CorePin;
  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Enum Registor
   */
  public: enum Registor{
    REG_GPIOA,
    REG_GPIOB,
    REG_GPIOC,
    REG_GPIOD,
    REG_GPIOF,
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
  private: void* mBase;

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
  public: CoreGPIO(Registor reg);

  /**
   * Disconstruct.
   */
  public: virtual ~CoreGPIO(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
   */

  /**
   * uninitialze hardware.
   */
  public: virtual bool deinit(void) override;

  /**
   * 
   */
  public: virtual uint32_t dir(uint32_t port) override;

  /**
   * 
   */
  public: virtual void dir(uint32_t port, uint32_t value) override;
  
  /**
   * 
   */
  public: virtual void dirClear(uint32_t port, uint32_t mask) override;
  
  /**
   * 
   */
  public: virtual void dirSet(uint32_t port, uint32_t mask) override;

  /**
   * initialze hardware;
   */
  public: virtual bool init(void) override;

  /**
   * get hardware initialzed status.
   * 
   * @return false = not init, true = initd
   */
  public: virtual bool isInit(void) override;

  /**
   * 
   * @param port GPIO port.
   */
  public: virtual uint32_t pin(uint32_t port) override;

  /**
   * 
   * @param port GPIO port.
   */
  public: virtual void pin(uint32_t port, uint32_t value) override;
  
  /**
   * 
   */
  public: virtual void pinClear(uint32_t port, uint32_t mask) override;

  /**
   *
   * @param port GPIO port.
   * @param value GPIO write value.
   */
  public: virtual void pinSet(uint32_t port, uint32_t mask) override;
  
  /**
   * 
   */
  public: virtual void pinToggle(uint32_t port, uint32_t mask) override;

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


#endif/* CORE_ARTERYTEK_AT32F415_ECE02CDF_DC7C_4FF3_A0C5_DE8A6C0F1776 */
