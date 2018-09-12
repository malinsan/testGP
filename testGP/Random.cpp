#include "Random.h"
#include <stdio.h>
#include "StringPrinter.h"

short int Random::rng_enabled = 0;

Random::Random(void){
  enableRNG();
}

/**
  Get a random number between min and max.
  Uses functions from stm32f4xx_rng.c
*/
uint8_t Random::getRandomNumber(uint8_t min, uint8_t max){
  uint32_t random = 0;

  if(RNG_GetFlagStatus(RNG_FLAG_DRDY)){
    random = RNG_GetRandomNumber() % (max+1) + min; //as according to c++ documentation
  }

  return (uint8_t)random;
}

void Random::getRandomNumberAsChar(char array[], uint8_t min, uint8_t max){
  uint8_t randomNumber = this->getRandomNumber(min,max);
  sprintf(array,"%d ", randomNumber);
}

/* ####### PRIVATE ####### */

void Random::enableRNG(){
  if(Random::rng_enabled == 0){
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    RNG_Cmd(ENABLE);
    rng_enabled++;
  }
}
