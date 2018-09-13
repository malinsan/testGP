#include "Individual.h"
#include "Random.h"
#include "constants.h"

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

Instruction instructions[MAX_LENGTH] = {};

Individual::Individual(){
  Individual(10);
}

Individual::Individual(int length){
  Random randN;

  if(length > MAX_LENGTH){
    length = MAX_LENGTH;
  }

  this->size = length;
  for(int i = 0; i < length; i++){
    instructions[i].reg = randN.getRandomNumber(0, REG_MAX);
    instructions[i].op1 = randN.getRandomNumber(0, OPERAND_MAX);
    instructions[i].op2 = randN.getRandomNumber(0, OPERAND_MAX);
    instructions[i].operation = randN.getRandomNumber(0, OPERATOR_MAX);
  }

}

Instruction* Individual::getInstructions(){
  return instructions;
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
