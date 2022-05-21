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
#include "arterytek/at32f415/counter/CorePulseWidthPort.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace counter{
      class CorePulseWidthPortSoft;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::counter::CorePulseWidthPortSoft extends
  arterytek::at32f415::counter::CorePulseWidthPort implements
  public hal::InterruptEvent{

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
    hal::general::GeneralPin* mGeneralPin[4];

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
	  CorePulseWidthPortSoft(arterytek::at32f415::counter::CorePulseWidthReg reg);
  
    /**
     *
     */
	  virtual ~CorePulseWidthPortSoft(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - arterytek::at32f415::counter::CorePulseWidthPort
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
   * Public Method <Override> - hal::InterruptEvent
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
    virtual bool setPin(int pin, hal::general::GeneralPin* generalPin);

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
