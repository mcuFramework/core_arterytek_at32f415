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
#include "arterytek/at32f415/analog/CoreAnalogInputPort.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using arterytek::at32f415::analog::CoreAnalogInputPort;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Analog Input Port:: Core Analog Input Port object
 * 
 */
CoreAnalogInputPort::CoreAnalogInputPort(void){

}

/**
 * @brief Destroy the Core Analog Input Port:: Core Analog Input Port object
 * 
 */
CoreAnalogInputPort::~CoreAnalogInputPort(void){
    this->deinit();
    return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - hal::Base
 */

/**
 *
 */
bool CoreAnalogInputPort::init(void){
  if(true){
    dma_init_type dma_init_struct;
    
    crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
    dma_reset(DMA1_CHANNEL1);
    dma_default_para_init(&dma_init_struct);
    dma_init_struct.buffer_size = 16;
    dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_base_addr = (uint32_t)this->mResult;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_base_addr = (uint32_t)&(ADC1->odt);
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    dma_init_struct.loop_mode_enable = TRUE;
    dma_init(DMA1_CHANNEL1, &dma_init_struct);

    dma_channel_enable(DMA1_CHANNEL1, TRUE);
  }
  
  if(true){
    int i;
    adc_base_config_type adc_base_struct;
    crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
    crm_adc_clock_div_set(CRM_ADC_DIV_6);

    adc_base_default_para_init(&adc_base_struct);
    adc_base_struct.sequence_mode = TRUE;
    adc_base_struct.repeat_mode = TRUE;
    adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
    adc_base_struct.ordinary_channel_length = 16;
    adc_base_config(ADC1, &adc_base_struct);
    
    for(i=0; i<16; ++i){
      adc_ordinary_channel_set(ADC1, (adc_channel_select_type)i, i+1, ADC_SAMPLETIME_239_5);
    }

    adc_ordinary_conversion_trigger_set(ADC1, ADC12_ORDINARY_TRIG_SOFTWARE, TRUE);
    adc_dma_mode_enable(ADC1, TRUE);

    adc_enable(ADC1, TRUE);
    adc_calibration_init(ADC1);
    while(adc_calibration_init_status_get(ADC1));
    adc_calibration_start(ADC1);
    while(adc_calibration_status_get(ADC1));
  }

  adc_ordinary_software_trigger_enable(ADC1, TRUE);
  return true;
}

/**
 *
 */
bool CoreAnalogInputPort::deinit(void){
  if(this->isInit())
    return false;  
  
  crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, FALSE);
  crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, FALSE);
  return true;
}

/**
 *
 */
bool CoreAnalogInputPort::isInit(void){
  return CRM_REG(CRM_ADC1_PERIPH_CLOCK) & CRM_REG_BIT(CRM_ADC1_PERIPH_CLOCK);
}

/* ****************************************************************************************
 * Public Method <Override> - hal::analog::AnalogInputPortControl
 */

/**
 *
 */
uint32_t CoreAnalogInputPort::read(int channel){
  if((channel >= 0) && (channel < 16))
    return this->mResult[channel];
  
  return 0;
}

/**
 *
 */
uint32_t CoreAnalogInputPort::getConvertBit(void){
  return 16;
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
