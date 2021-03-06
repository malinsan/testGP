#include "StringPrinter.h"


StringPrinter::StringPrinter(void){
	usartInit = false;
}


void StringPrinter::printStartUp(){
	char systemStarted[15] = "System Started";
	this->printText(systemStarted);
}



//wrapper
void StringPrinter::printText(char * s){
	if(!usartInit){
		init_USART2();
		usartInit = true;
	}
	StringPrinter::USART_PutString(s);
}


/* ########## PRIVATE ################# */
void StringPrinter::USART_PutChar(char c)
{
   // Wait until transmit data register is empty
   while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
   // Send a char using USART1
   USART_SendData(USART2, c);
}



void StringPrinter::USART_PutString(char * s)

{
   // Send a string
  	while (*s)
   {
       USART_PutChar(*s++);
   }

}

/*

* Configure USART3(PB10, PB11) to redirect printf data to host PC.

*/

void StringPrinter::init_USART2(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

  USART_Cmd(USART2, ENABLE);

  USART_InitStruct.USART_BaudRate = 38400; // should be set to 57600 on putty/realterm
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  

  USART_Init(USART2, &USART_InitStruct);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  NVIC_EnableIRQ(USART2_IRQn);
  
}