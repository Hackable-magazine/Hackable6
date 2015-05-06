#include <EEPROM.h>

byte mesdata[16] =
  {42,15,78,95,
   69,25,17,13,
   74,19,06,18,
   66,93,86,12};

void setup() {
  for(int i=0; i<16; i++) {
    EEPROM.write(i,mesdata[i]);
  }
}

void loop() {
}
