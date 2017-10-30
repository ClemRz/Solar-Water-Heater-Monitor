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
  for(uint8_t t = 2; t > 0; t--) {
    Serial.println(F("Boot wait"));
    Serial.flush();
    delay(1000);
  }
}

void initI2C(void) {
  Wire.begin();
}

void initSlave(void) {
  pinMode(SLAVE_PING, OUTPUT);
  digitalWrite(SLAVE_PING, HIGH);
}

void initWiFi(void) {
  int attempts = 0;
#if DEBUG
  Serial.println(F("Start WiFi"));
#endif
  WiFi.persistent(true);
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED && attempts <= MAX_WIFI_ATTEMPTS) {
      yield();
#if DEBUG
      Serial.print(F("."));
#endif
      attempts ++;
      delay(WIFI_REINTENT_DELAY);
    }
  }
#if DEBUG
  Serial.println();
  if (attempts > MAX_WIFI_ATTEMPTS) {
    Serial.print(F("Failed to connect to "));
    Serial.println(SSID);
  } else {
    Serial.print(F("Connected to "));
    Serial.println(SSID);
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
    Serial.print(F("Mac addresss: "));
    Serial.println(WiFi.macAddress());
  }
#endif
  if (attempts > MAX_WIFI_ATTEMPTS) sleep();
}
