#ifndef CORE_ARTERYTEK_AT32F415_B318B6BC_65EC_4A53_B95D_9955CF5B1BAC
#define CORE_ARTERYTEK_AT32F415_B318B6BC_65EC_4A53_B95D_9955CF5B1BAC

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"
#include "core_arterytek_at32f415.h"
#include "start/SpeedReader.hpp"

/* ****************************************************************************************
 * Namespace
 */  
namespace start{
  class CommandWriteTask;
}

/* ****************************************************************************************
 * Class Object
 */  
class start::CommandWriteTask extends mcuf::lang::Object
  implements mcuf::function::Consumer<mcuf::io::channel::ByteBuffer&>{

  /* **************************************************************************************
   * Subclass
   */

  /* **************************************************************************************
   * Variable <Public>
   */
  public: bool busy;
  public: uint32_t mData[10];

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
  private: core::arterytek::at32f415::CoreUSART* mUSART;
  public: mcuf::io::channel::ByteBuffer* mByteBuffer;

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
  public: CommandWriteTask(core::arterytek::at32f415::CoreUSART& usart);

  /**
   * Disconstruct.
   */
  public: virtual ~CommandWriteTask(void) = default;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mcuf::function::Consumer<mcuf::io::channel::ByteBuffer&>
   */
  
  /**
   *
   */
  public: virtual void accept(mcuf::io::channel::ByteBuffer& byteBuffer) override;

  /* **************************************************************************************
   * Public Method
   */
   
  /**
   *
   */
  public: bool writeConnect(void);
  
  /**
   *
   */
  public: bool writeData(void);

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

};

/* *****************************************************************************************
 * End of file
 */ 

#endif/* CORE_ARTERYTEK_AT32F415_B318B6BC_65EC_4A53_B95D_9955CF5B1BAC */
