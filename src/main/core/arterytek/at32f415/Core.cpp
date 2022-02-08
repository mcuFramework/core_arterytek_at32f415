/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "bsp_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/Core.h"

/* ****************************************************************************************
 * Using
 */  
using namespace core::arterytek::at32f415::general::port;

//-----------------------------------------------------------------------------------------
using core::arterytek::at32f415::Core;
using core::arterytek::at32f415::CoreIomux;
using core::arterytek::at32f415::CoreInterrupt;



/* ****************************************************************************************
 * Extern
 */ 
extern unsigned int SystemCoreClockHz;
extern void SystemCoreClockUpdate(void);

/* ****************************************************************************************
 * Variable <Static>
 */

CoreInterrupt Core::interrupt = CoreInterrupt();

CoreIomux Core::iomux = CoreIomux();

CoreGeneralPort Core::gpioa = CoreGeneralPort(CoreGeneralPortReg::REG_GPIOA);
CoreGeneralPort Core::gpiob = CoreGeneralPort(CoreGeneralPortReg::REG_GPIOB);
CoreGeneralPort Core::gpioc = CoreGeneralPort(CoreGeneralPortReg::REG_GPIOC);
CoreGeneralPort Core::gpiod = CoreGeneralPort(CoreGeneralPortReg::REG_GPIOD);
CoreGeneralPort Core::gpiof = CoreGeneralPort(CoreGeneralPortReg::REG_GPIOF);


/* ****************************************************************************************
 * Construct Method
 */

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/**
 *
 */
uint32_t Core::getSystemCoreClock(void){
  return SystemCoreClockHz;
}

/**
 *
 */
bool Core::setSystemCoreClock(uint32_t mhz){
  if(mhz > 150)
    return false;
  
  if(mhz < 12)
    return false;
  
  if(mhz & 0x00000001)
    return false;
  
  mhz = (mhz >> 1);
  
 /* config flash psr register */
  flash_psr_set(FLASH_WAIT_CYCLE_4); 

  /* reset crm */
  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);

   /* wait till hick is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) != SET);

  /* config pll clock resource */
  crm_pll_config2(CRM_PLL_SOURCE_HICK, mhz, 1, CRM_PLL_FR_2);
  //crm_pll_config(CRM_PLL_SOURCE_HICK, CRM_PLL_MULT_18);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET);

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL); 

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL);

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  SystemCoreClockUpdate();
  
  return true;
}


/* ****************************************************************************************
 * Public Method <Override>
 */

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
