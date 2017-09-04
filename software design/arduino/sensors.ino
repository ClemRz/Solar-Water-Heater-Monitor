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
  return getTemperatureCelsiusHundredths(INPUT_THERMISTOR);
}

int getOuptuCelsiusHundredths(void) {
  return getTemperatureCelsiusHundredths(OUTPUT_THERMISTOR);
}

int getTemperatureCelsiusHundredths(int pin) {
  return (int)(getTemperatureCelsius(pin) * 100);
}

// http://www.ametherm.com/thermistor/ntc-thermistors-steinhart-and-hart-equation
double getTemperatureCelsius(int pin) {
  double logR = log(getThermistance(pin, SERIES_RESISTANCE_OHM));
  double steinhart = _A[pin];
  steinhart += _B[pin] * logR;
  steinhart += _C[pin] * pow(logR, 3);
  steinhart = 1.0 / steinhart;
  return kToC(steinhart);
}

double getThermistance(int pin, int rSeriesOhm) {
  enableThermistors();
  double thermistance = getResistance(pin, rSeriesOhm);
#if DEBUG
  Serial.print(thermistance); Serial.println(F(" Ohm"));
#endif
  disableThermistors();
  return thermistance;
}

void disableThermistors(void) {
  digitalWrite(THERMISTOR_ENABLE, LOW);
}

void enableThermistors(void) {
  digitalWrite(THERMISTOR_ENABLE, HIGH);
}

