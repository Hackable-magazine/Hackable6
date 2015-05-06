#include <EEPROM.h>

struct montype {
  float virgule;
  byte entier;
  char texte[16];
};

void setup() {
  Serial.begin(9600);
  
  montype mesdata;

  EEPROM.get(0, mesdata);
  Serial.println("EEPROM lue !");
  Serial.println(mesdata.virgule);
  Serial.println(mesdata.entier);
  Serial.println(mesdata.texte);

  EEPROM.get(sizeof(montype), mesdata);
  Serial.println("EEPROM lue 2 !");
  Serial.println(mesdata.virgule);
  Serial.println(mesdata.entier);
  Serial.println(mesdata.texte);

  byte valeur;
  EEPROM.get(sizeof(montype)+sizeof(mesdata.virgule), valeur);
  Serial.print(">>");
  Serial.println(sizeof(montype));
  Serial.print(">>");
  Serial.println(sizeof(montype)+sizeof(mesdata.virgule));
  Serial.print(">>");
  Serial.println(valeur);

}

void loop() {
}
