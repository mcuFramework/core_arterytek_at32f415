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
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Namespace
 */

namespace arterytek{
  namespace at32f415{
    namespace serial{
      struct CoreSerialBusConfig;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct arterytek::at32f415::serial::CoreSerialBusConfig{
  void* mBase;
  uint32_t mCmr;
  arterytek::at32f415::CoreInterrupt::Irq mIrqEvent;
  arterytek::at32f415::CoreInterrupt::Irq mIrqError;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_67D46C38_F1AA_4FDA_B88E_B2575C633492 */
