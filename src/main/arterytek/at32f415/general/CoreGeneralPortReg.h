/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_D048A118_242D_4A65_869B_BF2600664039
#define CORE_ARTERYTEK_AT32F415_D048A118_242D_4A65_869B_BF2600664039

/* ****************************************************************************************
 * Include
 */
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace general{
      enum struct CoreGeneralPortReg : char;
    }
  }
}

/* ****************************************************************************************
 * Class/Interface/Struct
 */  
enum struct arterytek::at32f415::general::CoreGeneralPortReg : char{
  REG_GPIOA = 0,
  REG_GPIOB = 1,
  REG_GPIOC = 2,
  REG_GPIOD = 3,
  REG_GPIOF = 4
};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D048A118_242D_4A65_869B_BF2600664039 */
