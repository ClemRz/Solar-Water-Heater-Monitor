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

#include <Wire.h>                 // https://github.com/arduino/Arduino
#include <SI7021.h>               // https://github.com/mlsorensen/SI7021
#include "structures.h"           // https://github.com/ClemRz/Introduction-to-IoT#use-structures

// General
#define K                         1000
#define MICROSEC                  1000000L
#define MILLISEC                  1000L
#define SEC                       1L
#define MINUTE                    (unsigned int) 60L*SEC
#define HOUR                      (unsigned int) 60L*MINUTE
#define DAY                       (unsigned long) 24L*HOUR

// Debug
#define DEBUG                     1               // Debug current sketch

// I2C
#define SLAVE_I2C_ADDRESS         0x09

// Ping
#define DEBOUNCE_DELAY_MS         10L

// Sampling
#define ANALOG_READ_SAMPLES       8               // Number of averaged readings

// Pins
#define THERMISTOR_ENABLE         7
#define MASTER_PING               10
#define THERMISTOR_2              A1
#define THERMISTOR_3              A0
#define INPUT_THERMISTOR          THERMISTOR_2
#define OUTPUT_THERMISTOR         THERMISTOR_3

// Thermistors
#define CST_SIZE                  1 + max(INPUT_THERMISTOR, OUTPUT_THERMISTOR)
#define SERIES_RESISTANCE_OHM     2.19*K
  //without marking
#define A2                        0.0010175900000
#define B2                        0.0002663480000
#define C2                        0.0000001030690
  // Thermistor makred #3
#define A3                        0.000977495
#define B3                        0.000271468
#define C3                        0.0000000921738

// Global variables
SI7021 _si7021;
Readings _readings;
double _A[CST_SIZE], _B[CST_SIZE], _C[CST_SIZE];
unsigned long _lastDebounceTime = 0;
bool
  _lastPingState,
  _currentPingState;

void setup(void) {
#if DEBUG
  initSerial();
#endif
  initLed();
  initI2C();
  initSensors();
}

void loop(void) {
  if (debounce(MASTER_PING)) {
    turnLedOn();
    performReadings();
    turnLedOff();
  }
}

bool debounce(int pin) {
  bool ret = false, reading = digitalRead(pin);
  reading = !reading;
  if (reading != _lastPingState) _lastDebounceTime = millis();

  if ((millis() - _lastDebounceTime) > DEBOUNCE_DELAY_MS && reading != _currentPingState) {
    _currentPingState = reading;
    ret = reading;
  }

  _lastPingState = reading;
  return ret;
}
