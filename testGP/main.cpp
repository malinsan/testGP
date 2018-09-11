#include <stm32f4xx.h>
#include <stdlib.h>
#include <stdio.h>

#include <BlinkLed.h>

extern "C" {
  #include <Timer.h>
}

#include <stm32f4xx_dma.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rng.h>

#include "string.h"
#include "StringPrinter.h"





#define BLINK_ON_TICKS (TIMER_FREQUENCY_HZ * 2 / 3)

#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)


#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma GCC diagnostic ignored "-Wmissing-declarations"

#pragma GCC diagnostic ignored "-Wreturn-type"


/*
  VARIABLES
*/
StringPrinter sp;
bool rng_enabled = false;

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

/**
  Get a random number between min and max.
  Uses functions from stm32f4xx_rng.c
*/
uint8_t getRandomNumber(uint32_t min, uint8_t max){
  uint32_t random = 0;

  if(!rng_enabled){
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    RNG_Cmd(ENABLE);
    rng_enabled = true;
  }

  while(random <= min){
    if(RNG_GetFlagStatus(RNG_FLAG_DRDY)){
      random = RNG_GetRandomNumber();
      random &= max;
    }
  }
  return (uint8_t)random;
}



int main(int argc, char* argv[]){

  SystemInit();

  blink_led_init();
  blink_led_on();

  timer_start();


  char t[10] = "Test";
  char yoMom[10] = "Din Mamma";
  char yo[10] = "yoooooo";

  sp.printStartUp();

   while(1){

     uint8_t a = getRandomNumber(5,30);
     char random[5];
     sprintf(random,"%d", a);

      blink_led_on();

      timer_sleep(BLINK_ON_TICKS);



      blink_led_off();

      sp.printText(yoMom);
      sp.printText(random);

      timer_sleep(BLINK_OFF_TICKS);

   }


}





#pragma GCC diagnostic pop
