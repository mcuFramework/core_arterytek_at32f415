/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "core/arterytek/at32f415/bsp/at32f4xx.h"
#include "core/arterytek/at32f415/bsp/core_cm4.h"
#include "core/arterytek/at32f415/bsp/at32f4xx_exti.h"
#include "core/arterytek/at32f415/isr/isr_at32f415.h"

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
 
/* ------------------------------
 *    Usart
 * ------------------------------*/
void SPI1_IRQHandler(void){

}

void SPI2_IRQHandler(void){

}



/* ------------------------------
 *    Usart
 * ------------------------------*/
void USART1_IRQHandler(void){

}

void USART2_IRQHandler(void){

}

void USART3_IRQHandler(void){

}

void UART4_IRQHandler(void){

}

void UART5_IRQHandler(void){

}



/* ------------------------------
 *    Timer
 * ------------------------------*/
void TMR2_GLOBAL_IRQHandler(void){
  isr_at32f415_tmr2();
}

void TMR3_GLOBAL_IRQHandler(void){
  isr_at32f415_tmr3();
}

void TMR4_GLOBAL_IRQHandler(void){
  isr_at32f415_tmr4();
}

void TMR5_GLOBAL_IRQHandler(void){
  isr_at32f415_tmr5();
}

void TMR1_BRK_TMR9_IRQHandler(void){
  isr_at32f415_tmr9();
}

void TMR1_OV_TMR10_IRQHandler(void){
  isr_at32f415_tmr10();
}

void TMR1_TRG_COM_TMR11_IRQHandler(void){
  isr_at32f415_tmr11();
}



/* ------------------------------
 *    Ioint
 * ------------------------------*/
void EXTI0_IRQHandler(void){

}

void EXTI1_IRQHandler(void){

}

void EXTI2_IRQHandler(void){

}

void EXTI3_IRQHandler(void){

}

void EXTI4_IRQHandler(void){

}

void EXTI9_5_IRQHandler(void){
	for(;;){
		if(EXTI->PND & 0x00000020)
      __NOP();
		
		else if(EXTI->PND & 0x00000040)
			__NOP();
		
		else if(EXTI->PND & 0x00000080)
			__NOP();
		
		else if(EXTI->PND & 0x00000100)
			__NOP();
		
		else if(EXTI->PND & 0x00000200)
			__NOP();
		
		else
			break;
	}
}

void EXTI15_10_IRQHandler(void){
	for(;;){
		if(EXTI->PND & 0x00000400)
			__NOP();
		
		else if(EXTI->PND & 0x00000800)
			__NOP();
		
		else if(EXTI->PND & 0x00001000)
			__NOP();
		
		else if(EXTI->PND & 0x00002000)
			__NOP();
		
		else if(EXTI->PND & 0x00004000)
			__NOP();
		
		else if(EXTI->PND & 0x00008000)
			__NOP();
		
		else
			break;
	}
}



/* *****************************************************************************************
 *    End of file
 */
