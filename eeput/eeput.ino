#include <EEPROM.h>

struct montype {
  float virgule;
  byte entier;
  char texte[16];
};

void setup() {
  Serial.begin(9600);
  
  montype mesdata = {
    3.14f,
    42,
    "Coucou monde"
  };
  
  montype mesautresdata = {
    19.06f,
    23,
    "oh un texte !"
  };

  EEPROM.put(0, mesdata);
  EEPROM.put(sizeof(montype), mesautresdata);
  Serial.println( "mesdata est en EEPROM !");
}

void loop() {
}
