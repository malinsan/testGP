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

const int maxL = 10;
Instruction listOfInstructions[5][maxL] = {}; //population * maxlength
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
    k++;
    listOfInstructionsIndex++;
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
