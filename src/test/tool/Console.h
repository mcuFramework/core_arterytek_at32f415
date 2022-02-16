/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_4207A82C_790E_486E_A2E7_0D66F63DC3DA
#define CORE_ARTERYTEK_AT32F415_4207A82C_790E_486E_A2E7_0D66F63DC3DA

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#define TOOL_CONSOLE_DYNAMIC_SIZE ( \
  sizeof(core::arterytek::at32f415::serial::port::CoreSerialPort) + 4 + \
  sizeof(mcuf::io::SerialPortOutputStream) + 4 +\
  sizeof(mcuf::io::OutputStreamBuffer) + 4 +\
  sizeof(mcuf::io::PrintStream) + 4\
  )
  
/* ****************************************************************************************
 * Namespace
 */  
namespace tool{
  class Console;
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class tool::Console extends mcuf::lang::Object{

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  public:
    core::arterytek::at32f415::serial::port::CoreSerialPort* mCoreSerialPort;
    mcuf::io::SerialPortOutputStream* mSerialPortOutputStream;
    mcuf::io::OutputStreamBuffer* mOutputStreamBuffer;
    mcuf::io::PrintStream* mPrintStream;
  
    uint32_t mDynamicMemory[TOOL_CONSOLE_DYNAMIC_SIZE / 4];

    uint8_t mCoreSerialPortMemory[64];
    uint8_t mPrintStreamMemory[64];
    uint8_t mOutputStreamBufferMemory[1024];

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */
  public:

    /**
     * @brief Construct a new Console object
     * 
     */
    Console(void);

    /**
     * @brief Destroy the Console object
     * 
     */
    virtual ~Console(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
   */

  /* **************************************************************************************
   * Public Method <Inline>
   */
  public:

    /**
     * @brief 
     * 
     * @return mcuf::io::PrintStream& 
     */
    inline mcuf::io::PrintStream& out(void){
      return *this->mPrintStream;
    }

  /* **************************************************************************************
   * Public Method
   */

  /* **************************************************************************************
   * Protected Method <Static>
   */

  /* **************************************************************************************
   * Protected Method <Override>
   */

  /* **************************************************************************************
   * Protected Method
   */

  /* **************************************************************************************
   * Private Method <Static>
   */

  /* **************************************************************************************
   * Private Method <Override>
   */

  /* **************************************************************************************
   * Private Method
   */

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_4207A82C_790E_486E_A2E7_0D66F63DC3DA */
