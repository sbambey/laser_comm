void cycle(int pin, long period) {
  digitalWrite(pin, LOW);
  delayMicroseconds(comm_period);
  digitalWrite(pin, HIGH);
  delayMicroseconds(comm_period);
}

