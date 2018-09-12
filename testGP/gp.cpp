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
    Individual newIndividual(randNum.getRandomNumber(MIN_LENGTH, MAX_LENGTH));
    population[i] = newIndividual;
    sp.printInt(population[i].getInstructions()->reg);
  }
}
