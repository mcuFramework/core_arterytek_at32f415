/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141
#define CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141

/**
 *  USART1:
 *    Pin out:
 *      USART1_TX   - PA9
 *      USART1_RX   - PA10
 *      USART1_CK   - PA8
 *      USART1_CTS  - PA11
 *      USART1_RTS  - PA12
 *
 *  USART2: 
 *    Pin out:
 *      USART2_TX   - PA2
 *      USART2_RX   - PA3
 *      USART2_CK   - PA4
 *      USART2_CTS  - PA0
 *      USART2_RTS  - PA1
 *
 *  USART3:
 *    Pin out:
 *      USART3_TX   - PB10 / PA7
 *      USART3_RX   - PB11 / PA6 
 *      USART3_CK   - PB12 / PA5
 *      USART3_CTS  - PB13 / PB1
 *      USART3_RTS  - PB14 / PB0
 *
 *  UART4:
 *    Pin out:
 *      UART4_TX    - PC10 / PF4
 *      UART4_RX    - PC11 / PF5
 *
 *  UART5:
 *    Pin out:
 *      UART5_TX    - PC12
 *      UART5_RX    - PD2
 *      
 */

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
      class CoreUsart;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreUsart extends mcuf::util::RingBuffer
  implements mcuf::hal::SerialPort, mcuf::function::Runnable{
       
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
    public: mcuf::hal::SerialPortEvent* mEvent;
    public: mcuf::hal::SerialPortEvent::SerialPortStatus mStatus;
    public: mcuf::io::ByteBuffer* mByteBuffer;
    
    public: Packet(void) = default;
    public: virtual ~Packet(void) = default;
    
    public: void clear(void);
    public: bool isExist(void);
    public: bool init(mcuf::io::ByteBuffer& byteBuffer, mcuf::hal::SerialPortEvent* event);
    
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
   public: CoreUsart(Register reg, const mcuf::lang::Memory& memory);

  /**
   * Disconstruct.
   */
  public: ~CoreUsart(void);

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
  public: virtual bool read(mcuf::io::ByteBuffer* byteBuffer, 
                            mcuf::hal::SerialPortEvent* event) override;

  /**
   * 
   */
  public: virtual bool write(mcuf::io::ByteBuffer* byteBuffer, 
                             mcuf::hal::SerialPortEvent* event) override;

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
  virtual void flush(void);
  
  /**
   *  write nonBlocking
   */
  virtual void write(mcuf::io::ByteBuffer* byteBuffer, 
                     void* attachment,
                     mcuf::io::CompletionHandler<int, void*>* handler);  
                             
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
