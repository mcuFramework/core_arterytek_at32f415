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
 
//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/general/port/CoreGeneralPortReg.h"
#include "core/arterytek/at32f415/general/port/InputMode.h"
#include "core/arterytek/at32f415/general/port/OutputMode.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace general{
        namespace port{
          class CoreGeneralPort;
        }
      }
      class Core;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::general::port::CoreGeneralPort extends mcuf::lang::Object implements 
  public mcuf::hal::general::port::GeneralPort{

  friend Core;
        
  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: 
    core::arterytek::at32f415::general::port::CoreGeneralPortReg mRegister;

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */
  private: 
    CoreGeneralPort(core::arterytek::at32f415::general::port::CoreGeneralPortReg reg);

  
  public: 
    virtual ~CoreGeneralPort(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> mcuf::hal::Base
   */

  /**
   * uninitialze hardware.
   */
  public: virtual bool deinit(void) override;

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

  /* **************************************************************************************
   * Public Method <Override>
   */

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
  public:
    
    /**
     *
     */
    bool configInput(uint32_t pin, core::arterytek::at32f415::general::port::InputMode mode);
    
    /**
     *
     */
    bool configOutput(uint32_t pin, core::arterytek::at32f415::general::port::OutputMode mode, 
                      bool opendrain, 
                      bool function, 
                      bool value);

    /**
     *
     */
    void* getBase(void);

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
