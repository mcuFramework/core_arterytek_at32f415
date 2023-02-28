/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_843A68D6_19B5_424F_BC46_EF6C0CEF95B8
#define CORE_ARTERYTEK_AT32F415_843A68D6_19B5_424F_BC46_EF6C0CEF95B8

/* ****************************************************************************************
 * Include folder
 */

/* ****************************************************************************************
 * Include
 */
#include "./Core.h"
#include "./CoreAnalogInputPin.h"
#include "./CoreAnalogInputPort.h"
#include "./CoreEdgeTrigger.h"
#include "./CoreEdgeTriggerReg.h"
#include "./CoreFlashStorage.h"
#include "./CoreGeneralPin.h"
#include "./CoreGeneralPort.h"
#include "./CoreGeneralPortReg.h"
#include "./CoreHumanInterfaceDevices.h"
#include "./CoreInterrupt.h"
#include "./CoreIomux.h"
#include "./CorePulseWidthPin.h"
#include "./CorePulseWidthPort.h"
#include "./CorePulseWidthPortSoft.h"
#include "./CorePulseWidthReg.h"
#include "./CoreSerialBus.h"
#include "./CoreSerialBusConfig.h"
#include "./CoreSerialBusErrorCode.h"
#include "./CoreSerialBusErrorEvent.h"
#include "./CoreSerialBusReg.h"
#include "./CoreSerialBusSlave.h"
#include "./CoreSerialBusSlaveErrorEvent.h"
#include "./CoreSerialPeriph.h"
#include "./CoreSerialPeriphConfig.h"
#include "./CoreSerialPeriphPacket.h"
#include "./CoreSerialPeriphReg.h"
#include "./CoreSerialPort.h"
#include "./CoreSerialPortConfig.h"
#include "./CoreSerialPortReg.h"
#include "./CoreTimer.h"
#include "./CoreTimerReg.h"
#include "./InputMode.h"
#include "./OutputMode.h"

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

#endif /* CORE_ARTERYTEK_AT32F415_843A68D6_19B5_424F_BC46_EF6C0CEF95B8 */
