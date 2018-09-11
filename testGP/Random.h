#ifndef RANDOM_H
#define RANDOM_H

#include <stm32f4xx_rng.h>

class Random{
  public:
    uint8_t getRandomNumber(uint8_t min, uint8_t max);
    void getRandomNumberAsChar(char array[], uint8_t min, uint8_t max);
    Random();
  private:
    void enableRNG();
    static short int rng_enabled;
};

#endif
