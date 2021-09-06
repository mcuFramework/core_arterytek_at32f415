/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "core/arterytek/at32f415/core/core_io.h"

/* ****************************************************************************************
 * Extern
 */  

extern void mcuf_at32f415_interrupt_priority(void);


/* ****************************************************************************************
 *	Public function
 */
void lowlevel(void){
  SystemCoreClockUpdate();
	mcuf_at32f415_interrupt_priority();
}

/* ****************************************************************************************
 *	End of file
 */
