/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_DC90D869_7C04_4A21_B09F_F39C011F4D74
#define CORE_ARTERYTEK_AT32F415_DC90D869_7C04_4A21_B09F_F39C011F4D74

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
    namespace periph{
      class SerialPeriphTest;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::serial::periph::SerialPeriphTest extends mcuf::lang::Object implements
  public mcuf::function::Runnable,
  public mcuf::hal::serial::periph::SerialPeriphEvent{

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
  
    core::arterytek::at32f415::general::pin::CoreGeneralPin* mChipSelectPin[4];
    core::arterytek::at32f415::serial::periph::CoreSerialPeriph* mCoreSerialPeriph;
  
    mcuf::io::ByteBuffer* mTransferByteBuffer;
    mcuf::io::ByteBuffer* mReceiverByteBuffer;
  
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
    SerialPeriphTest(mcuf::util::Stacker& stacker);

    /**
     *
     */
    virtual ~SerialPeriphTest(void);

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
   * Public Method <Override> - mcuf::hal::serial::periph::SerialPeriphEvent
   */  
  public:
  
    /**
     * @brief 
     * 
     * @param status 
     * @param transfer 
     * @param receiver 
     */
    virtual void onSerialPeriphEvent(mcuf::hal::serial::periph::SerialPeriphStatus status, 
                                     mcuf::io::ByteBuffer* transfer,
                                     mcuf::io::ByteBuffer* receiver) override;  
  
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
     *
     */
    void init(void);
  
    /**
     *
     */
    void formatBuffer(void);
  
    /**
     *
     */
    void showBuffer(void);

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_DC90D869_7C04_4A21_B09F_F39C011F4D74 */
