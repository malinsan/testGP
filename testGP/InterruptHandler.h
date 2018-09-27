/*
* Handles the interrupt that's gotten when RX flag is set. I.e., received data
* Saves the received data in a buffer
*/

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#define NUMBER_OF_ELEMENTS_IN_ROW 6
#define ROW_SIZE                  NUMBER_OF_ELEMENTS_IN_ROW * 5 //43.56 => 5 chars
//#define ROW_SIZE_IN_BYTES         ROW_SIZE * 4 // NUMBER_OF_ELEMENTS_IN_ROW * 4 bytes
#define NUMBER_OF_ROWS         200


class InterruptHandler
{
public:
  int getSaveFlagStatus();
  void setSaveFlagStatus(bool status);
  int getNumberOfRows();
  char * getSavedDataRow(int rowNumber);
  int getRowSize(int rowNumber);

  InterruptHandler();
private:
  int convertASCIIToFloats(char data_row[], float array[], int size);

};



#endif
