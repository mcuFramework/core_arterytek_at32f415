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
    core::arterytek::at32f415::counter::pulse::CorePulseWidthPortSoft* mCorePulseWidthPortSoft;
  
    mcuf::hal::general::pin::GeneralPin* mPulseFanOut;
    mcuf::hal::general::pin::GeneralPin* mPulseMT3608;
  
    mcuf::hal::general::pin::GeneralPin* mLedPowerR;
    mcuf::hal::general::pin::GeneralPin* mLedPowerG;
    mcuf::hal::general::pin::GeneralPin* mLedPowerB;
  
    mcuf::hal::general::pin::GeneralPin* mLedStatusR;
    mcuf::hal::general::pin::GeneralPin* mLedStatusG;
    mcuf::hal::general::pin::GeneralPin* mLedStatusB;
  
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
