/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_555DF436_4F22_4BC9_84AD_462949BD4184
#define CORE_ARTERYTEK_AT32F415_555DF436_4F22_4BC9_84AD_462949BD4184

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/analog/input/CoreAnalogInputPort.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace analog{
        namespace input{
          class CoreAnalogInputPin;
        }
      }
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::arterytek::at32f415::analog::input::CoreAnalogInputPin extends mcuf::lang::Object implements
  public hal::analog::AnalogInputPin{

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
    core::arterytek::at32f415::analog::input::CoreAnalogInputPort& mCoreAnalogInputPort;
    uint16_t mChannel;

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
     * @brief Construct a new Core Analog Input Pin object
     * 
     */
    CoreAnalogInputPin(core::arterytek::at32f415::analog::input::CoreAnalogInputPort& coreAnalogInputPort, uint16_t channel);

    /**
     * @brief Destroy the Core Analog Input Pin object
     * 
     */
    virtual ~CoreAnalogInputPin(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> hal::analog::AnalogInputPin
   */
  public:
    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t convert(void) override;

    /**
     * @brief Get the adc convert bit.
     * 
     * @return uint32_t 
     */
    virtual uint32_t getConvertBit(void) override;

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

#endif /* CORE_ARTERYTEK_AT32F415_555DF436_4F22_4BC9_84AD_462949BD4184 */
