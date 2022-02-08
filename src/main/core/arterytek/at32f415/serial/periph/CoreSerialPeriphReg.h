/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_09AD1E5D_08B5_4A56_83AA_7D27448C6DC0
#define CORE_ARTERYTEK_AT32F415_09AD1E5D_08B5_4A56_83AA_7D27448C6DC0

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace serial{
        namespace periph{
          enum struct CoreSerialPeriphReg : char;
        }
      }
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
enum struct core::arterytek::at32f415::serial::periph::CoreSerialPeriphReg : char{
  REG_SPI1 = 0,
  REG_SPI2 = 1
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_09AD1E5D_08B5_4A56_83AA_7D27448C6DC0 */
