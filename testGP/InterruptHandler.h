#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H


class InterruptHandler
{
public:
  int getSaveFlagStatus();
  void setSaveFlagStatus(bool status);
  void saveRowsToFlash();
  InterruptHandler();
private:
  int convertASCIIToFloats(char data_row[], float array[], int size);
  int writeToFlash(float array[]);

};



#endif
