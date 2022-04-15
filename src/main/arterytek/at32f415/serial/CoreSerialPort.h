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

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "arterytek/at32f415/serial/CoreSerialPortConfig.h"
#include "arterytek/at32f415/serial/CoreSerialPortPacket.h"
#include "arterytek/at32f415/serial/CoreSerialPortReg.h"


/* ****************************************************************************************
 * Namespace
 */  

namespace arterytek{
  namespace at32f415{
    namespace serial{
      class CoreSerialPort;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class arterytek::at32f415::serial::CoreSerialPort extends mcuf::io::RingBuffer implements 
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
    static const arterytek::at32f415::serial::CoreSerialPortConfig mCoreSerialPortConfig[5];
  
    arterytek::at32f415::serial::CoreSerialPortReg mRegister;
    arterytek::at32f415::serial::CoreSerialPortPacket mPacketRead;
    arterytek::at32f415::serial::CoreSerialPortPacket mPacketWrite;

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
    CoreSerialPort(arterytek::at32f415::serial::CoreSerialPortReg reg, const mcuf::lang::Memory& memory);

    /**
     * @brief Destroy the Core Usart object
     * 
     */
    virtual ~CoreSerialPort(void) override;

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
    virtual bool abortWrite(void) override;

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
    virtual bool write(mcuf::io::ByteBuffer& byteBuffer,
                       void* attachment,
                       hal::serial::SerialPortEvent* event) override;

  /* **************************************************************************************
   * Public Method <Override> - hal::serial::SerialPortReceiver
   */
  public:
    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t avariable(void) override;

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
     * @param result 
     * @return true 
     * @return false 
     */
    virtual bool readByte(char& result) override;

    /**
     * @brief 
     * 
     * @param buffer 
     * @param maxLength 
     * @return uint32_t 
     */
    virtual uint32_t read(void* buffer, uint32_t maxLength) override;

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
