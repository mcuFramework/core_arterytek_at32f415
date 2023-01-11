/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_67D46C38_F1AA_4FDA_B88E_B2575C633492
#define CORE_ARTERYTEK_AT32F415_67D46C38_F1AA_4FDA_B88E_B2575C633492

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
  struct CoreSerialBusConfig;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct core::CoreSerialBusConfig{
  void* mBase;
  uint32_t mCmr;
  core::CoreInterrupt::Irq mIrqEvent;
  core::CoreInterrupt::Irq mIrqError;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_67D46C38_F1AA_4FDA_B88E_B2575C633492 */
