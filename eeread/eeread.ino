#include <EEPROM.h>

byte madonnee;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  Serial.println(EEPROM.length(), DEC);
  
  for(int i=0; i<16; i++) {
    madonnee = EEPROM.read(i);
    Serial.print("[");
    Serial.print(madonnee, DEC);
    Serial.print("]");
  }
  Serial.println();
}

void loop() {
}
