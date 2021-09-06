/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include <stdint.h>
#include "core/arterytek/at32f415/bsp/at32f4xx.h"
#include "core/arterytek/at32f415/bsp/core_cm4.h"


/* ****************************************************************************************
 * Extern
 */  
extern void lowlevel(void);
extern void main_cpp(void);


/* ****************************************************************************************
 *	Public function
 */
int main(){
	lowlevel();
	main_cpp();
}

/* ****************************************************************************************
 *	End of file
 */
