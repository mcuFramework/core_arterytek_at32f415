/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_9E4AFCAB_9259_45A5_ACFF_A3B1BB7CB8E1
#define CORE_ARTERYTEK_AT32F415_9E4AFCAB_9259_45A5_ACFF_A3B1BB7CB8E1

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */  
namespace arterytek{
  namespace at32f415{
    namespace analog{
      class CoreAnalogInputPort;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::analog::CoreAnalogInputPort extends mcuf::lang::Object implements
  public hal::analog::AnalogInputPort{

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  public:
    uint16_t mResult[16];

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
     * @brief Construct a new Core Analog Input Port object
     * 
     */
    CoreAnalogInputPort(void);

    /**
     * @brief Destroy the Core Analog Input Port object
     * 
     */
    virtual ~CoreAnalogInputPort(void) override;

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
     * @brief initialze hardware;
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;

    /**
     * @brief get hardware initialzed status.
     * 
     * @return true not init
     * @return false initd
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::analog::AnalogInputPortControl
   */
  public:

    /**
     * @brief 
     * 
     * @param pin 
     * @return uint32_t 
     */
    virtual uint32_t read(int pin) override;

    /**
     * @brief Get the adc convert bit.
     * 
     * @return uint32_t 
     */
    virtual uint32_t getConvertLevel(void) override;

  /* **************************************************************************************
   * Public Method <inline>
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

#endif /* CORE_ARTERYTEK_AT32F415_9E4AFCAB_9259_45A5_ACFF_A3B1BB7CB8E1 */
