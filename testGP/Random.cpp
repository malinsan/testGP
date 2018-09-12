#include "Random.h"
#include <stdio.h>
#include "StringPrinter.h"

bool Random::rng_enabled = false;

Random::Random(void){
  enableRNG();
}

/**
  Get a random number between min and max.
  Uses functions from stm32f4xx_rng.c
  This function does not seem to create any UB  which is nice!
*/
uint8_t Random::getRandomNumber(uint8_t min, uint8_t max){
  uint32_t random = 0;
  bool firstLoop = false;
  StringPrinter sp;

  while(!firstLoop || random < min){
    firstLoop = true;
    if(RNG_GetFlagStatus(RNG_FLAG_DRDY)){
      random = RNG_GetRandomNumber();
      random &= max;
    }
  }
  return (uint8_t)random;
}


void Random::getRandomNumberAsChar(char array[], uint8_t min, uint8_t max){
  uint8_t randomNumber = this->getRandomNumber(min,max);
  sprintf(array,"%d ", randomNumber);
}

/* ####### PRIVATE ####### */

void Random::enableRNG(){
  if(!Random::rng_enabled){
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    RNG_Cmd(ENABLE);
    rng_enabled = true;
  }
}
