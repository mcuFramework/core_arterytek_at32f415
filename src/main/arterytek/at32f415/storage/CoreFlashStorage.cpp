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
#include "arterytek/at32f415/storage/CoreFlashStorage.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
using arterytek::at32f415::storage::CoreFlashStorage;
using mcuf::io::ByteBuffer;
using hal::storage::FlashStorageEvent;
using hal::storage::FlashStorageStatus;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

/**
 * @brief Construct a new Core Flash Storage:: Core Flash Storage object
 * 
 */
CoreFlashStorage::CoreFlashStorage(void){
  this->mBusy = false;
  this->mAddress = 0x00000000;
}

/**
 * @brief Destroy the Core Flash Storage:: Core Flash Storage object
 * 
 */
CoreFlashStorage::~CoreFlashStorage(void){
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - hal::storage::FlashStorageControl
 */

/**
 * @brief Set the Address object
 * 
 * @param address 
 */
void CoreFlashStorage::setAddress(uint32_t address){
  this->mAddress = address;
}

/**
 * @brief Get the Address object
 * 
 * @return uint32_t 
 */
uint32_t CoreFlashStorage::getAddress(void){
  return this->mAddress;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreFlashStorage::flashSize(void){
  return 128 * 1024;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreFlashStorage::pageSize(void){
  return 1024;
}

/**
 * @brief 
 * 
 * @param pageNumber 
 * @return true 
 * @return false 
 */

bool CoreFlashStorage::pageErase(uint32_t pageNumber){
  return false;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreFlashStorage::sectorSize(void){
  return 1024;
}

/**
 * @brief 
 * 
 * @param sectorNumber 
 * @return true 
 * @return false 
 */
bool CoreFlashStorage::sectorErase(uint32_t sectorNumber){
  if(this->mBusy)
    return false;
  
  this->mBusy = true;

  uint32_t addr = (this->getFlashBase() + (sectorNumber * this->sectorSize()));
  
  if(addr >= this->getFlashBase() + this->flashSize()){
    this->mBusy = false;
    return false;
  }
  
  flash_status_type result = flash_sector_erase(addr);
  flash_unlock();
  
  flash_lock();
  this->mBusy = false;
  return (result == FLASH_OPERATE_DONE);
}

/**
 * @brief 
 * 
 * @param bytebuffer 
 * @param attachment 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreFlashStorage::write(ByteBuffer& byteBuffer, void* attachment, FlashStorageEvent* event){
  if(this->mBusy)
    return false;
  
  this->mBusy = true;  
  
  void* src = byteBuffer.pointer(byteBuffer.position());
  uint32_t length = static_cast<uint32_t>(byteBuffer.remaining());
  bool result = false;
  FlashStorageStatus status = FlashStorageStatus::WRITE_FAIL;
  
  if((this->mAddress + length) > this->flashSize()){
    length = 0;
    
  }else{
    result = this->flashWrite(this->mAddress, src, length);
    if(result){
      byteBuffer += static_cast<int>(length);
      status = FlashStorageStatus::WRITE_SUCCESSFUL;
      this->mAddress += length;
    }
  }
  
  this->mBusy = false;
  if(event)
    event->onFlashStorageEvent(status, static_cast<int>(length), attachment);
  
  return result;
}

/**
 * @brief 
 * 
 * @param bytebuffer 
 * @param attachment 
 * @param event 
 * @return true 
 * @return false 
 */
bool CoreFlashStorage::read(ByteBuffer& byteBuffer, void* attachment, FlashStorageEvent* event){
  if(this->mBusy)
    return false;
  
  this->mBusy = true;  
  
  bool result = false;
  int length = byteBuffer.remaining();
  FlashStorageStatus status = FlashStorageStatus::READ_FAIL;
  
  if(!byteBuffer.isReadOnly()){
    uint32_t offset = this->getFlashBase() + this->mAddress;
    
    if(mAddress + static_cast<uint32_t>(length) <= this->flashSize()){
      byteBuffer.put(reinterpret_cast<void*>(offset), length);    
      byteBuffer += length;
      status = FlashStorageStatus::READ_SUCCESSFUL;
      result = true;
    }
  }
  
  if(result){
    this->mAddress += static_cast<uint32_t>(length);
  }else{
    length = 0;
  }
  
  this->mBusy = false;
  if(event)
    event->onFlashStorageEvent(status, length, attachment);
  
  return result;
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

bool CoreFlashStorage::flashWrite(uint32_t address, void* src, uint32_t length){
  flash_unlock();
  char* ptr = static_cast<char*>(src);
  
  if(address & 0x0000001){
    uint16_t cache = 0xFF00 | *ptr;
    this->flashWriteNocheck((address - 1), &cache, 1);
    --length;
    ++address;
    ++ptr;
  }
  
  if(length & 0x00000001){
    uint16_t cache = static_cast<uint16_t>(0x00FF | (ptr[length-1] << 8));
    this->flashWriteNocheck(((address + length)  - 1), &cache, 1);
    --length;
  }
  
  this->flashWriteNocheck(address, reinterpret_cast<uint16_t*>(ptr), static_cast<uint16_t>(length>>1));
  
  flash_lock();
  return true;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t CoreFlashStorage::getFlashBase(void) const{
  return 0x08000000;
}

/**
 * @brief 
 * 
 * @param addr 
 * @param src 
 * @param numb 
 */
void CoreFlashStorage::flashWriteNocheck(uint32_t addr, uint16_t *src, uint16_t numb){
  uint16_t i;
  for(i = 0; i < numb; i++)
  {
    flash_halfword_program(addr, src[i]);
    addr += 2;
  }  
}

/* ****************************************************************************************
 * End of file
 */
