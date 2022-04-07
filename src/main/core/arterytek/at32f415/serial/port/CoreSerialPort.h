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
#include "core/arterytek/at32f415/serial/port/CoreSerialPortPacket.h"
#include "core/arterytek/at32f415/serial/port/CoreSerialPortReg.h"


/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace serial{
        namespace port{
          class CoreSerialPort;
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::serial::port::CoreSerialPort extends mcuf::io::RingBuffer implements 
  public hal::serial::SerialPort,
  public hal::InterruptEvent{
       
  /* **************************************************************************************
   * Enum Register
   */

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
    core::arterytek::at32f415::serial::port::CoreSerialPortReg mRegister;
    core::arterytek::at32f415::serial::port::CoreSerialPortPacket mPacketRead;
    core::arterytek::at32f415::serial::port::CoreSerialPortPacket mPacketWrite;

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
     * @brief Construct a new Core Usart object
     * 
     * @param reg 
     * @param memory 
     */
    CoreSerialPort(core::arterytek::at32f415::serial::port::CoreSerialPortReg reg, const mcuf::lang::Memory& memory);

    /**
     * @brief Destroy the Core Usart object
     * 
     */
    ~CoreSerialPort(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - hal::Base
   */
  public:

    /**
     * @brief uninitialze hardware.
     * 
     * @return true 
     * @return false 
     */
    virtual bool deinit(void) override;

    /**
     * @brief initialze hardware
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;

    /**
     * @brief 
     * 
     * @return true initd.
     * @return false not init.
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::serial::SerialPortConfig
   */
  public:
    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t baudrate(void) override;

    /**
     * @brief 
     * 
     * @param rate 
     * @return uint32_t 
     */
    virtual uint32_t baudrate(uint32_t rate) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::serial::SerialPortTransfer
   */
  public:

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool abortRead(void) override;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool abortWrite(void) override;
  
    /**
     * @brief 
     * 
     */
    virtual bool clear(void) override;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool readBusy(void) override;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    virtual bool writeBusy(void) override;

    /**
     * @brief 
     * 
     * @param byteBuffer 
     * @param attachment 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool read(mcuf::io::ByteBuffer& byteBuffer, 
                      void* attachment,
                      hal::serial::SerialPortEvent* event) override;

    /**
     * @brief 
     * 
     * @param value 
     * @param attachment 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool skip(int value,
                      void* attachment, 
                      hal::serial::SerialPortEvent* event) override;

    /**
     * @brief 
     * 
     * @param byteBuffer 
     * @param attachment 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool write(mcuf::io::ByteBuffer& byteBuffer,
                       void* attachment,
                       hal::serial::SerialPortEvent* event) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::InterruptEvent
   */
  public: 

    /**
     * @brief 
     * 
     */
    virtual void interruptEvent(void) override;
  
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
