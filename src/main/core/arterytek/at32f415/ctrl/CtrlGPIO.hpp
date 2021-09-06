/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef MCUF_AT32F415_FE703035_044A_4161_8785_2DB5F7B64B6F
#define MCUF_AT32F415_FE703035_044A_4161_8785_2DB5F7B64B6F

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"


/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace ctrl{
        class CtrlGPIO;
      }
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::ctrl::CtrlGPIO :
      public mcuf::lang::Object{

  /* **************************************************************************************
   * Subclass
   */
        
  /* **************************************************************************************
   * Struct ConfigDir
   */ 
  public: struct ConfigDir{
    uint32_t ctrlh;
    uint32_t ctrll;
    uint16_t maskPullUp;
    uint16_t maskPullDown;
  };

  /* **************************************************************************************
   * Struct HalfCtrl
   */   
  public: struct HalfCtrl{
    uint32_t ctrl;
    uint8_t maskPullUp;
    uint8_t maskPullDown;
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
  private: CtrlGPIO(void) = default;

  /**
   * Disconstruct.
   */
  public: virtual ~CtrlGPIO(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */
   
  /**
   *
   */
  public: static void refresh(uint16_t port);
  
  /**
   *
   */
  public: static void refresh(void* base);  
  
  /**
   *
   */
  public: static void refreshPin(uint16_t port, uint16_t pin);
  
  /**
   *
   */
  public: static void refreshPin(void* base, uint16_t pin);  
  
  /**
   *
   */
  public: static void refreshPinMask(uint16_t port, uint16_t pinMask);
  
  /**
   *
   */
  public: static void setDir(uint16_t port, uint16_t dir);
  
  /**
   *
   */
  public: static uint16_t getDir(uint16_t port);
  
  /**
   *
   */
  public: static uint16_t getDir(void* base);
  
  /**
   *
   */
  public: static bool getPinDir(uint16_t port, uint16_t pin);
  
  /**
   *
   */
  public: static bool getPinDir(void* base, uint16_t pin);  
  
  /**
   *
   */
  public: static void setPinDir(void* base, uint8_t pin, bool dir);  
  
  /**
   *
   */
  public: static void setPinDir(uint16_t port, uint8_t pin, bool dir);

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
  private: static void ctrlRefreshPinMask(void* base, void* reg, uint16_t pinMask);
  
  /**
   *
   */
  private: static void ctrlSetPinDir(void* base, void* reg, uint16_t pin, bool dir);
  
  /**
   *
   */
  private: static void ctrlGetPinDir(void* base, void* reg, uint16_t pin);
  
  /**
   *
   */
  private: static void ctrlSetDir(void* base, void* reg, uint16_t dir);
   
  /**
   * 
   */
  private: static void* getBase(uint16_t port);
  
  /**
   * 
   */
  private: static uint16_t getPort(void* base);

  /**
   *
   */
  private: static uint8_t getHelfDir(uint32_t ctrl);
  
  /**
   *
   */
  private: static uint16_t getFullDir(uint32_t ctrll, uint32_t ctrlh);
  
  /**
   *
   */
  private: static ConfigDir getCtrlRemix(uint32_t ctrll, uint32_t ctrlh, uint16_t dir, void* reg);
  
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

#endif /* MCUF_AT32F415_FE703035_044A_4161_8785_2DB5F7B64B6F */