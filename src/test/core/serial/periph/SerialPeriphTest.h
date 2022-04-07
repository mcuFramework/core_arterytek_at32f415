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
  public hal::serial::SerialPeriphEvent{

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
  
    arterytek::at32f415::general::CoreGeneralPin* mChipSelectPin[4];
    arterytek::at32f415::serial::CoreSerialPeriph* mCoreSerialPeriph;
  
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
   * Public Method <Override> - hal::serial::SerialPeriphEvent
   */  
  public:
  
    /**
     * @brief 
     * 
     * @param status 
     * @param transfer 
     * @param receiver 
     */
    virtual void onSerialPeriphEvent(hal::serial::SerialPeriphStatus status, 
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
