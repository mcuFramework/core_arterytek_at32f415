/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_D80282E8_F158_47F0_BD7E_7596EC8BCA9A
#define CORE_ARTERYTEK_AT32F415_D80282E8_F158_47F0_BD7E_7596EC8BCA9A

/* ****************************************************************************************
 * Include
 */
#include "mcuf/package-info.h" 

/* ****************************************************************************************
 * Namespace
 */  

namespace core{
  enum struct CoreSerialPortReg : char;
}

/* ****************************************************************************************
 * Class/Interface/Struct
 */  
enum struct core::CoreSerialPortReg : char{
  REG_USART1 = 0,
  REG_USART2 = 1,
  REG_USART3 = 2,
  REG_UART4  = 3,
  REG_UART5  = 4
};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_D80282E8_F158_47F0_BD7E_7596EC8BCA9A */
