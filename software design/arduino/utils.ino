void printReadings(void) {
  int reading;
  for (int i=0; i<READINGS_SIZE; i++) {
    if (i % 2 == 0) {
      reading = _readings.byteAt[i];
    } else {
      reading |= _readings.byteAt[i] << 8;
      Serial.print(F("_readings[")); Serial.print(i); Serial.print(F("] = ")); Serial.println(reading);
    }
  }
}

