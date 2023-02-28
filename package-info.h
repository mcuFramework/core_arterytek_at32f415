/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_D4A9DAB6_F7B9_4BA8_B887_6B8861010455
#define CORE_ARTERYTEK_AT32F415_D4A9DAB6_F7B9_4BA8_B887_6B8861010455

/* ****************************************************************************************
 * Include folder
 */
#include "core/package-info.h"
/* ****************************************************************************************
 * Include
 */

/* ****************************************************************************************
 * Reference
 */

/**
 * Module macro
 */
#include "mcuf/package-info.h"
#ifndef MODULE_VER_MCUF
#error "module macro version not found"
#endif
#define VERSION_STATUS_CACHE VERSION_CHECK(MODULE_VER_MCUF, 0, 1, 0)
#if VERSION_STATUS_CACHE != VERSION_PASS
  #if VERSION_STATUS_CACHE == VERSION_WARN
  	#warning "module macro reversion below request"
  #else
  	#error "module macro miner to low or majer not match"
  #endif
#endif
#undef VERSION_STATUS_CACHE

/* ****************************************************************************************
 * Version
 */
#define MODULE_VER_CORE VERSION_DEFINE(0, 1, 0)

/* ****************************************************************************************
 * End of file
 */

#endif /* CORE_ARTERYTEK_AT32F415_D4A9DAB6_F7B9_4BA8_B887_6B8861010455 */
