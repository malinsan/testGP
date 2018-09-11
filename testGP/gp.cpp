#include "gp.h"


GP::GP(){

}

void GP::run(){

}


/* ###### PRIVATE ###### */

void GP::createPopulation(int populationSize){
  for(int i = 0; i < populationSize; i++){
    Individual newIndividual;
    population[i] = newIndividual;
  }
}
