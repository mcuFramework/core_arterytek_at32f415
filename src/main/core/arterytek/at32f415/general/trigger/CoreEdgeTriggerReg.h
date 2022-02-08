/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_A4D5781B_552C_4BC9_A5F5_ADF9BB2CE9A8
#define CORE_ARTERYTEK_AT32F415_A4D5781B_552C_4BC9_A5F5_ADF9BB2CE9A8

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace general{
        namespace trigger{
          enum struct CoreEdgeTriggerReg : char;
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Class/Interface/Struct
 */  
enum struct core::arterytek::at32f415::general::trigger::CoreEdgeTriggerReg : char{
  REG_EXINT0  =  0,
  REG_EXINT1  =  1,
  REG_EXINT2  =  2,
  REG_EXINT3  =  3,
  REG_EXINT4  =  4,
  REG_EXINT5  =  5,
  REG_EXINT6  =  6,
  REG_EXINT7  =  7,
  REG_EXINT8  =  8,
  REG_EXINT9  =  9,
  REG_EXINT10 = 10,
  REG_EXINT11 = 11,
  REG_EXINT12 = 12,
  REG_EXINT13 = 13,
  REG_EXINT14 = 14,
  REG_EXINT15 = 15,
};

#endif/* CORE_ARTERYTEK_AT32F415_A4D5781B_552C_4BC9_A5F5_ADF9BB2CE9A8 */
