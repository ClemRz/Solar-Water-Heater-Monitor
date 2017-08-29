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

#include <ESP8266WiFi.h>          // https://github.com/esp8266/Arduino/
#include <Wire.h>                 // https://github.com/esp8266/Arduino/
#include "structures.h"           // https://github.com/ClemRz/Introduction-to-IoT#use-structures
#include "HTTPSRedirect.h"        // https://github.com/electronicsguy/ESP8266/tree/master/HTTPSRedirect

// General
#define MICROSEC                  1000000L
#define MILLISEC                  1000L
#define SEC                       1L
#define MINUTE                    (unsigned int) 60L*SEC
#define HOUR                      (unsigned int) 60L*MINUTE
#define DAY                       (unsigned long) 24L*HOUR

// Debug
#define DEBUG                     1               // Debug current sketch

// Custom settings
#define DEFAULT_POLLING_RATE      5*SEC
#define SSID                      "GENERAL"
#define PASSWORD                  "LEARNFROMYESTERDAYLIVEFORTODAY"
#define SCRIPT_ID                 "AKfycbzQfHhvTwNnsGMGTlpgQLmTLnjaEVfGweY9RI3Hl-fYb5jz6-wD"

// I2C
#define SLAVE_I2C_ADDRESS         0x09

// Pins
#define SDA                       4               // I2C data
#define SCL                       5               // I2C clock
#define SLAVE_RESET               12              // Connected to slave's RST pin

// HTTPS parameters
#define HTTPS_PORT                443
#define HOST                      "script.google.com"
#define URL                       "https://" HOST "/macros/s/" SCRIPT_ID "/exec"
#define MAX_WIFI_ATTEMPTS         15
#define MAX_HTTPS_ATTEMPTS        5
#define HTTPS_REINTENT_DELAY      2*SEC

// Deep-sleep time limit
#define MAX_SLEEP_TIME        71L*MINUTE

// Global variables
Readings _readings;
HTTPSRedirect* _client = NULL;
long _pollingRate = DEFAULT_POLLING_RATE;
int _attempts = 0;

void setup() {
#if DEBUG
  initSerial();
Serial.println(sizeof(int));
#endif
  initI2C();
  initSlave();
  delay(2*SEC*MILLISEC);
  while(!requestReadings()) yield();
#if DEBUG
  printReadings();
#endif
  initWiFi();
}

void loop() {
  if (_attempts <= MAX_WIFI_ATTEMPTS) {
    _attempts = 0;
    String response = httpsGet();
    if (response != "") {
      _pollingRate = response.toInt();
    } // else saveToSpiffs();
  } // else saveToSpiffs();
  sleep();
}
