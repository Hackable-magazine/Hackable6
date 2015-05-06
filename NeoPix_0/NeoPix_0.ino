#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = 
  Adafruit_NeoPixel(3, 9, NEO_RGB + NEO_KHZ800);

void setup() {
  // mise en route
  pixels.begin();
}

void loop() {
  // pixel/led en position 0 
  // 50 % de rouge, pas de vert, pas de bleu
  pixels.setPixelColor(0, pixels.Color(32,32,0));
  // envoi
  pixels.show();
}


