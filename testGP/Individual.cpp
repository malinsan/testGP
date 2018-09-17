#include "Individual.h"
#include "Random.h"
#include "StringPrinter.h"
#include "HelperFunctions.h"
#include <stdio.h>

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

const int maxL = 10;
Instruction listOfInstructions[20][maxL] = {}; //population * maxlength
int numberOfIndividuals = 0;

Individual::Individual(){
  Individual(10);
}

Individual::Individual(int length){
  Random randN;
  StringPrinter sp;

  this->index = 0;
  this->fitness = 10000;
  this->size = length;
  this->individualNumber = numberOfIndividuals;

  for(int i = 0; i < length; i++){
    listOfInstructions[numberOfIndividuals][i].reg = randN.getRandomNumber(0, REG_MAX);
    listOfInstructions[numberOfIndividuals][i].op1 = randN.getRandomNumber(0, OPERAND_MAX);
    listOfInstructions[numberOfIndividuals][i].op2 = randN.getRandomNumber(0, OPERAND_MAX);
    listOfInstructions[numberOfIndividuals][i].operation = randN.getRandomNumber(0, OPERATOR_MAX);
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
  for(int i = 0; i < maxL; i++){
    listOfInstructions[k][i] = listOfInstructions[listOfInstructionsIndex][i];
  }
}

void Individual::crossoverInstructions(int crossPoint1, int crossPoint2, int individual2){

  //save instructions
  Instruction savedInstructions [maxL];
  for(int i = 0; i < maxL; i++){
    savedInstructions[i] = listOfInstructions[this->individualNumber][i];
  }

  //overwrite instructions
  int k = crossPoint2;
  for(int i = crossPoint1; i < maxL; i++){
    listOfInstructions[this->individualNumber][i] = listOfInstructions[individual2][k];
    k++;
  }
  k = crossPoint1;
  for(int i = crossPoint2; i < maxL; i++){
    listOfInstructions[individual2][i] = savedInstructions[k];
    k++;
  }
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

void Individual::toString(char individualString [][10]){
  for(int i = 0; i < this->size; i++){
    Instruction currentInstruction = listOfInstructions[this->individualNumber][i];

    char reg = getRegChar(currentInstruction.reg);
    char op1 = getOperandChar(currentInstruction.op1);
    char op2 = getOperandChar(currentInstruction.op2);
    char operation = getOperationChar(currentInstruction.operation);

    sprintf(individualString[i], "%c = %c %c %c \r", reg, op1, operation, op2);

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
