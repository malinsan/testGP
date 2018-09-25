#include <stm32f4xx.h>
#include <stdlib.h>
#include <stdio.h>

#include <BlinkLed.h>

extern "C" {
  #include <Timer.h>
}

#include <stm32f4xx_dma.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rng.h> //random number generator
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

#include "string.h"

#include "StringPrinter.h"
#include "Random.h"
#include "Individual.h"
#include "gp.h"
#include "InterruptHandler.h"

#define BLINK_ON_TICKS (TIMER_FREQUENCY_HZ * 2 / 3)

#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)


#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma GCC diagnostic ignored "-Wmissing-declarations"

#pragma GCC diagnostic ignored "-Wreturn-type"

void blink_led_init()
{

 // Enable GPIO Peripheral clock

 RCC->AHB1ENR |= BLINK_RCC_MASKx(BLINK_PORT_NUMBER);

 GPIO_InitTypeDef GPIO_InitStructure;

 // Configure pin in output push/pull mode

 GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(BLINK_PIN_NUMBER);

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;

 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

 GPIO_Init(BLINK_GPIOx(BLINK_PORT_NUMBER), &GPIO_InitStructure);

 // Start with led turned off
 blink_led_off();

}


void initPeripherals(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

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

	/*NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  NVIC_EnableIRQ(USART2_IRQn);
}


int main(int argc, char* argv[]){

  /**
    Initialization
  */
  SystemInit();

  initPeripherals(); //init USART2
  InterruptHandler interruptHandler;

  StringPrinter sprint;
//Random randNum;
// GP gp;


  blink_led_init();
  blink_led_on();

  timer_start();

  //gp.run(); //start genetic programming

  //char yoMom[20] = "Din mamma";

  sprint.printStartUp();

  char buff[100];
  uint32_t *r = (uint32_t*)(FLASH_END_ADD - sizeof(uint32_t));
  sprintf(buff, "%d rows in flash\n\r", *r);
  sprint.printText(buff);

   while(1){
      blink_led_on();

      timer_sleep(BLINK_ON_TICKS);

      blink_led_off();

      if(interruptHandler.getSaveFlagStatus()){
        sprint.printInt(22222);
        interruptHandler.saveRowsToFlash();
        interruptHandler.setSaveFlagStatus(false);
      }

      sprint.printInt(interruptHandler.getValueFromFlash(1,1));

      //sprint.printText(yoMom);
      //sprint.printText(random);
      //sprint.printInt(r);

      timer_sleep(BLINK_OFF_TICKS);

   }


}



#pragma GCC diagnostic pop
