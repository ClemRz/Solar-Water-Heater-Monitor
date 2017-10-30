/*
    Copyright (C) 2017 Clément Ronzon

    This file is part of SolarWaterHeaterMonitor.

    SolarWaterHeaterMonitor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarWaterHeaterMonitor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarWaterHeaterMonitor.  If not, see <http://www.gnu.org/licenses/>.
 */

void pingSlave(void) {
  digitalWrite(SLAVE_PING, LOW);
  delay(1*SEC*MILLISEC);
  digitalWrite(SLAVE_PING, HIGH);
}

void requestReadings(void) {
  int attempts = 0;
  while(!requestFromSlave() && attempts <= MAX_SLAVE_ATTEMPTS) {
    yield();
    attempts ++;
    delay(SLAVE_REINTENT_DELAY*MILLISEC);
  }
  if (attempts > MAX_SLAVE_ATTEMPTS) sleep();
#if DEBUG
  printReadings();
#endif
}

bool requestFromSlave(void) {
  Wire.requestFrom(SLAVE_I2C_ADDRESS, REG_BYTE_SIZE);
  int i = 0;
  while (Wire.available()) {
    if (i < REG_BYTE_SIZE) {
      _readings.byteAt[i] = Wire.read();
      i++;
    }
  }
  return i == REG_BYTE_SIZE;
}
