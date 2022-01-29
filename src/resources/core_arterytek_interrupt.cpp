/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "core/arterytek/at32f415/Core.h" 
#include "core/arterytek/at32f415/CoreInterrupt.h" 

#include "bsp_arterytek_at32f415/at32f415.h"
#include "bsp_arterytek_at32f415/core_cm4.h"
#include "bsp_arterytek_at32f415/at32f415_exint.h"

/* ****************************************************************************************
 * Using
 */  
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreInterrupt;

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Extern
 */

/* ****************************************************************************************
 * Struct
 */

/* ****************************************************************************************
 * Static Variable
 */
 
/* ****************************************************************************************
 * Variable
 */

/* ****************************************************************************************
 * List
 */
 
/**
 * Inline function list
 */
 
/**
 * Static function list
 */

/* ****************************************************************************************
 * Inline Function
 */

/* ****************************************************************************************
 * Static Function
 */

/* ****************************************************************************************
 * Function
 */
 
/* ****************************************************************************************
 * Function - SPI/I2S
 */

/**
 *
 */
extern "C" void SPI1_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_SPI1]->run();
}

/**
 *
 */
extern "C" void SPI2_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_SPI2]->run();
}

/* ****************************************************************************************
 * Function - USART
 */

/**
 *
 */
extern "C" void USART1_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_USART1]->run();
}

/**
 *
 */
extern "C" void USART2_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_USART2]->run();
}

/**
 *
 */
extern "C" void USART3_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_USART3]->run();
}

/**
 *
 */
extern "C" void UART4_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_UART4]->run();
}

/**
 *
 */
extern "C" void UART5_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_UART5]->run();
}

/* ****************************************************************************************
 * Function - TMR
 */

/**
 *
 */
extern "C" void TMR1_CH_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1_CC]->run();
}

/**
 *
 */
extern "C" void TMR1_BRK_TMR9_IRQHandler(void){
  if(TMR1->ists_bit.brkif)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1_BRK]->run();
  
  if(TMR9->ists)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR9]->run();

}

/**
 *
 */
extern "C" void TMR1_OVF_TMR10_IRQHandler(void){
  if(TMR1->ists_bit.ovfif)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1]->run();
    
  
  if(TMR10->ists)
     Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR10]->run();
}

/**
 *
 */
extern "C" void TMR1_TRG_HALL_TMR11_IRQHandler(void){
  if(TMR1->ists_bit.trgif)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1_TRG_COM]->run();
  
  if(TMR11->ists)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR11]->run();
}

/**
 *
 */
extern "C" void TMR2_GLOBAL_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR2]->run();
}

/**
 *
 */
extern "C" void TMR3_GLOBAL_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR3]->run();
}

/**
 *
 */
extern "C" void TMR4_GLOBAL_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR4]->run();
}

/**
 *
 */
extern "C" void TMR5_GLOBAL_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR5]->run();
}



/* ****************************************************************************************
 * Function - EXINT
 */

/**
 *
 */
extern "C" void EXINT0_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT0]->run();
}

/**
 *
 */
extern "C" void EXINT1_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT1]->run();
}

/**
 *
 */
extern "C" void EXINT2_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT2]->run();
}

/**
 *
 */
extern "C" void EXINT3_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT3]->run();
}

/**
 *
 */
extern "C" void EXINT4_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT4]->run();
}

/**
 *
 */
extern "C" void EXINT9_5_IRQHandler(void){
  for(;;){
		if(EXINT->intsts & 0x00000020)
      Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT5]->run();
		
		else if(EXINT->intsts & 0x00000040)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT6]->run();
		
		else if(EXINT->intsts & 0x00000080)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT7]->run();
		
		else if(EXINT->intsts & 0x00000100)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT8]->run();
		
		else if(EXINT->intsts & 0x00000200)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT9]->run();
		
		else
			break;
	}
}

/**
 *
 */
extern "C" void EXINT15_10_IRQHandler(void){
	for(;;){
		if(EXINT->intsts & 0x00000400)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT10]->run();
		
		else if(EXINT->intsts & 0x00000800)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT11]->run();
		
		else if(EXINT->intsts & 0x00001000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT12]->run();
		
		else if(EXINT->intsts & 0x00002000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT13]->run();
		
		else if(EXINT->intsts & 0x00004000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT14]->run();
		
		else if(EXINT->intsts & 0x00008000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXINT15]->run();
		
		else
			break;
	}  
}



/* *****************************************************************************************
 *    End of file
 */
