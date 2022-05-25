/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_CAF972A4_84AB_4A4F_AF85_0CCDC8DF6E9A
#define CORE_ARTERYTEK_AT32F415_CAF972A4_84AB_4A4F_AF85_0CCDC8DF6E9A

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/counter/CorePulseWidthPort.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace arterytek{
  namespace at32f415{
    namespace counter{
      class CorePulseWidthPin;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::counter::CorePulseWidthPin extends mcuf::lang::Object implements
public hal::counter::PulseWidthPin{

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
    arterytek::at32f415::counter::CorePulseWidthPort& mCorePulseWidthPort;
    int mChannel;

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
     * @brief Construct a new Core Pulse Width Pin object
     * 
     * @param corePulseWidthPort 
     * @param channel 
     */
    CorePulseWidthPin(arterytek::at32f415::counter::CorePulseWidthPort& corePulseWidthPort, int channel);

    /**
     * @brief Destroy the Core Pulse Width Pin object
     * 
     */
    virtual ~CorePulseWidthPin(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - hal::counter::PulseWidthPin
   */
  public:
    /**
     * @brief Get the Period object
     * 
     * @return int 
     */
    virtual int getPeriod(void) override;
    
    /**
     * @brief Get the Duty object
     * 
     * @return float 
     */
    virtual float getDuty(void) override;
    
    /**
     * @brief Get the Frequence object
     * 
     * @return float 
     */
    virtual float getFrequence(void) override;
    
    /**
     * @brief Set the Duty object
     * 
     * @param percent 0 ~ 1.0
     * @return true 
     * @return false 
     */
    virtual bool setDuty(float percent) override;
    
    /**
     * @brief Set the Duty object
     * 
     * @param duty 
     * @return true 
     * @return false 
     */
    virtual bool setDuty(int duty) override;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool stop(void) override;

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

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_CAF972A4_84AB_4A4F_AF85_0CCDC8DF6E9A */
