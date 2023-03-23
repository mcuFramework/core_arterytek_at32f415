/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_91F8A9FC_556B_4D1C_8D4B_E515D285F7DF
#define CORE_ARTERYTEK_AT32F415_91F8A9FC_556B_4D1C_8D4B_E515D285F7DF

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  class CoreSerialBusSlaveErrorEvent;
  class CoreSerialBusSlave;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::CoreSerialBusSlaveErrorEvent extends mcuf::Object implements
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
    core::CoreSerialBusSlave& mBase;

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
     * @brief Construct a new Core Serial Bus Slave Error Event object
     * 
     * @param coreSerialBusSlave 
     */
    CoreSerialBusSlaveErrorEvent(core::CoreSerialBusSlave& coreSerialBusSlave);

    /**
     * @brief Destroy the Core Serial Bus Slave Error Event object
     * 
     */
    virtual ~CoreSerialBusSlaveErrorEvent(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

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

#endif /* CORE_ARTERYTEK_AT32F415_91F8A9FC_556B_4D1C_8D4B_E515D285F7DF */
