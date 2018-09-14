#include "Individual.h"
#include "Random.h"
#include "StringPrinter.h"

/*
  * Registers:  a, b, c :
             :  0, 1, 2 :
  * Operands :  a, b, c, -1, 0, 1 :
             :  0, 1, 2,  3, 4, 5 :
  * Operators:  +, -, * :
             :  0, 1, 2 :
*/
const int REG_MAX = 2;
const int OPERAND_MAX = 5;
const int OPERATOR_MAX = 2;

Instruction listOfInstructions[5][10] = {}; //maxlength * population
int numberOfIndividuals = 0;

Individual::Individual(){
  Individual(10);
}

Individual::Individual(int length){
  Random randN;
  StringPrinter sp;

  this->size = length;

  for(int i = 0; i < length; i++){
    listOfInstructions[numberOfIndividuals][i].reg = randN.getRandomNumber(0, REG_MAX);
    listOfInstructions[numberOfIndividuals][i].op1 = randN.getRandomNumber(0, OPERAND_MAX);
    listOfInstructions[numberOfIndividuals][i].op2 = randN.getRandomNumber(0, OPERAND_MAX);
    listOfInstructions[numberOfIndividuals][i].operation = randN.getRandomNumber(0, OPERATOR_MAX);
  }

  this->individualNumber = numberOfIndividuals;
  numberOfIndividuals++;
}

Instruction* Individual::getInstructions(){
  return listOfInstructions[individualNumber];
}

int Individual::getSize(){
  return size;
}

int Individual::getFitness(){
  return fitness;
}

void Individual::setFitness(int fitness){
  this->fitness = fitness;
}
