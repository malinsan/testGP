#include "gp.h"
#include "Random.h"
#include "StringPrinter.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

GP::GP(){
  this->copyTestData();
}


void GP::run(){
  this->createPopulation();
  this->evaluateIndividual(population[0]);
}


/* ###### PRIVATE ###### */

void GP::createPopulation(){
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

float GP::evaluateIndividual(Individual individualToEvaluate){
  float error = 0.0f;

  for(int i = 0; i < TEST_DATA_SIZE; i++){
    int y_result = decodeIndividual(individualToEvaluate, i);
    int y_real = (float)testData_Y[i];

    float y_dist = (float)abs(y_real - y_result);
    float y_sqr = pow(y_dist, 2.0f); //danger??

    error += y_sqr;

  }
  
  error = sqrt(error / TEST_DATA_SIZE);
  return error;
}

int GP::decodeIndividual(Individual individualToDecode, int x){
  return 0;
}

void GP::copyTestData(){
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    testData_Y[i] = Constants::TEST_DATA_A_Y[i];
  }
}
