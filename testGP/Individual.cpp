#include "Individual.h"
#include "Random.h"
#include "constants.h"


Individual::Individual(){
  Individual(10);
}

Individual::Individual(int length){
  Random randN;

  for(int i = 0; i < length; i++){
    instructions[i].reg = randN.getRandomNumber(0, Constants::REG_MAX);
  }
}

instruction * Individual::getInstructions(){
  return instructions;
}
