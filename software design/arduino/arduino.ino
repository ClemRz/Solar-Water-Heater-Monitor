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

#include <avr/sleep.h>
#include <Wire.h>
#include <SI7021.h>               // https://github.com/mlsorensen/SI7021
#include "structures.h"           // https://github.com/ClemRz/Introduction-to-IoT#use-structures

// General
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

// Pins
#define INPUT_THERMISTOR          A0
#define OUTPUT_THERMISTOR         A1

// Global variables
SI7021 _si7021;
Readings _readings;

void setup(void) {
#if DEBUG
  initSerial();
#endif
  initI2C();
  initSensors();
  performReadings();
}

void loop(void) {}
