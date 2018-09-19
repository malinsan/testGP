#include "gp.h"

#include "Instruction.h"
#include "Random.h"
#include "StringPrinter.h"
#include <math.h>
#include "HelperFunctions.h"
#include <limits.h>
#include "constants.h"
#include <cstring> //memcpy

/** ALL VARIABLES NEEDED **/
//const int POPULATION_SIZE = 20;
const int TEST_DATA_SIZE = 11;

const int MAX_GENERATIONS = 10;
//const int MAX_LENGTH = Constants::MAX_LENGTH;
const int MIN_LENGTH = 1;


//selection
const int TOURNAMENT_SIZE = 4;
const int PTOUR = 80;

//crossover
const int PCROSS = 60;

//mutation
const int PMUT = 5;

//testdata
const int TEST_DATA_A_Y[11] = {1,2,5,10,17,26,37,50,65,82,101}; // x²+1
const int TEST_DATA_B_Y[11] = {1,3,11,31,69,131,223,351,521,739,1011}; //x³+x+1
const int TEST_DATA_C_Y[11] = {1, 4, 5, 9, 12, 15, 20, 67, 89, 120, 234}; //random function

int TEST_DATA_Y[11];


//int testData_Y[TEST_DATA_SIZE] = {};
Individual population[POPULATION_SIZE] = {};

/** END OF VARIABLES **/


GP::GP(){
  this->copyTestData();
}


void GP::run(){
  StringPrinter sp;
  int numberOfGenerations = 0;

  this->createPopulation();
  this->evaluatePopulation();

  //find best individual
  Individual bestIndividual = population[0];
  for(int i = 1; i < POPULATION_SIZE; i++){
    if(population[i].getFitness() < bestIndividual.getFitness()){
      bestIndividual = population[i];
    }
  }

  char text[20] = "\rBest Individual: ";
  sp.printText(text);
  sp.printInt(bestIndividual.getFitness());

  //start generations
  while(numberOfGenerations < MAX_GENERATIONS){
    sp.printInt(numberOfGenerations);
    numberOfGenerations++;

    Individual children[2];
    this->tournamentSelection(children);

    //this->singlePointCrossover(children);
    //mutate children
    //this->mutation(children);

    //evaluate children
    for(int i = 0; i < 2; i++){
      children[i].setFitness(evaluateIndividual(children[i]));
      population[children[i].index] = children[i];
    }

  }

  //find best individual
  bestIndividual = population[0];
  for(int i = 1; i < POPULATION_SIZE; i++){
    if(population[i].getFitness() < bestIndividual.getFitness()){
      bestIndividual = population[i];
    }
  }

  //last printout
  sp.printText(text);
  sp.printInt(bestIndividual.getFitness());
  char individualString [bestIndividual.getSize() * 11];
  bestIndividual.toString(individualString);
  sp.printText(individualString);

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
  StringPrinter sp;
  for(int i = 0; i < POPULATION_SIZE; i++){
    int fitness = evaluateIndividual(population[i]);
    population[i].setFitness(fitness);
  }
}

/*
  * Calculates the fitness of an individual using MSE
*/
int GP::evaluateIndividual(Individual individualToEvaluate){
  float error = 0.0f;
  StringPrinter sp;
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    int y_result = decodeIndividual(individualToEvaluate, i);

    int y_real = TEST_DATA_Y[i];
    float y_dist = (float)abs(y_real - y_result);

    float y_sqr = pow(y_dist, 2.0f); //danger??
    //error += y_sqr;
    error += y_dist;
  }
  //error = sqrt(error / TEST_DATA_SIZE);
  //sp.printInt(error);
  return (int)error;
}

/*
  * Runs the individual instructions for one value of x and returns the result in register "a"
*/
int GP::decodeIndividual(Individual individualToDecode, int x){
                //a,b,c
  StringPrinter sp;
  int values[] = {x,0,0,-1,0,1};
  int overflowError = 10000;

  //start decoding
  for(int i = 0; i < individualToDecode.getSize(); i++){
    int result = 0;
    Instruction currentInstruction = individualToDecode.getInstructions()[i];
    int operand1 = values[currentInstruction.op1];
    int operand2 = values[currentInstruction.op2];

    switch (currentInstruction.operation) {
      case 0: // +
        if(operand2 > 0 && operand1 > INT_MAX - operand2){
          return overflowError;
        }
        result = operand1 + operand2;
        break;
      case 1: // -
        if(operand2 < 0 && operand1 < INT_MIN - operand2){
          return overflowError;
        }
        result = operand1 - operand2;
        break;
      case 2: // *
        if(operand2 != 0 && operand1 > INT_MAX / operand2){
          return overflowError;
        }
        result = operand1 * operand2;
        break;
      default:
        sp.printInt(99999);
        break;
    }
    values[currentInstruction.reg] = result; //if reg > 5 kabooom
  }
  return values[0];
}


void GP::tournamentSelection(Individual children[]){
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
  randNum.getRandomNumberArray(randomNumbers, TOURNAMENT_SIZE, 1, POPULATION_SIZE);

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

  Individual winners[2];
  Individual losers[2];

  //get winners and losers
  runTournament(firstTournament, secondTournament, winners, losers, halfTourSize);

  //copy winners to losers
  for(int i = 0; i < 2; i++){
    losers[i].setInstructions(winners[i].individualNumber);
    losers[i].setFitness(winners[i].getFitness());
    losers[i].setSize(winners[i].getSize());

    population[losers[i].index] = losers[i]; // replace losers with winners

    children[i] = winners[i];
  }
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


void GP::singlePointCrossover(Individual children[]){
  Random randNum;

  if(randNum.getRandomNumber(0,100) < PCROSS){
    //pick a crossover point
    int child1NewSize = MAX_LENGTH +1;
    int child2NewSize = MAX_LENGTH +1;

    int crossPoint1 = 0;
    int crossPoint2 = 0;

    while(child1NewSize > MAX_LENGTH || child2NewSize > MAX_LENGTH){
      crossPoint1 = randNum.getRandomNumber(1, children[0].getSize()-1);
      crossPoint2 = randNum.getRandomNumber(1, children[1].getSize()-1);

      child1NewSize = (crossPoint1) + (children[1].getSize() - crossPoint2);
      child2NewSize = (crossPoint2) + (children[0].getSize() - crossPoint1);
    }

    children[0].crossoverInstructions(crossPoint1, crossPoint2, children[1].individualNumber);
  }

}

void GP::mutation(Individual children[]){
  for(int i = 0; i < 2; i++){
    children[i].mutate(PMUT);
  }
}


void GP::copyTestData(){
  for(int i = 0; i < TEST_DATA_SIZE; i++){
    TEST_DATA_Y[i] = TEST_DATA_A_Y[i];
  }

}
