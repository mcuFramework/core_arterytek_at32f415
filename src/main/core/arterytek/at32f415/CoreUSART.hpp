/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141
#define CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"


/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CoreUSART;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreUSART extends mcuf::util::RingBuffer
  implements mcuf::hal::SerialPort, mcuf::function::Runnable, mcuf::io::OutputStream{
       
  /* **************************************************************************************
   * Subclass
   */
  private: class Packet;
      
  /* **************************************************************************************
   * Class ExecuteTask
   */

  /* **************************************************************************************
   * Class Packet
   */
  private: class Packet extends mcuf::lang::Object
    implements mcuf::function::Runnable{
    public: uint16_t mLength;
    public: uint16_t mCount;    
    public: uint8_t* mPointer;
    public: Event* mEvent;
    public: Event::Status mStatus;
    public: mcuf::io::channel::ByteBuffer* mByteBuffer;
    
    public: Packet(void) = default;
    public: virtual ~Packet(void) = default;
    
    public: void clear(void);
    public: bool isExist(void);
    public: bool init(mcuf::io::channel::ByteBuffer& byteBuffer, Event* event);
    
    public: virtual void run(void) override;
  };

  /* **************************************************************************************
   * Enum Register
   */
  public: enum Register{
    REG_USART1,
    REG_USART2,
    REG_USART3,
    REG_UART4,
    REG_UART5,
  };

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: Register mRegister;
  private: Packet mPacketRead;
  private: Packet mPacketWrite;

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */

  /**
   * Construct.
   */
   public: CoreUSART(Register reg, mcuf::lang::Memory& memory);

  /**
   * Disconstruct.
   */
  public: ~CoreUSART(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::Base
   */

  /**
   * uninitialze hardware.
   */
  public: virtual bool deinit(void) override;

  /**
   * initialze hardware;
   */
  public: virtual bool init(void) override;
  
  /**
   * get hardware initialzed status.
   * 
   * @return false = not init, true = initd
   */
  public: virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::hal::SerialPort
   */

  /**
   * 
   */
  public: virtual bool abortRead(void) override;

  /**
   * 
   */
  public: virtual bool abortWrite(void) override;

  /**
   * 
   */
  public: virtual uint32_t baudrate(void) override;

  /**
   * 
   */
  public: virtual uint32_t baudrate(uint32_t rate) override;

  /**
   *
   */
  public: virtual bool readBusy(void) override;

  /**
   *
   */
  public: virtual bool writeBusy(void) override;

  /**
   * 
   */
  public: virtual bool read(mcuf::io::channel::ByteBuffer* byteBuffer, 
                            mcuf::hal::SerialPort::Event* event) override;

  /**
   * 
   */
  public: virtual bool write(mcuf::io::channel::ByteBuffer* byteBuffer, 
                             mcuf::hal::SerialPort::Event* event) override;

  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Runnable
   */
                             
  /**
   *
   */
  public: virtual void run(void) override;
  
  /* **************************************************************************************
   * Public Method <Override> - mcuf::io::OutputStream
   */
  
  /**
   *
   */
  virtual void flush(void) override;
  
  /**
   *  write nonBlocking
   */
  virtual void write(mcuf::io::channel::ByteBuffer* byteBuffer, 
                     void* attachment,
                     mcuf::io::channel::CompletionHandler<int, void*>* handler) override;  
                             
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



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141 */
