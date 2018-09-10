#include <stm32f4xx.h>

#include <BlinkLed.h>

extern "C" {
  #include <Timer.h>  
}

#include <stm32f4xx_dma.h>
#include <stm32f4xx_usart.h>

#include "string.h"
#include "TestClass.h"
#include "StringPrinter.h"



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



int main(int argc, char* argv[])

{

  SystemInit();



  blink_led_init();



  blink_led_on();



  timer_start();

  StringPrinter sp;

  char t[10] = "Test";
  char yoMom[10] = "Din Mamma";


  char yo[10] = "yoooooo";

  sp.printStartUp();
  //string a = "hej";
  //sp.printString(a);

  TestClass test;


   while(1)

   {

    test.incX();

    blink_led_on();

    timer_sleep(BLINK_ON_TICKS);



    blink_led_off();


    if(test.getX() % 5 == 0){
      sp.printText(yoMom);      
    }else{
      sp.printText(t);      
    }


    timer_sleep(BLINK_OFF_TICKS);

   }


}





#pragma GCC diagnostic pop