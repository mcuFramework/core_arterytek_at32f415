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
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */
namespace arterytek{
  namespace at32f415{
    namespace serial{
      struct CoreSerialPortConfig;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct arterytek::at32f415::serial::CoreSerialPortConfig{
  void* baseAddress;
  uint32_t crmClock;
  CoreInterrupt::Irq irq;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_8F09A5A2_C5D5_4796_A93D_1713A565B7FC */
