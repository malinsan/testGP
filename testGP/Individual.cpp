#include "Individual.h"


Individual::Individual(){
  Individual(10);
}

Individual::Individual(int length){

  for(int i = 0; i < length; i++){
    instructions[i].reg = 2;
  }
}

instruction * Individual::getInstructions(){
  return instructions;
}
