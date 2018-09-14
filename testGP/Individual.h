#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Instruction.h"

//const int maxLength = Constants::MAX_INDIVIDUAL_LENGTH;
const int maxLength = 30;

class Individual
{
  public:
    int getFitness();
    void setFitness(int fitness);
    int getSize();
    Instruction* getInstructions();
    Individual();
    Individual(int length);

    int index;
    int individualNumber; //for finding instructions in the list of instructions
  private:
    int fitness;
    int size;
};

#endif
