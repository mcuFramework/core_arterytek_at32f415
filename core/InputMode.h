/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_BA1F141E_4C52_4D14_ADD3_852400BDE8F1
#define CORE_ARTERYTEK_AT32F415_BA1F141E_4C52_4D14_ADD3_852400BDE8F1

/* ****************************************************************************************
 * Include
 */
#include "mcuf/package-info.h" 

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  enum struct InputMode : char;
}

/* ****************************************************************************************
 * Class/Interface/Struct
 */  
enum struct core::InputMode : char{
  OPEN,
  ANALOG,
  PULLDOWN,
  PULLUP
};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_BA1F141E_4C52_4D14_ADD3_852400BDE8F1 */
