/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef CORE_ARTERYTEK_AT32F415_BD2A9420_72E7_485B_886F_F8FEF77E69C0
#define CORE_ARTERYTEK_AT32F415_BD2A9420_72E7_485B_886F_F8FEF77E69C0

/* ****************************************************************************************
 * Include
 */  
#include "mcuf.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace arterytek{
    namespace at32f415{
      class CoreAFIO;
    }
  }
}

/* ****************************************************************************************
 * Class Object
 */  
class core::arterytek::at32f415::CoreAFIO extends mcuf::lang::Object
      implements mcuf::hal::Base{
  
  /* **************************************************************************************
   * Enum MapCAN  <MAP6 - [0-3]>
   */        
  public: enum MapCAN{
    CAN_PA11_PA12 = 0x00000000,
    CAN_PB8_PB9   = 0x00000002,
    CAN_MASK      = 0x0000000F
  };
  
  /* **************************************************************************************
   * Enum MapCOMP <MAP2 - [26-27]>
   */     
  public: enum MapCOMP{
    COMP_PA0_PA2    = 0x00000000,
    COMP_PA6_PA7    = 0x04000000,
    COMP_PA11_PA12  = 0x08000000,
    COMP_MASK       = 0x0C000000
  };
  
  /* **************************************************************************************
   * Enum MapDEBUG  <MAP7 - [16-18]>
   */
  public: enum MapDEBUG{
    DEBUG_FULL        = 0x00000000,
    DEBUG_NOJNTRST    = 0x00010000,
    DEBUG_JTAGDISABLE = 0x00020000,
    DEBUG_ALLDISABLE  = 0x00040000,
    DEBUG_MASK        = 0x00070000,
  };
  
  /* **************************************************************************************
   * Enum MapEXTI
   */
  public: enum MapEXTI{
    EXTI_PA   = 0x00000000,
    EXTI_PB   = 0x00000001,
    EXTI_PC   = 0x00000002,
    EXTI_PD   = 0x00000003,
    EXTI_PF   = 0x00000005,
    EXTI_MASK = 0x0000000F
  };
  
  /* **************************************************************************************
   * Enum MapI2C1 <MAP5 - [4-7]>
   */
  public: enum MapI2C1{
    I2C1_PB6_PB7_PB5 = 0x00000000,
    I2C1_PB8_PB9_PB5 = 0x00000010,
    I2C1_PF6_PF7_PB5 = 0x00000020,
    I2C1_MASK        = 0x000000F0, 
  };
  
  /* **************************************************************************************
   * Enum MapI2C2 <MAP5 - [8-11]>
   */  
  public: enum MapI2C2{
    I2C2_PB10_PB11_PB12 = 0x00000000,
    I2C2_PA8_PC9_PA9    = 0x00000100,
    I2C2_PA8_PB4_PA9    = 0x00000200,
    I2C2_PF6_PF7_PA9    = 0x00000300,
    I2C2_MASK           = 0x00000F00,
  };
  
  /* **************************************************************************************
   * Enum MapSDIO <MAP6 - [8-11]>
   */  
  public: enum MapSDIO{
    SDIO_PC8_PC9_PC10_PC11_PB8_PB9_PC6_PC7_PC12_PD2 = 0x00000000,
    SDIO_PC0_PC1_PC2_PC3_PA4_PA5_PA6_PA7_PC4_PC5    = 0x00000400,
    SDIO_PA4_PA5_PA6_PA7_NC_NC_NC_NC_PC4_PC5        = 0x00000500,
    SDIO_PC0_PC1_PC2_PC3_PA4_PA5_PA6_PA7_PA2_PA3    = 0x00000600,
    SDIO_PA4_PA5_PA6_PA7_NC_NC_NC_NC_PA2_PA3        = 0x00000700,
    SDIO_MASK                                       = 0x00000F00,
  };
  
  /* **************************************************************************************
   * Enum MapSPI1 <MAP5 - [16-19]>
   */
  public: enum MapSPI1{         
    SPI1_PA4_PA5_PA6_PA7_PB0  = 0x00000000,
    SPI1_PA15_PB3_PB4_PB5_PB6 = 0x00010000,
    SPI1_MASK                 = 0x000F0000, 
  };
  
  /* **************************************************************************************
   * Enum MapSPI2 <MAP5 - [20-23]>
   */
  public: enum MapSPI2{
    SPI2_PB12_PB13_PB14_PB15_PC6  = 0x00000000,
    SPI2_PA15_PB3_PB4_PB5_PC7     = 0x00100000,
    SPI2_MASK                     = 0x00F00000, 
  };
  
  /* **************************************************************************************
   * Enum MapUSART1 <MAP6 - [16-19]>
   */
  public: enum MapUSART1{
    USART1_PA9_PA10 = 0x00000000,
    USART1_PB6_PB7  = 0x00010000,
    USART1_MASK     = 0x000F0000,
  };  
  
  /* **************************************************************************************
   * Enum MapUSART3 <MAP6 - [24-27]>
   */
  public: enum MapUSART3{
    USART3_PB10_PB11_PB12_PB13_PB14 = 0x00000000,
    USART3_PC10_PC11_PC12_PB13_PB14 = 0x01000000,
    USART3_PA7_PA6_PA5_PB1_PB0      = 0x02000000,
    USART3_MASK                     = 0x0F000000
  };
  
  /* **************************************************************************************
   * Enum MapUART4  <MAP6 - [28-31]>
   */
  public: enum MapUART4{
    UART4_PC10_PC11 = 0x00000000,
    UART4_PF4_PF5   = 0x10000000,
    UART4_MASK      = 0xF0000000
  };
        
  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */

  /**
   * Construct.
   */
  public: CoreAFIO(void) = default;

  /**
   * Disconstruct.
   */
  public: virtual ~CoreAFIO(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
   */

  /**
   * uninitialze hardware.
   */
  public: virtual bool deinit(void) override; 

  /**
   * initialze hardware;
   */
  public: virtual bool init(void) override;
  
  /**
   * get hardware initialzed status.
   * 
   * @return false = not init, true = initd
   */
  public: virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method
   */
   
  /**
   *
   */
  public: void remapCAN(MapCAN map);
  
  /**
   *
   */
  public: void remapCOMP(MapCOMP map);
  
  /**
   *
   */
  public: void remapDEBUG(MapDEBUG map);
  
  /**
   *
   */
  public: void remapEXTI(MapEXTI map, uint8_t pin);
  
  /**
   *
   */
  public: void remapI2C1(MapI2C1 map);
  
  /**
   *
   */
  public: void remapI2C2(MapI2C2 map);
  
  /**
   *
   */
  public: void remapSDIO(MapSDIO map);
  
  /**
   *
   */
  public: void remapSPI1(MapSPI1 map);
  
  /**
   *
   */
  public: void remapSPI2(MapSPI2 map);
  
  /**
   *
   */
  public: void remapUSART1(MapUSART1 map);
  
  /**
   *
   */
  public: void remapUSART3(MapUSART3 map);
  
  /**
   *
   */
  public: void remapUART4(MapUART4 map);
  
  /* **************************************************************************************
   * Protected Method <Static>
   */

  /* **************************************************************************************
   * Protected Method <Override>
   */

  /* **************************************************************************************
   * Protected Method
   */

  /* **************************************************************************************
   * Private Method <Static>
   */

  /* **************************************************************************************
   * Private Method <Override>
   */
   
  /* **************************************************************************************
   * Private Method
   */  
  private: void remap(volatile uint32_t* reg, uint32_t mask, uint32_t value);

};



/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_BD2A9420_72E7_485B_886F_F8FEF77E69C0 */
