#ifndef FLASHWRITER_H
#define FLASHWRITER_H


#include <stdint.h> //uint32_t


#define FLASH_START_ADD           ((uint32_t) 0x08080000) //sector 8
#define FLASH_END_ADD             ((uint32_t) 0x0809FFFF)

#define FLASH_TEST                ((uint32_t) 0x80803FFF)
//------------------------------------------------------------------------------


class FlashWriter{
public:
  FlashWriter();
  void writeCharArrayAsFloatToFlash(uint32_t adr, char data [], int dataSize);
  void writeFloatValueToFlash(uint32_t adr, float data);
  void writeValueToFlash(uint32_t adr, uint32_t data);

  uint32_t getValueFromFlash(uint32_t adr);
  float getValueFromFlashAsFloat(uint32_t adr);
private:

};



#endif
