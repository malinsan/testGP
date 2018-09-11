#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Instruction.h"
#include "constants.h"

class Individual
{
  public:
    int getFitness();
    void setFitness(int fitness);
    Individual();
    Individual(int length);
  private:
    int fitness;
//    struct instruction instructions [Constants::MAX_INDIVIDUAL_LENGTH];
    struct instruction instructions [3];
};

#endif
