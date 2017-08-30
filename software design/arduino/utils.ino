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
 
 void printReadings(void) {
  for (int i=0; i<REG_INT_SIZE; i++) {
    Serial.print(F("_readings[")); Serial.print(i); Serial.print(F("] = ")); Serial.println(_readings.intAt[i]);
  }
}

double getAverageAnalogRead(int pinToRead) {
  long runningValue = 0;
  for(int x=0; x<ANALOG_READ_SAMPLES; x++) runningValue += analogRead(pinToRead);
  return((double)runningValue/ANALOG_READ_SAMPLES);
}

double getResistance(int pin, int rSeriesKOhm) {
  return rSeriesKOhm * 1000.0 / (1023 / getAverageAnalogRead(pin) - 1);
}

double cToK(double celsius) {
  return celsius + 273.15;
}

double kToC(double kelvin) {
  return kelvin - 273.15;
}

