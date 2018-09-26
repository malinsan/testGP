#include "FlashWriter.h"
#include <stm32f4xx_flash.h>
#include <stm32f4xx_usart.h>
#include "StringPrinter.h"
#include "HelperFunctions.h"

#include <stdint.h> //uint32_t

static int numberOfRowsWrittenToFlash = 0;

FlashWriter::FlashWriter(){
    FLASH_SetLatency(FLASH_Latency_5);

}

void eraseFlashSector(){
  FLASH_Unlock();

  FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3);

  FLASH_Lock();//lock the flash for writing
}

void FlashWriter::writeValueToFlash(uint32_t adr, uint32_t data){
  FLASH_Unlock();

  //FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3);

  FLASH_ProgramWord(adr, data);

  FLASH_Lock();//lock the flash for writing


}

uint32_t FlashWriter::getValueFromFlash(uint32_t adr){
  uint32_t * result = (uint32_t *)adr;

  return *result;
}


void FlashWriter::writeFloatValueToFlash(uint32_t adr, float data){
  uint32_t floatToUint32 = *(uint32_t *)&data;

  this->writeValueToFlash(adr, floatToUint32);

}

void FlashWriter::writeCharArrayAsFloatToFlash(uint32_t adr, char data [], int dataSize){
  float floatDataArray[dataSize] = {};
  //translate char array into float array
  convertASCIIToFloats(data, floatDataArray, dataSize);

  eraseFlashSector();
  
  for(int i = 0; i < dataSize; i++){
    this->writeFloatValueToFlash(adr + (i * sizeof(float)), floatDataArray[i]);
  }


}


float FlashWriter::getValueFromFlashAsFloat(uint32_t adr){

  float * result = (float *)adr;

  return *result;

}