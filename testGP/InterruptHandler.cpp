#include "InterruptHandler.h"
#include <stm32f4xx_usart.h>
#include <stm32f4xx_flash.h>
#include "StringPrinter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLASH_START_ADD           ((uint32_t) 0x08080000)
#define FLASH_END_ADD             ((uint32_t) 0x08100000)
#define NUMBER_OF_ELEMENTS_IN_ROW 5
#define ROW_SIZE_IN_BYTES         20 // NUMBER_OF_ELEMENTS_IN_ROW * 4 bytes

char row[200];
char copy_of_row[200];

static bool save_row_flag = false;
static int numberOfRowsWrittenOnFlash = 0;
static int pos = 0;
static int sizeOfCopyRow = 0;

InterruptHandler::InterruptHandler(){
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  NVIC_EnableIRQ(USART2_IRQn);
}

int InterruptHandler::getSaveFlagStatus(){
  return save_row_flag;
}

void InterruptHandler::setSaveFlagStatus(bool status){
  save_row_flag = status;
}

void InterruptHandler::saveRowToFlash(){
  StringPrinter sp;
  sp.printInt(33333);
  float rowArrayInFloats[NUMBER_OF_ELEMENTS_IN_ROW + 1] = {};
  convertASCIIToFloats(copy_of_row, rowArrayInFloats, sizeOfCopyRow);
  sp.printInt(55555);

  writeToFlash(rowArrayInFloats, numberOfRowsWrittenOnFlash);
  sp.printInt(66666);

  numberOfRowsWrittenOnFlash++;

  sp.printInt(99999);
  sp.printInt(numberOfRowsWrittenOnFlash);

}

//** INTERNAL METHODS *//

void makeCopyOfDataRow(char dataRow[], int length, char copyRow[]){
  int i = 0;
  for(i = 0; i <= length; i++){
    copyRow[i] = dataRow[i];
  }
  copyRow[i] = '\0';
}


int InterruptHandler::convertASCIIToFloats(char data_row[], float array[], int size){
  StringPrinter sp;
  if (!data_row)
  {
    return -1;
  }

  if (size < 4)
  {
    return -1;
  }

  //const char COMMA[2] = ",";
  char tmp[200];
  makeCopyOfDataRow(data_row, size, tmp);

  int var = 0;

  char hej[] = "this,is,your,mom";
  char *token;

  sp.printInt(44444);

  token = strtok(hej,",");
  sp.printInt(42424);

  while( token != NULL ) {
      if (var >= NUMBER_OF_ELEMENTS_IN_ROW)
      {
        break;
      }
      float data_value = (float)atof(token);
      array[var] = data_value;

      var++;
      token = strtok(NULL, ",");
  }

  // if first element is empty
  if (array[0] == 0)
  {
    sp.printInt(66666);
    return -1;
  }

  return var;

}

int InterruptHandler::writeToFlash(float array[], int row)
{
  StringPrinter sp;
    char buff[100];

    if (FLASH_START_ADD +(row+1)*ROW_SIZE_IN_BYTES >= FLASH_END_ADD)
    {
      return -1;
    }

    volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

//    uint32_t i = 0;
    for(int i = 0; i < NUMBER_OF_ELEMENTS_IN_ROW; i++)
    {
      uint32_t adr = (FLASH_START_ADD + (i*sizeof(float)) + row*ROW_SIZE_IN_BYTES);
      FLASH_Unlock();
      FLASHStatus = FLASH_ProgramWord(adr, *(uint32_t *)&array[i]);
      FLASH_Lock();
      if (FLASHStatus != FLASH_COMPLETE)
      {
        sprintf(buff, "Failed with %d %x %x \n", FLASHStatus, adr, FLASH->SR);
        sp.printText(buff);
        break;
      }

    }

    return 0;

}


//interrupt handling
extern "C" {
  void USART2_IRQHandler(void) {
    StringPrinter sp;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // never in a while loop
    {
      USART_ClearITPendingBit(USART2, USART_IT_RXNE);//clear flag

      uint16_t received_data = USART_ReceiveData(USART2);

      if (pos > 198) // avoid overflow since row[200]
      {
        pos = 0;
      }

      if(received_data == 33){
        sp.printInt(55555);
      }

      row[pos++] = received_data;
      if(received_data == 10) // if NULL char, that means it has read a whole row
      {
        row[pos] = 0;
        makeCopyOfDataRow(row, pos, copy_of_row);
        sizeOfCopyRow = pos;
        pos = 0;         // restart position
        save_row_flag = true;
        sp.printInt(11111);
      }
    }

    // if Overrun flag (USAT_FLAG_ORE) is still set, clear it with ReceiveData
    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
    {
      //error_counter++;
      uint16_t received_data = USART_ReceiveData(USART2);
    }
  }

}
