#include "InterruptHandler.h"
#include <stm32f4xx_usart.h>
#include <stm32f4xx_flash.h>
#include "StringPrinter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NUMBER_OF_ELEMENTS_IN_ROW 10
#define ROW_SIZE_IN_BYTES         NUMBER_OF_ELEMENTS_IN_ROW * 4 // NUMBER_OF_ELEMENTS_IN_ROW * 4 bytes
#define SIZE_OF_ROW_ARRAY         200

int writeToFlash(float* array, int rowNumber); //extern C?

char rows[SIZE_OF_ROW_ARRAY][NUMBER_OF_ELEMENTS_IN_ROW * 2];
int sizeOfRows[SIZE_OF_ROW_ARRAY];
char copy_of_row[200]; //throw away?

static bool save_row_flag = false;
static int numberOfRowsWrittenToFlash = 0;
static int pos = 0;
static int sizeOfCopyRow = 0; //släng
static int numberOfRows = 0;

InterruptHandler::InterruptHandler(){
  FLASH_SetLatency(FLASH_Latency_5);
}

int InterruptHandler::getSaveFlagStatus(){
  return save_row_flag;
}

void InterruptHandler::setSaveFlagStatus(bool status){
  save_row_flag = status;
}

void InterruptHandler::saveRowsToFlash(){
  StringPrinter sp;
  sp.printInt(33333);
  sp.printInt(numberOfRows);

  FLASH_Unlock();
  FLASH_Status status = FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3);
  if(status == FLASH_COMPLETE){
    sp.printInt(3232);
  }
  //FLASH_Lock();

  /*for(int i = 0; i < numberOfRows; i++){
    float rowArrayInFloats[NUMBER_OF_ELEMENTS_IN_ROW + 1] = {};
    convertASCIIToFloats(rows[i], rowArrayInFloats, sizeOfRows[i]);
    sp.printInt(55555);
    writeToFlash(rowArrayInFloats, i);
    sp.printInt(66666);
  }
*/

  //FLASH_Unlock();
  //uint32_t adr = (FLASH_END_ADD - sizeof(uint32_t)); // -4
  uint32_t adr = FLASH_START_ADD;
  float num = 5.0f;
  uint32_t data = *(uint32_t *)&num;
  //(void)FLASH_ProgramWord(adr, (uint32_t)numberOfRowsWrittenToFlash);
  FLASH_ProgramWord(adr, data);
  FLASH_Lock();//lock the flash for writing


  sp.printInt(99999);
  sp.printInt(numberOfRowsWrittenToFlash);

}

float InterruptHandler::getValueFromFlash(int rowNmr, int x){
  float* f = (float*)FLASH_START_ADD;

  //return f[(rowNmr * NUMBER_OF_ELEMENTS_IN_ROW) + (x)];
  return *f;

}

//** INTERNAL METHODS *//

/*
* Malins little version of strtok
* returns false when the end of the buffer is reached, otherwise returns true
*/
bool myStrtok(bool firstRun, char buffer [], const char delimiter [], char returnString []){
  static int bufferPosition;
  if(firstRun){
    bufferPosition = 0;
  }
  if(buffer[bufferPosition] == '\0'){ //when the end of buffer is reached
    return false;
  }

  int startPostion = bufferPosition;
  int endPosition = startPostion;

  while(buffer[endPosition] != delimiter[0]){
    endPosition++;
  }

  int i;
  int j = 0;
  for(i = startPostion; i < endPosition; i++){
    returnString[j] = buffer[i];
    j++;
  }
  returnString[j] = '\0';

  bufferPosition = endPosition + 1;

  return true;
}

/*
* Turns a char array into a float
*/
float stof(char s []){
  float rez = 0, fact = 1;
  int pos = 0;
  if (s[pos] == '-'){
    pos++;
    fact = -1;
  }
  for (bool point_seen = false; s[pos] != '\0'; pos++){
    if (s[pos] == '.'){
      point_seen = true;
      continue;
    }
    int d = s[pos] - '0';
    if (d >= 0 && d <= 9){
      if (point_seen){
        fact /= 10.0f;
      }
      rez = rez * 10.0f + (float)d;
    }
  }
  return rez * fact;

}


void makeCopyOfDataRow(char dataRow[], int length, char copyRow[]){
  StringPrinter sp;
  int i = 0;
  for(i = 0; i <= length; i++){
    copyRow[i] = dataRow[i];
  }
  copyRow[i] = '\0';
  sizeOfCopyRow = length;
}


int InterruptHandler::convertASCIIToFloats(char data_row[], float array[], int size){
  StringPrinter sp;

  if (!data_row){
    return -1;
  }

  if (size < 4){
    return -1;
  }

  const char COMMA[2] = ",";
  char tmp[SIZE_OF_ROW_ARRAY];
  makeCopyOfDataRow(data_row, size, tmp);
  char token[10];
  bool tokenizeBuffer = myStrtok(true,tmp,COMMA,token);


  int var = 0;
  while( tokenizeBuffer ) {

    if (var >= NUMBER_OF_ELEMENTS_IN_ROW)
    {
      break;
    }
    float data_value = (float)stof(token);
    sp.printInt(data_value);

    array[var] = data_value;

    var++;
    tokenizeBuffer = myStrtok(false,tmp,COMMA,token);
  }

  // if first element is empty
  if (array[0] == 0)
  {
    return -1;
  }

  return var;

}

int writeToFlash(float* array, int rowNumber)
{
  StringPrinter sp;
  sp.printInt(6868);
  char buff[100];

  if (FLASH_START_ADD +(rowNumber+1)*ROW_SIZE_IN_BYTES >= FLASH_END_ADD)
  {
    return -1;
  }

  volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

//    uint32_t i = 0;
  for(int i = 0; i < NUMBER_OF_ELEMENTS_IN_ROW; i++)
  {
    uint32_t adr = (FLASH_START_ADD + (i*32) + rowNumber*ROW_SIZE_IN_BYTES);

    FLASH_Unlock();
    FLASHStatus = FLASH_ProgramWord(adr, *(uint32_t *)&array[i]);
    FLASH_Lock();

    if (FLASHStatus != FLASH_COMPLETE)
    {
      sprintf(buff, "Failed with %d %x %x \n", FLASHStatus, adr, FLASH->SR);
      sp.printText(buff);
      sp.printInt(6767);
      break;
    }else{
      numberOfRowsWrittenToFlash++;
    }

  }


  return 0;

}


//interrupt handling
extern "C" {
  void USART2_IRQHandler(void) {
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // never in a while loop
    {
      USART_ClearITPendingBit(USART2, USART_IT_RXNE);//clear flag

      uint16_t received_data = USART_ReceiveData(USART2);

      if (pos > 198) // avoid overflow since row[200]
      {
        pos = 0;
      }

      if(received_data == 33){
      }

      rows[numberOfRows][pos++] = received_data;
      if(received_data == 13) // if newline char, that means it has read a whole row
      {
        rows[numberOfRows][pos] = 0; //insert null on the row
        sizeOfRows[numberOfRows] = pos;
        pos = 0;         // restart position
        numberOfRows++;
        save_row_flag = true;
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
