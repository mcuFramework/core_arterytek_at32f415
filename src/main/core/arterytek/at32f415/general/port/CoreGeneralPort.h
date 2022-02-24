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
  public:
    
    /**
     * @brief uninitialze hardware.
     * 
     * @return true 
     * @return false 
     */
    virtual bool deinit(void) override;

    /**
     * @brief initialze hardware.
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;

    /**
     * @brief get hardware initialzed status.
     * 
     * @return true initd
     * @return false not init
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override>
   */
  public:
  
    /**
     * @brief 
     * 
     * @param port 
     * @return uint32_t 
     */
    virtual uint32_t dir(uint32_t port) override;

    /**
     * @brief 
     * 
     * @param port 
     * @param value 
     */
    virtual void dir(uint32_t port, uint32_t value) override;
    
    /**
     * @brief 
     * 
     * @param port 
     * @param mask 
     */
    virtual void dirClear(uint32_t port, uint32_t mask) override;
    
    /**
     * @brief 
     * 
     * @param port 
     * @param mask 
     */
    virtual void dirSet(uint32_t port, uint32_t mask) override;

    /**
     * @brief 
     * 
     * @param port 
     * @return uint32_t 
     */
    virtual uint32_t pin(uint32_t port) override;

    /**
     * @brief 
     * 
     * @param port 
     * @param value 
     */
    virtual void pin(uint32_t port, uint32_t value) override;
    
    /**
     * @brief 
     * 
     * @param port 
     * @param mask 
     */
    virtual void pinClear(uint32_t port, uint32_t mask) override;

    /**
     * @brief 
     * 
     * @param port 
     * @param mask 
     */
    virtual void pinSet(uint32_t port, uint32_t mask) override;
    
    /**
     * @brief 
     * 
     * @param port 
     * @param mask 
     */
    virtual void pinToggle(uint32_t port, uint32_t mask) override;

  /* **************************************************************************************
   * Public Method
   */
  public:
    
    /**
     * @brief 
     * 
     * @param pin 
     * @param mode 
     * @return true 
     * @return false 
     */
    bool configInput(uint32_t pin, core::arterytek::at32f415::general::port::InputMode mode);
    
    /**
     * @brief 
     * 
     * @param pin 
     * @param mode 
     * @param opendrain 
     * @param function 
     * @param value 
     * @return true 
     * @return false 
     */
    bool configOutput(uint32_t pin, core::arterytek::at32f415::general::port::OutputMode mode, 
                      bool opendrain, 
                      bool function, 
                      bool value);

    /**
     * @brief Set the Function object
     * 
     * @param pin 
     * @param enable 
     * @return true 
     * @return false 
     */
    bool setFunction(uint32_t pin, bool opendrain);

    /**
     * @brief Get the Base object
     * 
     * @return void* 
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
