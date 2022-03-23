/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_A1F6DB35_6272_4D2B_83BB_188CAB641C1B
#define CORE_ARTERYTEK_AT32F415_A1F6DB35_6272_4D2B_83BB_188CAB641C1B

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
      namespace serial{
        namespace bus{
          enum struct CoreSerialBusReg : char;
        }
      }
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
enum struct core::arterytek::at32f415::serial::bus::CoreSerialBusReg : char{
  REG_IIC1 = 0,
  REG_IIC2 = 1,
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_A1F6DB35_6272_4D2B_83BB_188CAB641C1B */
