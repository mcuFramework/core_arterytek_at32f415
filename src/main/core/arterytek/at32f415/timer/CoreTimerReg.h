/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_FE1A89DD_E895_41F7_9214_D2E3F75EC999
#define CORE_ARTERYTEK_AT32F415_FE1A89DD_E895_41F7_9214_D2E3F75EC999

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace timer{
        enum struct CoreTimerReg : char;
      }
    }
  }
}

/* ****************************************************************************************
 * Class/Interface/Struct
 */  
enum struct core::arterytek::at32f415::timer::CoreTimerReg : char{
  REG_TMR1  = 0,
  REG_TMR2  = 1,
  REG_TMR3  = 2,
  REG_TMR4  = 3,
  REG_TMR5  = 4,
  REG_TMR9  = 5,
  REG_TMR10 = 6,
  REG_TMR11 = 7,
};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_FE1A89DD_E895_41F7_9214_D2E3F75EC999 */
