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

namespace arterytek{
  namespace at32f415{
    class CoreIomux;
  }
}


/* ****************************************************************************************
 * Class Object
 */  
class arterytek::at32f415::CoreIomux extends mcuf::lang::Object
      implements hal::Base{
  
  /* **************************************************************************************
   * Enum MapCAN  <MAP6[10] - [0-3]> 
   */        
  public: 
    enum struct MapCAN : uint32_t{
      PA11_PA12 = 0x00000000,
      PB8_PB9   = 0x00000002,
      MASK      = 0x0000000F
    };
  
  /* **************************************************************************************
   * Enum MapCOMP <MAP2[6] - [26-27]>
   */     
  public: 
    enum struct MapCOMP : uint32_t{
      PA0_PA2    = 0x00000000,
      PA6_PA7    = 0x04000000,
      PA11_PA12  = 0x08000000,
      MASK       = 0x0C000000
    };
  
  /* **************************************************************************************
   * Enum MapSWDIO  <MAP7[11] - [16-18]>
   */
  public: 
    enum struct MapSWDIO : uint32_t{
      FULL        = 0x00000000,
      NOJNTRST    = 0x00010000,
      JTAGDISABLE = 0x00020000,
      ALLDISABLE  = 0x00040000,
      MASK        = 0x00070000
    };
  
  /* **************************************************************************************
   * Enum MapEXTI
   */
  public: 
    enum struct MapEXTI : uint32_t{
      PORTA   = 0x00000000,
      PORTB   = 0x00000001,
      PORTC   = 0x00000002,
      PORTD   = 0x00000003,
      PORTF   = 0x00000005,
      MASK    = 0x0000000F
    };
  
  /* **************************************************************************************
   * Enum MapI2C1 <MAP5[9] - [4-7]>
   */
  public: 
    enum struct MapI2C1 : uint32_t{
      PB6_PB7_PB5 = 0x00000000,
      PB8_PB9_PB5 = 0x00000010,
      PF6_PF7_PB5 = 0x00000020,
      MASK        = 0x000000F0
    };
  
  /* **************************************************************************************
   * Enum MapI2C2 <MAP5[9] - [8-11]>
   */  
  public: 
    enum struct MapI2C2 : uint32_t{
      PB10_PB11_PB12 = 0x00000000,
      PA08_PC09_PA09 = 0x00000100,
      PA08_PB04_PA09 = 0x00000200,
      PF06_PF07_PA09 = 0x00000300,
      MASK           = 0x00000F00
    };
  
  /* **************************************************************************************
   * Enum MapSDIO <MAP6[10] - [8-11]>
   */  
  public: 
    enum struct MapSDIO : uint32_t{
      PC08_PC09_PC10_PC11_PB08_PB09_PC06_PC07_PC12_PD02 = 0x00000000,
      PC00_PC01_PC02_PC03_PA04_PA05_PA06_PA07_PC04_PC05 = 0x00000400,
      PA04_PA05_PA06_PA07_NC___NC___NC___NC___PC04_PC05 = 0x00000500,
      PC00_PC01_PC02_PC03_PA04_PA05_PA06_PA07_PA02_PA03 = 0x00000600,
      PA04_PA05_PA06_PA07_NC___NC___NC___NC___PA02_PA03 = 0x00000700,
      MASK                                              = 0x00000F00
    };
  
  /* **************************************************************************************
   * Enum MapSPI1 <MAP5[9] - [16-19]>
   */
  public:
    enum struct MapSPI1 : uint32_t{         
      PA04_PA05_PA06_PA07_PB00 = 0x00000000,
      PA15_PB03_PB04_PB05_PB06 = 0x00010000,
      MASK                     = 0x000F0000
    };
  
  /* **************************************************************************************
   * Enum MapSPI2 <MAP5[9] - [20-23]>
   */
  public: 
    enum struct MapSPI2 : uint32_t{
      PB12_PB13_PB14_PB15_PC06 = 0x00000000,
      PA15_PB03_PB04_PB05_PC07 = 0x00100000,
      MASK                     = 0x00F00000
    };
  
  /* **************************************************************************************
   * Enum MapUSART1 <MAP6[10] - [16-19]>
   */
  public: 
    enum struct MapUSART1 : uint32_t{
      PA09_PA10 = 0x00000000,
      PB06_PB07 = 0x00010000,
      MASK      = 0x000F0000
    };  
  
  /* **************************************************************************************
   * Enum MapUSART3 <MAP6[10] - [24-27]>
   */
  public: 
    enum struct MapUSART3 : uint32_t{
      PB10_PB11_PB12_PB13_PB14 = 0x00000000,
      PC10_PC11_PC12_PB13_PB14 = 0x01000000,
      PA07_PA06_PA05_PB01_PB00 = 0x02000000,
      MASK                     = 0x0F000000
    };
  
  /* **************************************************************************************
   * Enum MapUART4  <MAP6[10] - [28-31]>
   */
  public: 
    enum struct MapUART4 : uint32_t{
      PC10_PC11 = 0x00000000,
      PF04_PF05 = 0x10000000,
      MASK      = 0xF0000000
    };
    
  /* **************************************************************************************
   * Enum MapTmr1  <MAP4[8] - [0-3]>
   */
  public:
    enum struct MapTMR1 : uint32_t{
      PA12_PA08_PA09_PA10_PA11_PB12_PB13_PB14_PB15 = 0x00000000,
      PA12_PA08_PA09_PA10_PA11_PA06_PA07_PB00_PB01 = 0x00000001,
      PA00_PC06_PC07_PC08_PC09_PA06_PA07_PB00_PB01 = 0x00000002,
      MASK                                         = 0x0000000F
    };
    
  /* **************************************************************************************
   * Enum MapTmr2  <MAP4[8] - [4-6]>
   */
  public:
    enum struct MapTMR2 : uint32_t{
      PA00_PA01_PA02_PA03 = 0x00000000,
      PA15_PB03_PA02_PA03 = 0x00000010,
      PA00_PA01_PB10_PB11 = 0x00000020,
      PA15_PB03_PB10_PB11 = 0x00000030,
      MASK                = 0x00000070
    };    
    
  /* **************************************************************************************
   * Enum MapTmr3  <MAP4[8] - [8-11]>
   */
  public:
    enum struct MapTMR3 : uint32_t{
      PA06_PA07_PB00_PB01 = 0x00000000,
      PB04_PB05_PB00_PB01 = 0x00000200,
      PC06_PC07_PC08_PC09 = 0x00000300,
      MASK                = 0x00000F00
    };
   
  /* **************************************************************************************
   * Enum MapTmr5  <MAP4[8] - [16-18]>
   */
  public:
    enum struct MapTMR5 : uint32_t{
      PA00_PA01_PA02_PA03 = 0x00000000,
      PF04_PF05_PA02_PA03 = 0x00010000,
      MASK                = 0x00070000
    }; 
    
  /* **************************************************************************************
   * Enum MapTmr9  <MAP3[7] - [0-3]>
   */
  public:
    enum struct MapTMR9 : uint32_t{
      PA02_PA03 = 0x00000000,
      PB14_PB15 = 0x00000001,
      MASK      = 0x0000000F
    }; 
    
  /* **************************************************************************************
   * Enum MapTmr10  <MAP3[7] - [4-7]>
   */
  public:
    enum struct MapTMR10 : uint32_t{
      PB8   = 0x00000000,
      PA6   = 0x00000010,
      MASK  = 0x000000F0
    }; 
    
  /* **************************************************************************************
   * Enum MapTmr11  <MAP3[7] - [4-7]>
   */
  public:
    enum struct MapTMR11 : uint32_t{
      PB9   = 0x00000000,
      PA7   = 0x00000100,
      MASK  = 0x00000F00
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
  public: 

    /**
     * @brief Construct a new Core Iomux object
     * 
     */
    CoreIomux(void);

    /**
     * @brief Destroy the Core Iomux object
     * 
     */
    virtual ~CoreIomux(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override>
   */
  public:

    /**
     * @brief uninitialze hardware.
     * 
     * @return true 
     * @return false 
     */
    virtual bool deinit(void) override; 
    
    /**
     * @brief initialze hardware;
     * 
     * @return true 
     * @return false 
     */
    virtual bool init(void) override;
  
    /**
     * @brief get hardware initialzed status.
     * 
     * @return true initd
     * @return false not init
     */
    virtual bool isInit(void) override;

  /* **************************************************************************************
   * Public Method <Inline>
   */
  public:
    
    
    
  /* **************************************************************************************
   * Public Method
   */
  public: 

    /**
     * @brief 
     * 
     * @param enable 
     */
    void enableHEXT(bool enable);

    /**
     * @brief 
     * 
     * @param map 
     * @param pin 
     */
    void remapEXTI(MapEXTI map, uint8_t pin);    
  
    /**
     * @brief 
     * 
     * @param enable 
     */
    void enableSWDIO(bool enable);
  
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapCAN(MapCAN map);
  
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapCOMP(MapCOMP map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapSWDIO(MapSWDIO map);
  
  
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapI2C1(MapI2C1 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapI2C2(MapI2C2 map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapSDIO(MapSDIO map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapSPI1(MapSPI1 map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapSPI2(MapSPI2 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR1(MapTMR1 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR2(MapTMR2 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR3(MapTMR3 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR5(MapTMR5 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR9(MapTMR9 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR10(MapTMR10 map);
    
    /**
     * @brief 
     * 
     * @param map 
     */
    void remapTMR11(MapTMR11 map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapUSART1(MapUSART1 map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapUSART3(MapUSART3 map);

    /**
     * @brief 
     * 
     * @param map 
     */
    void remapUART4(MapUART4 map);
  
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
