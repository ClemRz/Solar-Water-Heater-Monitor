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

 void performReadings(void) {
  _readings.ambientCelsiusHundredths = getAmbientCelsiusHundredths();
  _readings.ambientHumidityPercent = getAmbientHumidityPercent();
  _readings.inputCelsiusHundredths = getInputCelsiusHundredths();
  _readings.outputCelsiusHundredths = getOuptuCelsiusHundredths();
#if DEBUG
  printReadings();
#endif
 }

int getAmbientCelsiusHundredths(void) {
  return _si7021.getCelsiusHundredths();
}

int getAmbientHumidityPercent(void) {
  return _si7021.getHumidityPercent();
}

int getInputCelsiusHundredths(void) {
  return analogRead(INPUT_THERMISTOR);
}

int getOuptuCelsiusHundredths(void) {
  return analogRead(OUTPUT_THERMISTOR);
}

