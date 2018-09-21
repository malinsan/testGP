#include "InterruptHandler.h"
#include <stm32f4xx_usart.h>
#include "StringPrinter.h"

char row[200];
char copy_of_row[200];

static bool save_row_flag = false;
static int pos = 0;

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

//** INTERNAL METHODS *//

void make_a_copy_of_data_row(char data_row[], int length){
  int i = 0;
  for(i = 0; i < length; i++){
    copy_of_row[i] = data_row[i];
  }
  copy_of_row[i] = '\0';
}

//interrupt handling
extern "C" {
  void USART2_IRQHandler(void) {
    StringPrinter sp;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // never in a while loop
    {
      USART_ClearITPendingBit(USART2, USART_IT_RXNE);
      uint16_t received_data = USART_ReceiveData(USART2);

      if (pos > 198) // avoid overflow since row[200]
      {
        pos = 0;
      }

      if(received_data == 33){
        save_row_flag = true;
        sp.printInt(55555);
      }

      row[pos++] = received_data;
      if(received_data == 10) // if NULL char, that means it has read a whole row
      {
        row[pos] = 0;
        make_a_copy_of_data_row(row, pos);
        pos = 0;         // restart position
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
