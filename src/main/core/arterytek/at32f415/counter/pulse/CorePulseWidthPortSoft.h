/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_B09B7E0F_F374_4212_879E_18612F21D19B
#define CORE_ARTERYTEK_AT32F415_B09B7E0F_F374_4212_879E_18612F21D19B

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/counter/pulse/CorePulseWidthPort.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace counter{
        namespace pulse{
          class CorePulseWidthPortSoft;
        }
      }
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::arterytek::at32f415::counter::pulse::CorePulseWidthPortSoft extends
  core::arterytek::at32f415::counter::pulse::CorePulseWidthPort implements
  public mcuf::hal::InterruptEvent{

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
    mcuf::hal::general::pin::GeneralPin* mGeneralPin[4];

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
     *
     */
	  CorePulseWidthPortSoft(core::arterytek::at32f415::counter::pulse::CorePulseWidthReg reg);
  
    /**
     *
     */
	  virtual ~CorePulseWidthPortSoft(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - core::arterytek::at32f415::counter::pulse::CorePulseWidthPort
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
   * Public Method <Override> - mcuf::hal::InterruptEvent
   */
  public: 

    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;
  
  /* **************************************************************************************
   * Public Method
   */
  public:
    
    /**
     *
     */
    virtual bool setPin(int pin, mcuf::hal::general::pin::GeneralPin* generalPin);

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

#endif /* CORE_ARTERYTEK_AT32F415_B09B7E0F_F374_4212_879E_18612F21D19B */
