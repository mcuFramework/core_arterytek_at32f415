/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_B1A7652D_F659_4F29_94D4_855853FB027E
#define CORE_ARTERYTEK_AT32F415_B1A7652D_F659_4F29_94D4_855853FB027E

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */
namespace arterytek{
  namespace at32f415{
    namespace serial{
      enum struct CoreSerialBusErrorCode : char;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
enum struct arterytek::at32f415::serial::CoreSerialBusErrorCode : char{
  BUSERR,
  ARLOST,
  ACKFAIL,
  OVER,
  PECERR,
  TMOUT,
  ALERTF
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_B1A7652D_F659_4F29_94D4_855853FB027E */
