#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Instruction.h"

class Individual
{
  public:
    int getFitness();
    void setFitness(int fitness);
    Individual();
    Individual(int length);
  private:
    int fitness;
    struct instruction instruction [];
};

#endif
