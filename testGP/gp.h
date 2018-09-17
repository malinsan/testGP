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
    bool isOverflow(int values[], int size);

    //selection
    void tournamentSelection(Individual children[]);
    void runTournament(Individual firstTournament[], Individual secondTournament[],
                        Individual winners[], Individual losers[], int size);


    //crossover
    /*
    * TO-DO rest of functions needed for gp
    */
};

#endif
