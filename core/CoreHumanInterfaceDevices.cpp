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

//-----------------------------------------------------------------------------------------
#include "./CoreHumanInterfaceDevices.h"
#include "./Core.h"
#include "./CoreInterrupt.h"
#include "../bsp/middlewares/usb_conf.h"
#include "../bsp/middlewares/usb_core.h"
#include "../bsp/middlewares/usbd_int.h"
#include "../bsp/middlewares/custom_hid_class.h"
#include "../bsp/middlewares/custom_hid_desc.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using core::CoreHumanInterfaceDevices;
using core::Core;
using core::CoreInterrupt;
using mcuf::Memory;
using mcuf::OutputBuffer;
using mcuf::OutputBuffer;
using mcuf::CompletionHandler;
using mcuf::Future;

static CoreHumanInterfaceDevices* arterytek_at32f415_usb_coreHumanInterfaceDevices;
static otg_core_type arterytek_at32f415_usb_coreHumanInterfaceDevices_mPudev;

extern "C" void arterytek_at32f415_usb_CoreHumanInterfaceDevices_onTransfer(void){
  arterytek_at32f415_usb_coreHumanInterfaceDevices->onTransfer();
}

extern "C" void arterytek_at32f415_usb_CoreHumanInterfaceDevices_onReceiver(void *udev, uint8_t *report, uint16_t len){
  arterytek_at32f415_usb_coreHumanInterfaceDevices->onReceiver(udev, report, len);
}

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Human Interface Devices object
 * 
 * @param buffer 
 * @param bufferSize 
 */
CoreHumanInterfaceDevices::CoreHumanInterfaceDevices(void* buffer, uint32_t bufferSize) : RingBufferInputStream(buffer, bufferSize){
  return;
}
  
/**
 * @brief Construct a new Core Human Interface Devices object
 * 
 * @param memory 
 */
CoreHumanInterfaceDevices::CoreHumanInterfaceDevices(const Memory& memory) : RingBufferInputStream(memory){
  return;
}

/**
 * @brief Construct a new Core Human Interface Devices object
 * 
 * @param length 
 */
CoreHumanInterfaceDevices::CoreHumanInterfaceDevices(uint32_t length) : RingBufferInputStream(length){
  return;
}

/**
 * @brief Destroy the Core Human Interface Devices object
 * 
 */
CoreHumanInterfaceDevices::~CoreHumanInterfaceDevices(void){
  return;  
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::Base
 */

/**
 * @brief uninitialze hardware.
 * 
 * @return true 
 * @return false 
 */
bool CoreHumanInterfaceDevices::deinit(void){
  return false;
}

/**
 * @brief initialze hardware;
 * 
 * @return true 
 * @return false 
 */
bool CoreHumanInterfaceDevices::init(void){
  if(this->isInit())
    return false;
  
  this->mOutputBuffer = nullptr;
  arterytek_at32f415_usb_coreHumanInterfaceDevices = this;
  crm_periph_clock_enable(CRM_OTGFS1_PERIPH_CLOCK, TRUE);
  Core::interrupt.setHandler(CoreInterrupt::IRQ_OTGFS, this);
  Core::interrupt.irqEnable(CoreInterrupt::IRQ_OTGFS, true);

  if(true){
    gpio_init_type gpio_init_struct;

    crm_periph_clock_enable(OTG_PIN_GPIO_CLOCK, TRUE);
    gpio_default_para_init(&gpio_init_struct);

    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = OTG_PIN_VBUS;
    gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init(OTG_PIN_GPIO, &gpio_init_struct);
  }
 
  
  usbd_init(&arterytek_at32f415_usb_coreHumanInterfaceDevices_mPudev,
            USB_FULL_SPEED_CORE_ID,
            USB_ID,
            &custom_hid_class_handler,
            &custom_hid_desc_handler);  
  
  return true;
}

/**
 * @brief get hardware initialzed status.
 * 
 * @return true not init
 * @return false initd
 */
bool CoreHumanInterfaceDevices::isInit(void){
  return CRM_REG(CRM_OTGFS1_PERIPH_CLOCK) & CRM_REG_BIT(CRM_OTGFS1_PERIPH_CLOCK);
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreHumanInterfaceDevices::interruptEvent(void){
  usbd_irq_handler(&arterytek_at32f415_usb_coreHumanInterfaceDevices_mPudev);
  return;
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::OutputStream
 */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreHumanInterfaceDevices::abortWrite(void){
  return false;
}

/**
 * @brief 
 * 
 * @return true is busy.
 * @return false isn't busy.
 */
bool CoreHumanInterfaceDevices::writeBusy(void){
  return (this->mOutputBuffer != nullptr);
}

/**
 * @brief 
 * 
 * @param outputBuffer
 * @param future 
 * @return true 
 * @return false 
 */
bool CoreHumanInterfaceDevices::write(OutputBuffer& outputBuffer, int timeout){
  Future future = Future();
  if(this->write(outputBuffer, future) == false)
    return false;
  
  future.waitDone(timeout);
  if(future.isDone() == false)
    this->abortWrite();
  
  future.waitDone();
  return true;
}

/**
 * @brief 
 * 
 * @param outputBuffer
 * @param attachment 
 * @param handler 
 * @return true successful.
 * @return false fail.
 */
bool CoreHumanInterfaceDevices::write(OutputBuffer& outputBuffer, void* attachment, CompletionHandler<int, void*>* handler){
  if(this->writeBusy())
    return false;
  
  if(outputBuffer.avariable()<= 0)
    return false;
  
  this->mOutputBuffer = &outputBuffer;
  this->mHandler = handler;
  this->mAttachment = attachment;
  this->mResult = 0;
  
  this->writePacket();

  return true;
}

/**
 * @brief 
 * 
 * @param outputBuffer
 * @param future 
 * @return true 
 * @return false 
 */
bool CoreHumanInterfaceDevices::write(OutputBuffer& outputBuffer, mcuf::Future& future){
  if(!future.isIdle())
    return false;
  
  future.setWait();
  bool result = this->write(outputBuffer, nullptr, &future);
  if(result == false)
    future.clear();

  return result;
}

/* ****************************************************************************************
 * Public Method
 */

/**
 * @brief 
 * 
 */
void CoreHumanInterfaceDevices::onTransfer(void){
  if(this->mOutputBuffer == nullptr)
    return;
  
  if(this->mOutputBuffer->avariable() <= 0){
    this->executeCompletionHandler();
  }else{
    this->writePacket();
  }
  return;
}
  
/**
 * @brief 
 * 
 * @param data 
 */
void CoreHumanInterfaceDevices::onReceiver(void *udev, uint8_t *report, uint16_t len){
  usbd_core_type *pudev = (usbd_core_type *)udev;
  custom_hid_type *pcshid = (custom_hid_type *)pudev->class_handler->pdata;
  
  if(report[0] == HID_REPORT_ID_6){
    if(report[1] > (len-2))
      return;
    
    this->put(&report[2], report[1]);
  }
  
  return;
}

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

/**
 * @brief 
 *
 */
void CoreHumanInterfaceDevices::executeCompletionHandler(void){
  if(!this->writeBusy())
    return;
  
  CompletionHandler<int, void*>* handler = this->mHandler;
  void* attachment = this->mAttachment;
  
  int result = this->mResult;
  this->mResult = 0;
  this->mOutputBuffer = nullptr;
  
  if(handler)
    handler->completed(result, attachment);

  return;
}

/**
 * @brief 
 * 
 */
void CoreHumanInterfaceDevices::writePacket(void){
  usbd_core_type *pudev = &arterytek_at32f415_usb_coreHumanInterfaceDevices_mPudev.dev;
  custom_hid_type *pcshid = (custom_hid_type *)pudev->class_handler->pdata;
  
  int len = this->mOutputBuffer->get(&pcshid->g_txhid_buff[2], 62);
  pcshid->g_txhid_buff[0] = 0xf0;
  pcshid->g_txhid_buff[1] = len;
  this->mResult += len;
  usbd_ept_send(pudev, USBD_CUSTOM_HID_IN_EPT, pcshid->g_txhid_buff, 64);
  
  return;
}

/* ****************************************************************************************
 * End of file
 */
