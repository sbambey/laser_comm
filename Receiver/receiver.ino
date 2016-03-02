#include "constants.h"

long start;
long finish;

int readings[8];

void setup() {
  //pinMode(PHOTO_DIODE, INPUT);
}

void loop() {
  //Serial.println(analogRead(PHOTO_DIODE));
  for(int i=0; i<8; i++) {
    while(analogRead(PHOTO_DIODE) < 454);
    start = micros();
    while(analogRead(PHOTO_DIODE) >= 454) {
      delayMicroseconds(1);
    }
    readings[i] = micros()-start;
    //delay(2000);
    //readings[i] = analogRead(PHOTO_DIODE);
  }
  Serial.begin(9600);
  for(int i=0; i<8; i++) {
    Serial.println(readings[i]);
  }
  Serial.println("---------------");
  Serial.end();
  delay(5000);
}
