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

String httpsPost(void) {
  HTTPSRedirect* client = new HTTPSRedirect(HTTPS_PORT);
  client->setInsecure();
  bool connected = false;
  int attemps = 0;
  while (!connected && attemps < MAX_HTTPS_ATTEMPTS) {
    yield();
    if (client->connect(HOST, HTTPS_PORT) == 1) {
       connected = true;
       break;
#if DEBUG
    } else {
      Serial.println(F("Connection failed. Retrying..."));
#endif
    }
    attemps ++;
    delay(HTTPS_REINTENT_DELAY*MILLISEC);
  }

  if (!connected) {
#if DEBUG
    Serial.print(F("Could not connect to server"));
    Serial.println(HOST);
#endif
    return "";
  }
  
  String url = String(URL) + "?valCsv=";
  for (int i = 0; i < REG_INT_SIZE; i ++) url += String(_readings.intAt[i]) + "%2C";
#if DEBUG
    Serial.print(F("URL: ")); Serial.println(url);
#endif
  if (client->POST(url, HOST, "")) {
    String payload = client->getResponseBody();
#if DEBUG
    Serial.println(F("HTTP Response: "));
    Serial.println(payload);
#endif
    return payload;
  } else {
#if DEBUG
    Serial.print(F("Couldn't get the body, code: ")); Serial.print(client->getStatusCode()); Serial.print(F(", message: ")); Serial.println(client->getReasonPhrase());
#endif
    return "";
  }
  
  delete client;
  client = nullptr;
}
