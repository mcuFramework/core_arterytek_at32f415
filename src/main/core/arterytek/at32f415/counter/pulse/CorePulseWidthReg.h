/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_4070C469_83AD_4D71_B727_BD0D2D2AAF6B
#define CORE_ARTERYTEK_AT32F415_4070C469_83AD_4D71_B727_BD0D2D2AAF6B

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
      namespace counter{
        namespace pulse{
          enum struct CorePulseWidthReg : char;
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Class/Interface/Struct
 */  
enum struct core::arterytek::at32f415::counter::pulse::CorePulseWidthReg : char{
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

#endif/* CORE_ARTERYTEK_AT32F415_4070C469_83AD_4D71_B727_BD0D2D2AAF6B */
