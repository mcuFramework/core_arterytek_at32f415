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
#include "mcuf/package-info.h" 
#include "../bsp/package-info.h"  

//-----------------------------------------------------------------------------------------
#include "./Core.h"

/* ****************************************************************************************
 * Using
 */  
using namespace core;

//-----------------------------------------------------------------------------------------

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

/**
 *
 */
Core::Core(void){
  return;
}

/**
 *
 */
Core::~Core(void){
  return;
}
 
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
  if((mhz > 256) || (mhz < 16))
    return false;
  
  if(mhz & 0x00000003)
    return false;
  
 /* config flash psr register */
  if(mhz <= 128)
    flash_psr_set(((mhz-1) >> 5));
  
  else
    flash_psr_set(FLASH_WAIT_CYCLE_4);

  /* reset crm */
  crm_reset();

  /* enable hick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);

   /* wait till hick is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) != SET);

  /* config pll clock resource */
  if(mhz <= 60)
    crm_pll_config(CRM_PLL_SOURCE_HICK, static_cast<crm_pll_mult_type>((mhz >> 2) - 2));
  
  else
    crm_pll_config(CRM_PLL_SOURCE_HICK, static_cast<crm_pll_mult_type>((mhz >> 2) - 1));

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET);

  if(mhz <= 150){
    crm_ahb_div_set(CRM_AHB_DIV_1);

    if(mhz <= 75){
      crm_apb2_div_set(CRM_APB2_DIV_1);
      crm_apb1_div_set(CRM_APB1_DIV_1);
    }else{
      crm_apb2_div_set(CRM_APB2_DIV_2);
      crm_apb1_div_set(CRM_APB1_DIV_2);
    }
  }else{
    crm_ahb_div_set(CRM_AHB_DIV_2);
    crm_apb2_div_set(CRM_APB2_DIV_2);
    crm_apb1_div_set(CRM_APB1_DIV_2);
  }

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL); 

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL);

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* config usbclk from hick48 */
  crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);

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
