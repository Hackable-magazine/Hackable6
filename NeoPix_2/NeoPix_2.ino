#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels =
  Adafruit_NeoPixel(3, 9, NEO_RGB + NEO_KHZ800);

void HSVtoRGB(int  *r, int *g, int *b, int h, int s, int v) {
  int c;
  long l, m, n;

  // saturation zéro, pas de couleur
  if (s == 0) {
    *r = *g = *b = v;
    return;
  }

  // chroma
  c = ((h % 60) * 255) / 60;
  h /= 60;

  // intermédiaire
  l = (v * (256 - s)) / 256;
  m = (v * (256 - (s * c) / 256)) / 256;
  n = (v * (256 - (s * (256 - c)) / 256)) / 256;

  // choix dominante
  switch (h) {
    case 0:
      *r = v; *g = n; *b = l;
      break;
    case 1:
      *r = m; *g = v; *b = l;
      break;
    case 2:
      *r = l; *g = v; *b = n;
      break;
    case 3:
      *r = l; *g = m; *b = v;
      break;
    case 4:
      *r = n; *g = l; *b = v;
      break;
    default:
      *r = v; *g = l; *b = m;
      break;
  }
}

int brocheclic = 4;
int mode=0;
int led=0;
int brocheA = 3;
int brocheB = 2;
int actuelle[3] = {0,0,0};
int derniereA = LOW;
int n = LOW;

void setup() {
  Serial.begin(115200);

  // configuration commutateur rotatif
  pinMode (brocheA,INPUT);
  pinMode (brocheB,INPUT);
  pinMode (brocheclic,INPUT);
 
  pixels.begin();
  pixels.setBrightness(32);

  // tout sur rouge
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.show();
}

int STEP=5;
 
void loop() {
  int r, v, b;
  
  if(digitalRead(brocheclic)==LOW) {
    mode++;
    if(mode>2) mode=0;
    Serial.print("mode :");
    Serial.println(mode);
    led=mode;
    
    HSVtoRGB(&r, &v, &b, actuelle[led], 255, 255);
    pixels.setPixelColor(led, pixels.Color(0, 0, 0));
    pixels.show();
    delay(150);
    pixels.setPixelColor(led, pixels.Color(r, v, b));
    pixels.show();
    delay(150);
    pixels.setPixelColor(led, pixels.Color(0, 0, 0));
    pixels.show();
    delay(150);
    pixels.setPixelColor(led, pixels.Color(r, v, b));
    pixels.show();

    while(digitalRead(brocheclic)==LOW) {}
    return;
  }
  
  n = digitalRead(brocheA);
  if ((derniereA == LOW) && (n == HIGH)) {
    if (digitalRead(brocheB) == LOW) {
      actuelle[led]-=STEP;
      if(actuelle[led]<0) actuelle[led]=359;
      HSVtoRGB(&r, &v, &b, actuelle[led], 255, 255);
      pixels.setPixelColor(led, pixels.Color(r, v, b));
      pixels.show();
    } else {
      actuelle[led]+=STEP;
      if(actuelle[led]>359) actuelle[led]=0;
      HSVtoRGB(&r, &v, &b, actuelle[led], 255, 255);
      pixels.setPixelColor(led, pixels.Color(r, v, b));
      pixels.show();
    }
  } 
  derniereA = n;
}
