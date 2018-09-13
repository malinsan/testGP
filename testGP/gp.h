/**
* GP has a population, created during run() and performs different operations
  upon this population such as crossover, mutation and checking fitness.

*/

#ifndef GP_H
#define GP_H

#include "Individual.h"
#include "constants.h"

class GP {
public:
  void run();
  GP();
private:
  void createPopulation();
  int evaluateIndividual(Individual individualToEvaluate);
  void evaluatePopulation();
  Individual population[POPULATION_SIZE];

  int testDataSize;
  int testData_Y[TEST_DATA_SIZE];
  void copyTestData();
  /*
  * TO-DO rest of functions needed for gp
  */
};

#endif
