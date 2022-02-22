/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_519BB51C_09CB_40B0_83D4_C068D10A5FE1
#define CORE_ARTERYTEK_AT32F415_519BB51C_09CB_40B0_83D4_C068D10A5FE1

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "tool/package-info.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace serial{
    namespace port{
      class SerialPortTest;
    }
  }
}

/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::serial::port::SerialPortTest extends mcuf::lang::Object implements
  public mcuf::function::Runnable, 
  public mcuf::hal::serial::port::SerialPortEvent{

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private:
    mcuf::util::Stacker& mStacker;
    tool::Console* mConsole;
    tool::BoardPeriph* mBoardPeriph;
    tool::Blinker mBlinker;
    int mSelectMode;
    int mStage;
    int mPackageNumber;
    int mLength;
  
    mcuf::io::ByteBuffer* mReceiver;


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
     * 
     */
    SerialPortTest(mcuf::util::Stacker& stacker);

    /**
     * 
     */
    virtual ~SerialPortTest(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Runnable
   */
  public:
    
    /**
     * @brief 
     * 
     */
    virtual void run(void) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::serial::port::SerialPortEvent
   */
  public:
    
    /**
     * @brief 
     * 
     * @param status 
     * @param byteBuffer 
     */
    virtual void onSerialPortEvent(mcuf::hal::serial::port::SerialPortStatus status, 
                                   mcuf::io::ByteBuffer* byteBuffer) override;  

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
  private:

    /**
     * @brief 
     * 
     */
    void init(void);
  
    void beginRead(int len);
  
    void readCommand(mcuf::io::ByteBuffer* byteBuffer);
  
    void readPackage(mcuf::io::ByteBuffer* byteBuffer);
  

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_519BB51C_09CB_40B0_83D4_C068D10A5FE1 */
