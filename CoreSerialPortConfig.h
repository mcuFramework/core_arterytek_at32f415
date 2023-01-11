/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_8F09A5A2_C5D5_4796_A93D_1713A565B7FC
#define CORE_ARTERYTEK_AT32F415_8F09A5A2_C5D5_4796_A93D_1713A565B7FC

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "mcuf/package-info.h" 

//-----------------------------------------------------------------------------------------
#include "./CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */
namespace core{
  struct CoreSerialPortConfig;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct core::CoreSerialPortConfig{
  void* baseAddress;
  uint32_t crmClock;
  CoreInterrupt::Irq irq;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_8F09A5A2_C5D5_4796_A93D_1713A565B7FC */
