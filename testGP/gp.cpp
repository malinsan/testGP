#include "gp.h"

#include "Instruction.h"
#include "Random.h"
#include "StringPrinter.h"
#include <math.h>
#include "HelperFunctions.h"

/** ALL VARIABLES NEEDED **/
const int POPULATION_SIZE = 5;
const int TEST_DATA_SIZE = 11;

const int MAX_GENERATIONS = 5000;
const int MAX_LENGTH = 10;
const int MIN_LENGTH = 5;


//selection
const int TOURNAMENT_SIZE = 4;
const float pTour = 0.8f;

//testdata
const int TEST_DATA_A_Y[] = {1,2,5,10,17,26,37,50,65,82,101}; // x²+1


//int testData_Y[TEST_DATA_SIZE] = {};
Individual population[POPULATION_SIZE] = {};

/** END OF VARIABLES **/


GP::GP(){
  //this->copyTestData();
}


void GP::run(){
  int numberOfGenerations = 0;

  this->createPopulation();
  this->evaluatePopulation();

  //this->tournamentSelection();

  /*while(numberOfGenerations < MAX_GENERATIONS){
    numberOfGenerations++;



  }*/
}


/* ###### PRIVATE ###### */

void GP::createPopulation(){
  Random randNum;
  StringPrinter sp;
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
int countA = 0;
float GP::evaluateIndividual(Individual individualToEvaluate){
  countA ++;
  float error = 0.0f;
  StringPrinter sp;
  /*sp.printInt(55555);
  sp.printInt(countA);*/
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    sp.printInt(44444);
    sp.printInt(TEST_DATA_A_Y[i]);
    int y_result = decodeIndividual(individualToEvaluate, i);

    int y_real = TEST_DATA_A_Y[i];

    /*sp.printInt(44444);
    sp.printInt(y_result);
    sp.printInt(33333);
    sp.printInt(y_real);
    sp.printInt(22222);*/
    float y_dist = (float)abs(y_real - y_result);
    //sp.printInt(y_dist);
    float y_sqr = pow(y_dist, 2.0f); //danger??

    error += y_sqr;

  }
  error = sqrt(error / TEST_DATA_SIZE);
  //sp.printInt(error);
  return error;
}

/*
  * Runs the individual instructions for one value of x and returns the result in register "a"
*/
int GP::decodeIndividual(Individual individualToDecode, int x){
                //a,b,c
  StringPrinter sp;
  int values[] = {x,0,0,-1,0,1};
  for(int i = 0; i < individualToDecode.getSize(); i++){

    //overflow handling
    bool overflow = false;

    int result = 0;
    Instruction currentInstruction = individualToDecode.getInstructions()[i];

    //sp.printInt(6666);
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
    values[currentInstruction.reg] = result; //if reg > 5 kabooom
  }

  return values[0];
}

//must be able to scale!
bool GP::isOverflow(int values[], int size){
  bool overflow = false;

  for(int i = 0; i < size ; i++){

  }

  return overflow;
}


void GP::tournamentSelection(){
  if(TOURNAMENT_SIZE % 2 != 0){
    //kaboom
  }

  StringPrinter sp;
  Random randNum;
  int halfTourSize = TOURNAMENT_SIZE/2;

  //create two different tournaments
  Individual firstTournament[halfTourSize];
  Individual secondTournament[halfTourSize];

  //** RANDOMIZING NUMBERS **//
  int randomNumbers[TOURNAMENT_SIZE] = {};
  // +1 or we can't get the 0th individual
  randNum.getRandomNumberArray(randomNumbers, TOURNAMENT_SIZE, 1, POPULATION_SIZE-1);

  for(int i = 0; i < TOURNAMENT_SIZE; i++){
    randomNumbers[i] --; //-1 to get the 'real' index
    if(randomNumbers[i] >= POPULATION_SIZE){
      //kaboom
    }
  }
  // RANDOMIZING NUMBERS END //

  //use random numbers to fill in the tournaments
  for(int i = 0; i < TOURNAMENT_SIZE; i++){
    if(i < halfTourSize){
      firstTournament[i] = population[randomNumbers[i]];
    }else{
      secondTournament[i-halfTourSize] = population[randomNumbers[i]];
    }
  }

  Individual winners[halfTourSize];
  Individual losers[halfTourSize];

  runTournament(firstTournament, secondTournament, winners, losers, halfTourSize);





}

void GP::runTournament(Individual firstTournament[], Individual secondTournament[],
                        Individual winners[], Individual losers[], int size){
  //run first tournament
  Individual winner = firstTournament[0];
  Individual loser = firstTournament[0];
  for(int i = 1; i < size; i++){
    if(firstTournament[i].getFitness() < winner.getFitness()){
      winner = firstTournament[i];
    }
    if(firstTournament[i].getFitness() >= loser.getFitness()){
      loser = firstTournament[i];
    }
  }
  winners[0] = winner;
  losers[0] = loser;
  //run second tournament
  winner = secondTournament[0];
  loser = secondTournament[0];
  for(int i = 1; i < size; i++){
    if(secondTournament[i].getFitness() < winner.getFitness()){
      winner = secondTournament[i];
    }
    if(secondTournament[i].getFitness() >= loser.getFitness()){
      loser = secondTournament[i];
    }
  }
  winners[1] = winner;
  losers[1] = loser;
}



void GP::copyTestData(){
  for(int i = 0; i < TEST_DATA_SIZE; i++){
//    testData_Y[i] = TEST_DATA_A_Y[i];
  }

}
