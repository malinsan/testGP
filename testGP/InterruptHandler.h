#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#define FLASH_START_ADD           ((uint32_t) 0x08080000) //sector 8
#define FLASH_END_ADD             ((uint32_t) 0x0809FFFF)

class InterruptHandler
{
public:
  int getSaveFlagStatus();
  void setSaveFlagStatus(bool status);
  void saveRowsToFlash();
  float getValueFromFlash(int rowNmr, int x);
  InterruptHandler();
private:
  int convertASCIIToFloats(char data_row[], float array[], int size);
  //int writeToFlash(float array[]);

};



#endif
