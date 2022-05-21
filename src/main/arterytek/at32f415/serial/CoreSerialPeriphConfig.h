/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_8C458E4C_2A42_44A1_8796_2080971D3519
#define CORE_ARTERYTEK_AT32F415_8C458E4C_2A42_44A1_8796_2080971D3519

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
      struct CoreSerialPeriphConfig;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct arterytek::at32f415::serial::CoreSerialPeriphConfig{
  void* baseAddress;
  uint32_t crmClock;
  CoreInterrupt::Irq irq;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_8C458E4C_2A42_44A1_8796_2080971D3519 */
