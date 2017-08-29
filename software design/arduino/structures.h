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

#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#define REG_INT_SIZE              4
#define REG_BYTE_SIZE             REG_INT_SIZE*2 // Size of the register (consider nuber of bytes)

typedef struct {
  union {
    byte byteAt[REG_BYTE_SIZE];
    int intAt[REG_INT_SIZE];
    struct {
      int ambientCelsiusHundredths;
      int ambientHumidityPercent;
      int inputCelsiusHundredths;
      int outputCelsiusHundredths;
    };
  };
} Readings;

#endif  //_STRUCTURES_H
