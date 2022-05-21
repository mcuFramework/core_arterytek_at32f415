/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_C09D221D_8804_4F57_BB8A_559BDB91F9E1
#define CORE_ARTERYTEK_AT32F415_C09D221D_8804_4F57_BB8A_559BDB91F9E1

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
      struct CoreSerialPeriphPacket;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct arterytek::at32f415::serial::CoreSerialPeriphPacket{
  mcuf::io::ByteBuffer* byteBuffer;
  uint8_t* ptr;
  uint32_t length;
  uint32_t count;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_C09D221D_8804_4F57_BB8A_559BDB91F9E1 */
