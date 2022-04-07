/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_BABF1D6B_FDA4_44DA_994F_DC2EAEF4CEC0
#define CORE_ARTERYTEK_AT32F415_BABF1D6B_FDA4_44DA_994F_DC2EAEF4CEC0

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"

//-----------------------------------------------------------------------------------------
#include "tool/package-info.h"

/* ****************************************************************************************
 * Namespace
 */  
namespace core{
  namespace counter{
    namespace pulse{
      class PulseWidthTest;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class core::counter::pulse::PulseWidthTest extends mcuf::lang::Object implements
  public mcuf::function::Runnable{

  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private:
    mcuf::util::Stacker& mStacker;
    tool::Console* mConsole;
    tool::BoardPeriph* mBoardPeriph;
    arterytek::at32f415::counter::CorePulseWidthPortSoft* mCorePulseWidthPortSoft;
    arterytek::at32f415::counter::CorePulseWidthPort* mCorePulseWidthPort;
  
    hal::general::GeneralPin* mPulseFanOut;
    hal::general::GeneralPin* mPulseMT3608;
  
    hal::general::GeneralPin* mLedPowerR;
    hal::general::GeneralPin* mLedPowerG;
    hal::general::GeneralPin* mLedPowerB;
  
    hal::general::GeneralPin* mLedStatusR;
    hal::general::GeneralPin* mLedStatusG;
    hal::general::GeneralPin* mLedStatusB;
  
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
     *
     */
    PulseWidthTest(mcuf::util::Stacker& stacker);

    /**
     *
     */
    virtual ~PulseWidthTest(void);

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Runnable
   */
  public:
    
    /**
     * @brief 
     * 
     */
    virtual void run(void) override;

  /* **************************************************************************************
   * Public Method
   */

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
  private:
    
    /**
     *
     */
    void init(void);

};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_BABF1D6B_FDA4_44DA_994F_DC2EAEF4CEC0 */
