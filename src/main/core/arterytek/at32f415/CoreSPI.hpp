/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_ABB9BEEF_3AF5_49CB_AB49_A1A1B3886DA7
#define CORE_ARTERYTEK_AT32F415_ABB9BEEF_3AF5_49CB_AB49_A1A1B3886DA7

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"
#include "CoreEntitySPI.hpp"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CoreSPI;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreSPI :
      public mcuf::hal::Base{

  /* **************************************************************************************
   * Subclass
   */
  
  /* **************************************************************************************
   * Struct Packet
   */
  private: struct Packet{
    core::arterytek::at32f415::CoreEntitySPI* coreEntitySPI;
  };

  /* **************************************************************************************
   * Enum Register
   */
  public: enum Register{
    SPI1,
    SPI2
  };
        
  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: void* regAddress;
  private: mcuf::util::Fifo* fifo;

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
  public: CoreSPI(Register reg);

  /**
   * Destruct.
   */
  public: virtual ~CoreSPI(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
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
  
  /**
   *
   */
  private: inline void xferClear(void);

  /**
   * 
   */
  private: inline void spiEnable(void);

  /**
   * 
   */
  private: inline void spiDisable(void);

  /**
   * 
   */
  private: inline void isrTransferEnable(void);

  /**
   * 
   */
  private: inline void isrTransferDisable(void);

  /**
   * 
   */
  private: inline void isrReceiverEnable(void);

  /**
   * 
   */
  private: inline void isrReceiverDisable(void);

  /**
   * 
   */
  private: inline void isrEnable(void);

  /**
   * 
   */
  private: inline void isrDisable(void);
  
  
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


#endif/* CORE_ARTERYTEK_AT32F415_ABB9BEEF_3AF5_49CB_AB49_A1A1B3886DA7 */
