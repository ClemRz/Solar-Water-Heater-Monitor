/*
 *  Copyright (C) 2017 Clément Ronzon
 *
 *  This file is part of SolarWaterHeaterMonitor.
 *
 *  SolarWaterHeaterMonitor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SolarWaterHeaterMonitor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SolarWaterHeaterMonitor.  If not, see <http://www.gnu.org/licenses/>.
 */


/*
 * When deploying a new version remember to flash the ESP8266's code and update the 4 gauges in the Widgy Widget
 */

const SPREADSHEET_ID = '';

function doGet(event) {
    let report = "{}",
        spreadSheet = SpreadsheetApp.openById(SPREADSHEET_ID);
    try {
        report = getReport(spreadSheet);
    } catch (e) {
        Logger.log(e);
    }
    return ContentService.createTextOutput(report).setMimeType(ContentService.MimeType.CSV);
}

function doPost(event) {
    let spreadSheet = SpreadsheetApp.openById(SPREADSHEET_ID);
    try {
        logToSpreadsheet(spreadSheet, event.parameter);
    } catch (e) {
        Logger.log(e);
    }
    return ContentService.createTextOutput(getRate(spreadSheet)).setMimeType(ContentService.MimeType.TEXT);
}

function getReport(spreadSheet) {
    let sheet = spreadSheet.getSheetByName('report'),
        data = sheet.getRange('B2:E4').getValues();
    return data.map((x) => x.join(",")).join("\n");
}

function getRate(spreadSheet) {
    let sheet = spreadSheet.getSheetByName('config');
    return sheet.getRange('B2').getValue(); // Rate
}

function logToSpreadsheet(spreadSheet, data) {
    let sheet = spreadSheet.getSheetByName('data'),
        row = [new Date()];

    for (let key in data) {
        if (!data.hasOwnProperty(key) || data[key] === '') continue;
        let value = data[key];
        if (key.toLowerCase().indexOf('csv') > -1) {
            value = value.split(',');
            for (let i = 0; i < value.length; i++) {
                if (value[i] !== '') {
                    row.push(value[i]);
                }
            }
        } else {
            row.push(value);
        }
    }
    try {
        sheet.appendRow(row);
    } catch (e) {
        sheet.deleteRows(1, 1); // Delete 1st row
        sheet.appendRow(row); // Retry
    }
}
