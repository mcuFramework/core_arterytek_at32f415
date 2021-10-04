/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  
#include "CoreUSART.hpp"
#include "bsp_arterytek_at32f415/at32f4xx.h"


/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::CoreUSART;
using mcuf::function::Consumer;
using mcuf::lang::Memory;
using mcuf::lang::Pointer;
using mcuf::io::channel::ByteBuffer;

/* ****************************************************************************************
 * Construct Method
 */

/**
 * 
 */
CoreUSART::CoreUSART(CoreUSART::Register reg, uint32_t bufferSize){
  switch (reg){
    case CoreUSART::REG_USART1:
      this->regAddress = (void*)USART1;
      break;
    
    case CoreUSART::REG_USART2:
      this->regAddress = (void*)USART2;
      break;
    
    case CoreUSART::REG_USART3:
      this->regAddress = (void*)USART3;
      break;
    
    case CoreUSART::REG_UART4:
      this->regAddress = (void*)UART4;
      break;
    
    case CoreUSART::REG_UART5:
      this->regAddress = (void*)UART5;
      break;
    
    default:
      THROW_ERROR(MESSAGE_OUT_OF_RANGE);
  }
}

/**
 * 
 */
CoreUSART::~CoreUSART(void){

}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */
 
/* ****************************************************************************************
 * Public Method <Override>
 */

/**
 * 
 */
bool CoreUSART::abortRead(void){
  return false;
}

/**
 * 
 */
bool CoreUSART::abortWrite(void){
  return false;
}

/**
 * 
 */
uint32_t CoreUSART::baudrate(void){
  return false;
}

/**
 * 
 */
uint32_t CoreUSART::baudrate(uint32_t rate){
  return false;
}

/**
 * 
 */
bool CoreUSART::deinit(void){
  return false;
}

/**
 * 
 */
bool CoreUSART::init(void){
  return false;
}
  
/**
 * 
 */
bool CoreUSART::isInit(void){
  return false;
}

/**
 * 
 */
bool CoreUSART::read(ByteBuffer& byteBuffer, Consumer<ByteBuffer&>* consumer){
  return false;
}

/**
 * 
 */
bool CoreUSART::write(ByteBuffer& byteBuffer, Consumer<ByteBuffer&>* consumer){
  return false;
}



/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */
void CoreUSART::run(void){

}

/* ****************************************************************************************
 * Public Method
 */

/* ****************************************************************************************
 * Protected Method <Static>
 */
 
/* ****************************************************************************************
 * Protected Method <Override>
 */ 

/* ****************************************************************************************
 * Protected Method
 */

/* ****************************************************************************************
 * Private Method
 */
 
/* ****************************************************************************************
 * End of file
 */ 
