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
    void setSize(int size);
    Instruction* getInstructions();
    void setInstructions(int listOfInstructions);
//    void crossoverInstructions(int crossPoint1, int crossPoint2, Individual individual2);
    void crossoverInstructions(int crossPoint, Individual otherIndividual);
    void mutate(int pMut);
    void toString(char individualString []);

    int getNumberOfCrossovers();

    Individual();
    Individual(int length);

    int index;
    int individualNumber; //for finding instructions in the list of instructions
  private:
    int fitness;
    int size;
};

#endif
