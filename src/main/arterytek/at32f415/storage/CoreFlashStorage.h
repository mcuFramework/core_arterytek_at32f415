/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */
#ifndef CORE_ARTERYTEK_AT32F415_F9F5B621_B341_4FBE_B39B_826822BAC2FA
#define CORE_ARTERYTEK_AT32F415_F9F5B621_B341_4FBE_B39B_826822BAC2FA

/* ****************************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------------------
#include "mcuf.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Namespace
 */  
namespace arterytek{
  namespace at32f415{
    namespace storage{
      class CoreFlashStorage;
    }
  }
}


/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */  
class arterytek::at32f415::storage::CoreFlashStorage extends mcuf::lang::Object implements
  public hal::storage::FlashStorage{

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
    uint32_t mAddress;
    bool mBusy;

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
     * @brief Construct a new Core Flash Storage object
     * 
     */
    CoreFlashStorage(void);

    /**
     * @brief Destroy the Core Flash Storage object
     * 
     */
    virtual ~CoreFlashStorage(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - hal::storage::FlashStorageControl
   */
  public:

    /**
     * @brief Set the Address object
     * 
     * @param address 
     */
    virtual void setAddress(uint32_t address) override;

    /**
     * @brief Get the Address object
     * 
     * @return uint32_t 
     */
    virtual uint32_t getAddress(void) override;

    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t flashSize(void) override;

    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t pageSize(void) override;

    /**
     * @brief 
     * 
     * @param pageNumber 
     * @return true 
     * @return false 
     */
    virtual bool pageErase(uint32_t pageNumber) override;

    /**
     * @brief 
     * 
     * @return uint32_t 
     */
    virtual uint32_t sectorSize(void) override;

    /**
     * @brief 
     * 
     * @param sectorNumber 
     * @return true 
     * @return false 
     */
    virtual bool sectorErase(uint32_t sectorNumber) override;

    /**
     * @brief 
     * 
     * @param bytebuffer 
     * @param attachment 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool write(mcuf::io::ByteBuffer& byteBuffer, 
                       void* attachment,
                       hal::storage::FlashStorageEvent* event) override;

    /**
     * @brief 
     * 
     * @param bytebuffer 
     * @param attachment 
     * @param event 
     * @return true 
     * @return false 
     */
    virtual bool read(mcuf::io::ByteBuffer& byteBuffer, 
                      void* attachment,
                      hal::storage::FlashStorageEvent* event) override;

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
     * @brief 
     * 
     * @param write_addr 
     * @param p_buffer 
     * @param num_write 
     */
    bool flashWrite(uint32_t address, void* src, uint32_t length);
  
    /**
     * @brief Get the Flash Base object
     * 
     * @return uint32_t 
     */
    constexpr uint32_t getFlashBase(void) const;
  
    /**
     * @brief 
     * 
     * @param addr 
     * @param src 
     * @param numb 
     */
    void flashWriteNocheck(uint32_t addr, uint16_t *src, uint16_t numb);


};

/* ****************************************************************************************
 * End of file
 */ 

#endif /* CORE_ARTERYTEK_AT32F415_F9F5B621_B341_4FBE_B39B_826822BAC2FA */
