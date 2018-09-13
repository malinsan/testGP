#include "gp.h"

#include "Instruction.h"
#include "Random.h"
#include "StringPrinter.h"
#include <math.h>
#include "HelperFunctions.h"

/** ALL VARIABLES NEEDED **/
const int POPULATION_SIZE = 50;
const int TEST_DATA_SIZE = 11;

const int MAX_GENERATIONS = 5000;
const int MIN_LENGTH = 5;
const int MAX_LENGTH = 10;

//selection
const int TOURNAMENT_SIZE = 4;
const float pTour = 0.8f;

//testdata
const int TEST_DATA_A_Y[] = {1,2,5,10,17,26,37,50,65,82,101}; // x²+1


int testData_Y[TEST_DATA_SIZE] = {};
Individual population[POPULATION_SIZE] = {};

/** END OF VARIABLES **/


GP::GP(){
  this->copyTestData();
}


void GP::run(){
  int numberOfGenerations = 0;

  this->createPopulation();
  this->evaluatePopulation();

  this->tournamentSelection();

  /*while(numberOfGenerations < MAX_GENERATIONS){
    numberOfGenerations++;



  }*/
}


/* ###### PRIVATE ###### */

void GP::createPopulation(){
  Random randNum;
  for(int i = 0; i < POPULATION_SIZE; i++){
    int r = randNum.getRandomNumber(MIN_LENGTH, MAX_LENGTH);
    Individual newIndividual(r);
    population[i] = newIndividual;
    population[i].index = i;
  }
}

void GP::evaluatePopulation(){
  for(int i = 0; i < POPULATION_SIZE; i++){
    population[i].setFitness(evaluateIndividual(population[i]));
  }

}

/*
  * Calculates the fitness of an individual using MSE
*/
float GP::evaluateIndividual(Individual individualToEvaluate){
  float error = 0.0f;
  StringPrinter sp;
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

/*
  * Runs the individual instructions for one value of x and returns the result in register "a"
*/
int GP::decodeIndividual(Individual individualToDecode, int x){
                //a,b,c
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


void GP::tournamentSelection(){
  if(TOURNAMENT_SIZE % 2 != 0){
    //kaboom
  }

  StringPrinter sp;
  Random randNum;
  int halfTourSize = TOURNAMENT_SIZE/2;

  //create two different tournaments
  Individual firstTournament[halfTourSize] = {};
  Individual secondTournament[halfTourSize] = {};

  int randomNumbers[TOURNAMENT_SIZE] = {};
  for(int i = 0; i < TOURNAMENT_SIZE; i++){
    int r = randNum.getRandomNumber(0, POPULATION_SIZE);
    if(!isValueInArray(r, randomNumbers, TOURNAMENT_SIZE)){
      randomNumbers[i] = r;
    }else{
      i--; //does this work??
    }
  }

  for(int i = 0; i < 4; i++){
    sp.printInt(randomNumbers[i]);
  }


  //randomly pick TOURNAMENT_SIZE individuals from the population
  //and put them in the tournaments
  for(int i = 0; i < TOURNAMENT_SIZE; i++){
    if(i < halfTourSize){
      firstTournament[i] = population[randomNumbers[i]];
    }else{
      secondTournament[i-halfTourSize] = population[randomNumbers[i]];
    }
  }


}




void GP::copyTestData(){
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    testData_Y[i] = TEST_DATA_A_Y[i];
  }

}
