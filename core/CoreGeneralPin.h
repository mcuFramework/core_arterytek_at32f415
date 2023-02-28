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

//-----------------------------------------------------------------------------------------
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreGeneralPort.h" 

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  class CoreGeneralPin;
}



/* ****************************************************************************************
 * Class Object
 */  
class core::CoreGeneralPin  extends mcuf::Object implements 
  public mcuf::hal::GeneralPin{

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
  private: 
    void* mBase;
    uint32_t mPin;


  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */
  public:
    
    /**
     * Construct.
     */
    CoreGeneralPin(core::CoreGeneralPort& base, 
                   uint32_t pin);

    /**
     * Dis:.
     */
    virtual ~CoreGeneralPin(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
   */
  public:
    
    /**
     * Get io direction.
     * 
     * @return false = input, true = output.
     */
    virtual bool dir(void) override;

    /**
     * Set io direction.
     * 
     * @param dir false = input, true = output.
     */
    virtual void dir(bool dir) override;
    
    /**
     * 
     */
    virtual mcuf::hal::GeneralPinMode pinMode(void) override;

    /**
     * 
     */
    virtual bool pinMode(mcuf::hal::GeneralPinMode mode) override; 

    /**
     * Set io pin to high.
     */
    virtual void setHigh(void) override;
    
    /**
     * Set io direction to input.
     */
    virtual void setInput(void) override;

    /**
     * Set io pin to low.
     */
    virtual void setLow(void) override;
    
    /**
     * Set io direction to output.
     */
    virtual void setOutput(void) override;

    /**
     * Set io not logic.
     */
    virtual void setToggle(void) override;

    /**
     * Get io pin.
     *
     * @return false = low, true = high.
     */
    virtual bool value(void) override;

    /**
     * Set io pin to high or low.
     *
     * @param value false = low, true = high.
     */
    virtual void value(bool level) override;


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
