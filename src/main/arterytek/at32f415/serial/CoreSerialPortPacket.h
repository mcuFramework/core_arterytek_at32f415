/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_E18452D0_D438_47E9_ACE9_3E3BC0006D12
#define CORE_ARTERYTEK_AT32F415_E18452D0_D438_47E9_ACE9_3E3BC0006D12

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace serial{
      class CoreSerialPortPacket;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class arterytek::at32f415::serial::CoreSerialPortPacket extends mcuf::lang::Object implements 
  public mcuf::function::Runnable{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */
  public: 
    uint16_t mLength;
    uint16_t mCount;    
    uint8_t* mPointer;
    hal::serial::SerialPortEvent* mEvent;
    hal::serial::SerialPortStatus mStatus;
    mcuf::io::ByteBuffer* mByteBuffer;
    void* mAttachment;
  
  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */

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
     * Construct.
     */
    CoreSerialPortPacket(void);

    /**
     * Destruct.
     */
    virtual ~CoreSerialPortPacket(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> mcuf::function::Runnable
   */
  public: 
    /**
     *
     */
    virtual void run(void) override;

  /* **************************************************************************************
   * Public Method
   */
  public: 
    /**
     *
     */
    void clear(void);
    
    /**
     *
     */
    bool isExist(void);
    
    /**
     *
     */
    bool init(mcuf::io::ByteBuffer& byteBuffer, 
              void* attachment,
              hal::serial::SerialPortEvent* event);
                      
    /**
     *
     */
    bool init(void* pointer, 
              int length,
              void* attachment,
              hal::serial::SerialPortEvent* event);                    
  
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

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_E18452D0_D438_47E9_ACE9_3E3BC0006D12 */
