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

 void initSerial(void) {
  Serial.begin(9600);
  Serial.println();
}

void initLed(void) {
  pinMode(LED_BUILTIN, OUTPUT);
}

void initI2C(void) {
  Wire.begin(SLAVE_I2C_ADDRESS);
  Wire.onRequest(isrOnI2cRequest);
}

void initSensors(void) {
  initSi7021();
  initThermistors();
  _A[THERMISTOR_2] = A2;
  _B[THERMISTOR_2] = B2;
  _C[THERMISTOR_2] = C2;
  _A[THERMISTOR_3] = A3;
  _B[THERMISTOR_3] = B3;
  _C[THERMISTOR_3] = C3;
}

void initSi7021(void) {
  _si7021.begin();
}

void initThermistors(void) {
  analogReference(DEFAULT);
  pinMode(MASTER_PING, INPUT_PULLUP);
  pinMode(INPUT_THERMISTOR, INPUT);
  pinMode(OUTPUT_THERMISTOR, INPUT);
  pinMode(THERMISTOR_ENABLE, OUTPUT);
  disableThermistors();
}

