#include "gp.h"
#include "Random.h"
#include "constants.h"
#include "StringPrinter.h"
#include <stdio.h>
#include <string.h>

GP::GP(){
  StringPrinter sp;
  this->copyTestData();
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    sp.printInt(testData_Y[i]);
  }
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
    //sp.printInt(population[i].getInstructions()->reg);
  }
}

void GP::evaluatePopulation(){

}

int GP::evaluateIndividual(Individual individualToEvaluate){
  int error = 0;
  for(int i = 0; i < testDataSize; i++){

  }
}

void GP::copyTestData(){
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    testData_Y[i] = Constants::TEST_DATA_A_Y[i];
  }
}
