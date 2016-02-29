#include "base.h"
#include "constants.h"

/*
 * Sync signature LOW-HIGH-LOW-HIGH
 */
void synchronize(int pin, long comm_period) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(SYNC_DELAY);
  cycle(pin, comm_period);
  cycle(pin, comm_period);
}

void setup() {
  

}

void loop() {

}
