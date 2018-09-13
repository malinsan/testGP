#include "gp.h"

#include "Instruction.h"
#include "Random.h"
#include "StringPrinter.h"
#include <math.h>


int testData_Y[TEST_DATA_SIZE] = {};
Individual population[POPULATION_SIZE] = {};


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
  }
}

void GP::evaluatePopulation(){

}

float GP::evaluateIndividual(Individual individualToEvaluate){
  float error = 0.0f;
  StringPrinter sp;
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    int y_result = decodeIndividual(individualToEvaluate, i);
    sp.printInt(y_result);
    int y_real = (float)testData_Y[i];

    float y_dist = (float)abs(y_real - y_result);
    float y_sqr = pow(y_dist, 2.0f); //danger??

    error += y_sqr;

  }
  error = sqrt(error / TEST_DATA_SIZE);
  return error;
}

int GP::decodeIndividual(Individual individualToDecode, int x){

  int values[] = {x,0,0,-1,0,1};

  for(int i = 0; i < individualToDecode.getSize(); i++){
    int result = 0;
    Instruction currentInstruction = individualToDecode.getInstructions()[i];

    switch (currentInstruction.operation) {
      case 0: // +
        result = values[currentInstruction.op1] + values[currentInstruction.op2];
        break;
      case 1: // -
        result = values[currentInstruction.op1] - values[currentInstruction.op2];
        break;
      case 2: // *
        result = values[currentInstruction.op1] * values[currentInstruction.op2];
        break;
    }
    values[0] = result;
  }

  return values[0];
}

void GP::copyTestData(){
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    testData_Y[i] = Constants::TEST_DATA_A_Y[i];
  }

}
