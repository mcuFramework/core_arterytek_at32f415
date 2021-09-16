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
class core::arterytek::at32f415::CoreUSART :
      public mcuf::hal::SerialPort{

  /* **************************************************************************************
   * Subclass
   */

  public: struct Pakcet{
    void* pointer;
    void* execute;
    void* attachment;
    uint16_t length;
    uint16_t count;
  };

  /* **************************************************************************************
   * Enum Registor
   */
  public: enum Registor{
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
  private: void* regAddress;
  private: void* ringBuffer;
  private: Pakcet readPacket;
  private: Pakcet writePacket;


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
  public: CoreUSART(Registor reg, uint32_t bufferSize);

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
   * Public Method <Override>
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
  public: virtual int available(void) override;

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
  public: virtual void close(void) override;

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

  /**
   * 
   */
  public: virtual bool isOpen(void) override;

  /**
   * 
   */
  public: virtual bool open(void) override;

  /**
   * 
   */
  public: virtual bool read(mcuf::lang::Memory& memory, 
                            void* attachment,
                            mcuf::function::BiConsumer<mcuf::lang::Memory&, void*>* function) override;

  /**
   * 
   */
  public: virtual bool write(mcuf::lang::Memory& memory, 
                             void* attachment,
                             mcuf::function::BiConsumer<mcuf::lang::Memory&, void*>* function) override;

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
  
  /**
   * 
   */
  private: void clockEnable(void* base, bool enable);

  /**
   * 
   */
  private: void interruptEnable(void* base, bool enable);

  /**
   * 
   */
  private: void interruptHandler(void);

};



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D5941889_B076_4A75_A2BB_6381B6E20141 */
