#include "gp.h"
#include "Random.h"
#include "constants.h"
#include "StringPrinter.h"

GP::GP(){

}


void GP::run(){
  this->createPopulation();
}


/* ###### PRIVATE ###### */

void GP::createPopulation(){
  StringPrinter sp;
  Random randNum;
  for(int i = 0; i < POPULATION_SIZE; i++){
    int r = randNum.getRandomNumber(MIN_LENGTH, MAX_LENGTH);
    Individual newIndividual(r);
    population[i] = newIndividual;
    sp.printInt(population[i].getInstructions()->reg);
  }
}

void GP::evaluatePopulation(){

}

int GP::evaluateIndividual(Individual individualToEvaluate){

}
