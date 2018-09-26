#include "InterruptHandler.h"
#include <stm32f4xx_usart.h>
#include <stm32f4xx_flash.h>
#include "StringPrinter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char savedData[NUMBER_OF_ROWS][NUMBER_OF_ELEMENTS_IN_ROW * 2];
int sizeOfRows[NUMBER_OF_ROWS];

static bool save_row_flag = false;
static int pos = 0;
static int numberOfRows = 0;

InterruptHandler::InterruptHandler(){
}

int InterruptHandler::getNumberOfRows(){
  return numberOfRows;
}

char * InterruptHandler::getSavedDataRow(int rowNumber){
  return savedData[rowNumber];
}

int InterruptHandler::getSaveFlagStatus(){
  return save_row_flag;
}

void InterruptHandler::setSaveFlagStatus(bool status){
  save_row_flag = status;
}

int InterruptHandler::getRowSize(int rowNumber){
  return sizeOfRows[rowNumber];
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

      //save the received data
      savedData[numberOfRows][pos++] = received_data;

      if(received_data == 13) // if newline char, that means it has read a whole row
      {
        savedData[numberOfRows][pos] = 0; //insert null on the row
        sizeOfRows[numberOfRows] = pos; //save the row size
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
