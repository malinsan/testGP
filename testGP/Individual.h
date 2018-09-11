#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

struct instruction {
  int register;
  int operand1;
  int operand2;
  int operator;
};

class Individual
{
  public:
    int getFitness();
    void setFitness(int fitness);
    Individual();
    Individual(int length);
  private:
    int fitness;
    instruction instructions[];
};

#endif
