/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_417580DF_A500_4B9E_BBA7_0D0C69198C2E
#define CORE_ARTERYTEK_AT32F415_417580DF_A500_4B9E_BBA7_0D0C69198C2E

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/counter/CorePulseWidthReg.h"
#include "arterytek/at32f415/Core.h"
#include "arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace counter{
      class CorePulseWidthPort;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::counter::CorePulseWidthPort extends mcuf::lang::Object implements
  public hal::counter::PulseWidthPort{

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */
  protected:
    arterytek::at32f415::counter::CorePulseWidthReg mRegister;
  
  /* **************************************************************************************
   * Variable <Private>
   */

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
     * @brief Construct a new Core Pulse Width Port object
     * 
     * @param reg 
     */
    CorePulseWidthPort(arterytek::at32f415::counter::CorePulseWidthReg reg);

    /**
     * @brief Destroy the Core Pulse Width Port object
     * 
     */
    virtual ~CorePulseWidthPort(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - hal::Base
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
     * @brief initialze hardware
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;

    /**
     * @brief 
     * 
     * @return true initd.
     * @return false not init.
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::counter::PulseWidthPort
   */
  public:
    /**
     * @brief Set the Frequence object
     * 
     * @param hz 
     * @return true 
     * @return false 
     */
    virtual bool setFrequence(float hz) override;

    /**
     * @brief Get the Frequence object
     * 
     * @return float 
     */
    virtual float getFrequence(void) override;

    /**
     * @brief Get the Period object
     * 
     * @return int 
     */
    virtual int getPeriod(void) override;
    
    /**
     * @brief Get the Duty object
     * 
     * @param pin 
     * @return float 
     */
    virtual float getDuty(int pin) override;

    /**
     * @brief Get the Duty Tick object
     * 
     * @param pin 
     * @return int 
     */
    virtual int getDutyTick(int pin) override;
    
    /**
     * @brief Set the Duty object
     * 
     * @param pin 
     * @param percent 
     * @return true 
     * @return false 
     */
    virtual bool setDuty(int pin, float percent) override;
    
    /**
     * @brief Set the Duty Tick object
     * 
     * @param pin 
     * @param duty 
     * @return true 
     * @return false 
     */
    virtual bool setDutyTick(int pin, int duty) override;

    /**
     * @brief 
     * 
     * @param pin 
     * @return true 
     * @return false 
     */
    virtual bool enable(int pin) override;
  
    /**
     * @brief 
     * 
     * @param pin 
     * @return true 
     * @return false 
     */
    virtual bool disable(int pin) override;  
  
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
  protected:
    
    /**
     *
     */
    void setDivider(uint32_t tick);
  
    /**
     *
     */
    bool outputControl(int pin, bool enable);
  
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

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_417580DF_A500_4B9E_BBA7_0D0C69198C2E */
