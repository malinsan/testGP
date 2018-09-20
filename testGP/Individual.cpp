#include "Individual.h"
#include "Random.h"
#include "StringPrinter.h"
#include "HelperFunctions.h"
#include <stdio.h>
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

static Instruction listOfInstructions[POPULATION_SIZE][MAX_LENGTH] = {}; //population * maxlength
static int numberOfIndividuals = 0;
static int numberOfCrossovers = 0;

Individual::Individual(){
  //for when creating children
  //Individual(10);
}

Individual::Individual(int length){
  Random randN;
  StringPrinter sp;

  this->index = 0;
  this->fitness = 10000;
  this->size = length;
  this->individualNumber = numberOfIndividuals;

  for(int i = 0; i < length; i++){
    listOfInstructions[individualNumber][i].reg = randN.getRandomNumber(0, REG_MAX);
    listOfInstructions[individualNumber][i].op1 = randN.getRandomNumber(0, OPERAND_MAX);
    listOfInstructions[individualNumber][i].operation = randN.getRandomNumber(0, OPERATOR_MAX);
    listOfInstructions[individualNumber][i].op2 = randN.getRandomNumber(0, OPERAND_MAX);
  }


  numberOfIndividuals++;
}

Instruction* Individual::getInstructions(){
  return listOfInstructions[this->individualNumber];
}

/*
* Used for copying the instructions of one individual to another
*/
void Individual::setInstructions(int listOfInstructionsIndex){
  int k = this->individualNumber;
  for(int i = 0; i < MAX_LENGTH; i++){
    listOfInstructions[k][i] = listOfInstructions[listOfInstructionsIndex][i];
  }
}

void Individual::crossoverInstructions(int crossPoint, Individual otherIndividual){
  numberOfCrossovers++;

  StringPrinter sp;
  //save instructions of this individual
  Instruction savedInstructions [this->size];
  for(int i = 0; i < this->size; i++){
    savedInstructions[i] = listOfInstructions[this->individualNumber][i];
  }

  for(int i = crossPoint; i < otherIndividual.getSize(); i++){
    listOfInstructions[this->individualNumber][i] = listOfInstructions[otherIndividual.individualNumber][i];
  }

  for(int i = crossPoint; i < this->size; i++){
    listOfInstructions[otherIndividual.individualNumber][i] = savedInstructions[i];
  }

  int tmpSize = this->size;
  this->size = otherIndividual.getSize();
  otherIndividual.setSize(tmpSize);

}

void Individual::mutate(int pMut){
  StringPrinter sp;
  Random randNum;
  for(int i = 0; i < this->size; i++){
    Instruction currentInstruction = listOfInstructions[this->individualNumber][i];
    for(int i = 0; i < 4; i++){ //reg, op1, operator, op2,
      if(randNum.getRandomNumber(0,100) < pMut){
        switch(i){
          case 0:
            currentInstruction.reg = randNum.getRandomNumber(0, REG_MAX);
            break;
          case 1:
            currentInstruction.op1 = randNum.getRandomNumber(0, OPERAND_MAX);
            break;
          case 2:
            currentInstruction.operation = randNum.getRandomNumber(0, OPERATOR_MAX);
            break;
          case 3:
            currentInstruction.op2 = randNum.getRandomNumber(0, OPERAND_MAX);
            break;
        }
      }
    }
    listOfInstructions[this->individualNumber][i] = currentInstruction;
  }

}

void Individual::toString(char individualString []){
  StringPrinter sp;
  sprintf(individualString, "\r");
  for(int i = 0; i < this->size; i++){
    Instruction currentInstruction = listOfInstructions[this->individualNumber][i];

    char currentInstructionString[20];

    getRegChar(currentInstruction.reg, currentInstructionString);
    getOperandChar(currentInstruction.op1, currentInstructionString);
    getOperationChar(currentInstruction.operation, currentInstructionString);
    getOperandChar(currentInstruction.op2, currentInstructionString);

    sprintf(individualString, "%s %s \r",individualString, currentInstructionString);
  }
}

int Individual::getSize(){
  return size;
}

void Individual::setSize(int size){
  this->size = size;
}

int Individual::getFitness(){
  return fitness;
}

void Individual::setFitness(int fitness){
  this->fitness = fitness;
}

int Individual::getNumberOfCrossovers(){
  return numberOfCrossovers;
}
