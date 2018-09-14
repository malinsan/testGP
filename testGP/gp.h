/**
* GP has a population, created during run() and performs different operations
  upon this population such as crossover, mutation and checking fitness.

*/

#ifndef GP_H
#define GP_H

#include "Individual.h"

class GP {
  public:
    void run();
    GP();
  private:
    void createPopulation();
    float evaluateIndividual(Individual individualToEvaluate);
    int decodeIndividual(Individual individualToDecode, int x);
    void evaluatePopulation();
    void copyTestData();

    //selection
    void tournamentSelection();


    /*
    * TO-DO rest of functions needed for gp
    */
};

#endif
