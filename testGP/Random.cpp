#include "Random.h"

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

  while(random <= min){
    if(RNG_GetFlagStatus(RNG_FLAG_DRDY)){
      random = RNG_GetRandomNumber();
      random &= max;
    }
  }
  return (uint8_t)random;
}

/* ####### PRIVATE ####### */

void Random::enableRNG(){
  if(Random::rng_enabled == 0){
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
    RNG_Cmd(ENABLE);
    rng_enabled++;
  }
}
