/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_EF4F5B70_C257_44EE_8874_9BBD7AFAD856
#define CORE_ARTERYTEK_AT32F415_EF4F5B70_C257_44EE_8874_9BBD7AFAD856

/* ****************************************************************************************
 * Include
 */  
#include "core/arterytek/at32f415/CoreGPIO.hpp" 

#include "mcuf.h"


/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CorePin;
    }
  }
}



/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CorePin :
      public mcuf::hal::GeneralPurposePin{

  /* **************************************************************************************
   * Subclass
   */

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
  private: uint32_t mPin;


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
  public: CorePin(core::arterytek::at32f415::CoreGPIO* base, uint32_t pin);

  /**
   * Disconstruct.
   */
  public: virtual ~CorePin(void) = default;

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
   * Get io direction.
   * 
   * @return false = input, true = output.
   */
  public: virtual bool dir(void) override;

  /**
   * Set io direction.
   * 
   * @param dir false = input, true = output.
   */
  public: virtual void dir(bool dir) override;
  
   /**
   * 
   */
  public: virtual PinMode pinMode(void) override;

  /**
   * 
   */
  public: virtual bool pinMode(PinMode mode) override; 

  /**
   * Set io pin to high.
   */
  public: virtual void setHigh(void) override;
  
  /**
   * Set io direction to input.
   */
  public: virtual void setInput(void) override;

  /**
   * Set io pin to low.
   */
  public: virtual void setLow(void) override;
  
  /**
   * Set io direction to output.
   */
  public: virtual void setOutput(void) override;

  /**
   * Set io not logic.
   */
  public: virtual void setToggle(void) override;

  /**
   * Get io pin.
   *
   * @return false = low, true = high.
   */
  public: virtual bool value(void) override;

  /**
   * Set io pin to high or low.
   *
   * @param value false = low, true = high.
   */
  public: virtual void value(bool level) override;


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

#endif/* CORE_ARTERYTEK_AT32F415_EF4F5B70_C257_44EE_8874_9BBD7AFAD856 */
