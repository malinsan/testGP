#include "Individual.h"
#include "Random.h"
#include "constants.h"


Individual::Individual(){
  Individual(10);
}

Individual::Individual(int length){
  Random randN;
  instruction instructions[MAX_LENGTH] = {};

  if(length > MAX_LENGTH){
    length = MAX_LENGTH;
  }

  for(int i = 0; i < length; i++){
    instructions[i].reg = randN.getRandomNumber(0, Constants::REG_MAX);
    instructions[i].op1 = randN.getRandomNumber(0, Constants::OPERAND_MAX);
    instructions[i].op2 = randN.getRandomNumber(0, Constants::OPERAND_MAX);
    instructions[i].operation = randN.getRandomNumber(0, Constants::OPERATOR_MAX);
  }

}

instruction * Individual::getInstructions(){
  return instructions;
}
