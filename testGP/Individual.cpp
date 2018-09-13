#include "Individual.h"
#include "Random.h"
#include "constants.h"


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
    instructions[i].reg = randN.getRandomNumber(0, Constants::REG_MAX);
    instructions[i].op1 = randN.getRandomNumber(0, Constants::OPERAND_MAX);
    instructions[i].op2 = randN.getRandomNumber(0, Constants::OPERAND_MAX);
    instructions[i].operation = randN.getRandomNumber(0, Constants::OPERATOR_MAX);
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
