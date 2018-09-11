#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Instruction.h"
#include "constants.h"

//const int maxLength = Constants::MAX_INDIVIDUAL_LENGTH;
const int maxLength = 30;

class Individual
{
  public:
    int getFitness();
    void setFitness(int fitness);
    instruction * getInstructions();
    Individual();
    Individual(int length);
  private:
    int fitness;
    instruction instructions [MAX_LENGTH];
};

#endif
