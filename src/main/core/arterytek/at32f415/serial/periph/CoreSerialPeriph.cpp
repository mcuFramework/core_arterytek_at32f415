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
#include "bsp_arterytek_at32f415.h"
#include "mcuf.h"

//-----------------------------------------------------------------------------------------
#include "core/arterytek/at32f415/serial/periph/CoreSerialPeriph.h"
#include "core/arterytek/at32f415/serial/periph/CoreSerialPeriphPacket.h"
#include "core/arterytek/at32f415/Core.h"
#include "core/arterytek/at32f415/CoreInterrupt.h"

/* ****************************************************************************************
 * Macro
 */
#define REGNUMB                  (static_cast<char>(this->mRegister))
#define CONFIG                   (config[REGNUMB])
#define BASE                     ((spi_type*)CONFIG.Register)

/* ****************************************************************************************
 * Using
 */
using namespace mcuf::hal::serial::periph;
using namespace core::arterytek::at32f415::serial::periph;

//-----------------------------------------------------------------------------------------
using mcuf::io::ByteBuffer;
using mcuf::lang::System;

/* ****************************************************************************************
 * Namesapce
 */
namespace core{
  namespace arterytek{
    namespace at32f415{
      namespace serial{
        namespace periph{
          
          struct Config{
            spi_type* Register;
            crm_periph_clock_type crmClock;
            CoreInterrupt::Irq irq;
            
          }const config[2] = {
            {SPI1 , CRM_SPI1_PERIPH_CLOCK , CoreInterrupt::IRQ_SPI1 },
            {SPI2 , CRM_SPI2_PERIPH_CLOCK , CoreInterrupt::IRQ_SPI2 },
          };
          
          /**
           * @brief 
           * 
           * @param byteBuffer 
           * @return CoreSerialPeriphPacket 
           */
          static CoreSerialPeriphPacket handlePacket(ByteBuffer* byteBuffer){
            CoreSerialPeriphPacket result;
            result.byteBuffer = byteBuffer;
            result.count = 0;
            
            if(byteBuffer == nullptr){
              result.ptr = nullptr;
              result.length = 0;
            }else{
              result.ptr = static_cast<uint8_t*>(byteBuffer->pointer(byteBuffer->position()));
              result.length = byteBuffer->remaining();
              if(result.length == 0)
                result.ptr = nullptr;
            }
            
            return result;
          }
          
        }
      }
    }
  }
}

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Serial Periph object
 * 
 * @param reg 
 */
CoreSerialPeriph::CoreSerialPeriph(core::arterytek::at32f415::serial::periph::CoreSerialPeriphReg reg){
  this->mRegister = reg;
  this->mTransfer.byteBuffer = nullptr;
  this->mReceiver.byteBuffer = nullptr;
}

/**
 * @brief Destroy the Core Serial Periph object
 * 
 */
CoreSerialPeriph::~CoreSerialPeriph(void){
  this->deinit();
}


/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mcuf::function::Runnable
 */

/**
 * @brief 
 * 
 */
void CoreSerialPeriph::run(void){
  ByteBuffer* transfer = this->mTransfer.byteBuffer;
  ByteBuffer* receiver = this->mReceiver.byteBuffer;
  SerialPeriphEvent* event = this->mEvent;
  SerialPeriphStatus status = this->mStatus;
  
  if(transfer)
    transfer->pointer(transfer->position() + this->mTransfer.count);
  
  if(receiver)
    receiver->pointer(receiver->position() + this->mReceiver.count);
  
  this->mTransfer.byteBuffer = nullptr;
  this->mReceiver.byteBuffer = nullptr;
  
  if(event)
    event->onSerialPeriphEvent(status, transfer, receiver);
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::InterruptEvent
 */

/**
 * @brief 
 * 
 */
void CoreSerialPeriph::interruptEvent(void){
  spi_type* base = BASE;
  if(base->sts_bit.tdbe){
    if(this->mTransfer.count >= this->mTransfer.length){ //transfe successful
      if(base->ctrl2_bit.rdbfie)
        base->dt = 0xFFFF;

      else{
        base->ctrl2_bit.tdbeie = false;
        base->ctrl1_bit.spien = false;
        if(!System::execute(*this))
          this->run();
        
      }

    }else{
      if(this->mTransfer.ptr)
        base->dt = this->mTransfer.ptr[this->mTransfer.count];

      else
        base->dt = 0xFFFF;

      ++this->mTransfer.count;
    }
  }

  if(base->sts_bit.rdbf){
    uint16_t receiver = base->dt;

    if(this->mReceiver.ptr) // rxData is exist
      this->mReceiver.ptr[this->mReceiver.count] = receiver;

    ++this->mReceiver.count;

    if(this->mReceiver.count >= this->mReceiver.length){
      base->ctrl2_bit.rdbfie = false;
      
      if(this->mTransfer.count >= this->mTransfer.length){
        base->ctrl2_bit.tdbeie = false;
        base->ctrl1_bit.spien = false;
        if(!System::execute(*this))
          this->run();
      }
      
    }
  }
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::serial::periph::SerialPeriph
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
bool CoreSerialPeriph::deinit(void){
  if(!this->isInit())
    return false;
  
  this->abort();
  Core::interrupt.irqEnable(CONFIG.irq, false);
  crm_periph_clock_enable(CONFIG.crmClock, FALSE);
  Core::interrupt.setHandler(CONFIG.irq, nullptr);
  return true;              
}

/**
 * @brief initialze hardware;
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPeriph::init(void){
  if(this->isInit())
    return false;
  
  crm_periph_clock_enable(CONFIG.crmClock, TRUE);
  spi_init_type spi_init_struct;

  spi_default_para_init(&spi_init_struct);
  spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
  spi_init_struct.master_slave_mode =SPI_MODE_MASTER;
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_8;
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
  spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
  spi_init(SPI1, &spi_init_struct);

  Core::interrupt.setHandler(CONFIG.irq, this);
  
  return true;              
}

/**
 * @brief get hardware initialzed status.
 * 
 * @return true not init
 * @return false initd
 */
bool CoreSerialPeriph::isInit(void){
  return CRM_REG(CONFIG.crmClock) & CRM_REG_BIT(CONFIG.crmClock);
}

/* ****************************************************************************************
 * Public Method <Override> - mcuf::hal::serial::periph::SerialPeriphTransfer
 */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CoreSerialPeriph::abort(void){
  if(!this->isBusy())
    return false;

  BASE->ctrl1_bit.spien = false;
  BASE->ctrl2_bit.rdbfie = false;
  BASE->ctrl2_bit.tdbeie = false;
  
  this->run();
  
  return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */

bool CoreSerialPeriph::isBusy(void){
  if(this->mTransfer.byteBuffer != nullptr)
    return true;
  
  if(this->mReceiver.byteBuffer != nullptr)
    return true;
  
  return false;
}

/**
 * @brief 
 * 
 * @param chipSelect 
 * @param packet 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreSerialPeriph::transfer(uint32_t chipSelect, 
                                SerialPeriphPacket* packet,
                                SerialPeriphEvent* event){

  if(packet==nullptr){
    if(event != nullptr)
      event->onSerialPeriphEvent(SerialPeriphStatus::FAIL, nullptr, nullptr);
    
    return false;
  }
  
  if(this->isBusy()){
    if(event != nullptr)
      event->onSerialPeriphEvent(SerialPeriphStatus::FAIL, packet->tx, packet->rx);
    
    return false;
  }
  
  if(packet->tx == nullptr){
    if(event != nullptr)
      event->onSerialPeriphEvent(SerialPeriphStatus::FAIL, packet->tx, packet->rx);
    
    return false;
  }
  
  if(packet->rx != nullptr){
    if(packet->rx->isReadOnly())
      event->onSerialPeriphEvent(SerialPeriphStatus::FAIL, packet->tx, packet->rx);
    
    return false;
  }
  
  this->mEvent = event;
  this->mTransfer = handlePacket(packet->tx);
  this->mTransfer = handlePacket(packet->rx);
  this->mStatus = SerialPeriphStatus::SUCCESSFUL;
  
  if(packet->significantBit == SerialPeriphSignificantBit::LSB){
    BASE->ctrl1_bit.slben = true;
  }else{
    BASE->ctrl1_bit.slben = false;
  }

  if(packet->polarity == SerialPeriphPolarity::ACTIVE_HIGH){
    BASE->ctrl1_bit.clkpol = true;
  }else{
    BASE->ctrl1_bit.clkpol = false;
  }

  if(packet->phase == SerialPeriphPhase::SECOND_EDGE){
    BASE->ctrl1_bit.clkpha = true;
  }else{
    BASE->ctrl1_bit.clkpha = false;
  }

	uint32_t clock = (Core::getSystemCoreClock() >> 2);
	clock = clock>>2;
	
	uint8_t div = 0;
	for(uint8_t i=0; i<10; i++){
		
		div = i;
		if(packet->clock >= clock){
			div -= 1;
			break;
		}
		clock = clock >> 1;
	}

  BASE->ctrl2_bit.mdiv_h = div;

  BASE->ctrl1_bit.spien = true;
  
  if(this->mReceiver.ptr)
    BASE->ctrl2_bit.rdbfie = true;
  
  BASE->ctrl2_bit.tdbeie = true;
  
  return true;
}
                      
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
