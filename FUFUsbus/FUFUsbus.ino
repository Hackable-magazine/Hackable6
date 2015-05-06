#include <FUTABA_SBUS.h>

FUTABA_SBUS sBus;

void setup(){
  sBus.begin();
  Serial.begin(115200);
}

void loop(){
  sBus.FeedLine();
  if (sBus.toChannels == 1){
    sBus.UpdateServos();
    sBus.UpdateChannels();
    sBus.toChannels = 0;
    Serial.println("-------");
    for(int i=0; i<18; i++) {
      Serial.print("Channel ");
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(sBus.channels[i]);
      Serial.println("");
    }
  }
}
