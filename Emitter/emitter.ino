#include "constants.h"

void cycle(long period) {
  digitalWrite(LASER_VCC, LOW);
  delayMicroseconds(period);
  digitalWrite(LASER_VCC, HIGH);
  delayMicroseconds(period);
}

/*
 * Sync signature LOW-HIGH-LOW-HIGH
 */
void synchronize(int pin, long comm_period) {
  digitalWrite(pin, HIGH);
  delay(SYNC_DELAY);
  cycle(comm_period);
  cycle(comm_period);
}

void setup() {
  pinMode(LASER_VCC, OUTPUT);
  synchronize(LASER_VCC, 200);
}

void loop() {
  //synchronize(LASER_VCC, 200);
  digitalWrite(LASER_VCC, HIGH);
  delayMicroseconds(30);
  digitalWrite(LASER_VCC, LOW);
  delayMicroseconds(30);
}
