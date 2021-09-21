/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "core/arterytek/at32f415/Core.hpp" 
#include "core/arterytek/at32f415/CoreInterrupt.hpp" 

#include "bsp_arterytek_at32f415/at32f4xx.h"
#include "bsp_arterytek_at32f415/core_cm4.h"
#include "bsp_arterytek_at32f415/at32f4xx_exti.h"

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
extern "C" void TMR1_CC_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1_CC]->run();
}

/**
 *
 */
extern "C" void TMR1_BRK_TMR9_IRQHandler(void){
  if(TMR1->STS & TMR_STS_BRKIF)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1_BRK]->run();
  
  if(TMR9->STS)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR9]->run();

}

/**
 *
 */
extern "C" void TMR1_OV_TMR10_IRQHandler(void){
  if(TMR1->STS & TMR_STS_UEVIF)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1]->run();
    
  
  if(TMR10->STS)
     Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR10]->run();
}

/**
 *
 */
extern "C" void TMR1_TRG_COM_TMR11_IRQHandler(void){
  if(TMR1->STS)
    Core::interrupt.mHandle[CoreInterrupt::IRQ_TMR1_TRG_COM]->run();
  
  if(TMR11->STS)
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
 * Function - EXTI
 */

/**
 *
 */
extern "C" void EXTI0_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI0]->run();
}

/**
 *
 */
extern "C" void EXTI1_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI1]->run();
}

/**
 *
 */
extern "C" void EXTI2_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI2]->run();
}

/**
 *
 */
extern "C" void EXTI3_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI3]->run();
}

/**
 *
 */
extern "C" void EXTI4_IRQHandler(void){
  Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI4]->run();
}

/**
 *
 */
extern "C" void EXTI9_5_IRQHandler(void){
  for(;;){
		if(EXTI->PND & 0x00000020)
      Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI5]->run();
		
		else if(EXTI->PND & 0x00000040)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI6]->run();
		
		else if(EXTI->PND & 0x00000080)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI7]->run();
		
		else if(EXTI->PND & 0x00000100)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI8]->run();
		
		else if(EXTI->PND & 0x00000200)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI9]->run();
		
		else
			break;
	}
}

/**
 *
 */
extern "C" void EXTI15_10_IRQHandler(void){
	for(;;){
		if(EXTI->PND & 0x00000400)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI10]->run();
		
		else if(EXTI->PND & 0x00000800)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI11]->run();
		
		else if(EXTI->PND & 0x00001000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI12]->run();
		
		else if(EXTI->PND & 0x00002000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI13]->run();
		
		else if(EXTI->PND & 0x00004000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI14]->run();
		
		else if(EXTI->PND & 0x00008000)
			Core::interrupt.mHandle[CoreInterrupt::IRQ_EXTI15]->run();
		
		else
			break;
	}  
}



/* *****************************************************************************************
 *    End of file
 */
