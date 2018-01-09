function doGet(event) {
  const SECOND = 1;
  const MINUTE = 60 * SECOND;
  const HOUR = 60 * MINUTE;
  const DAY = 24 * HOUR;
  const WEEK = 7 * DAY;
  
  var _spreadsheetId = 'YOUR SPREADSHEET ID',
      _externalUrl = 'https://api.thingspeak.com/update?api_key=YOUR-API-KEY',
      _checkInRate = 1 * MINUTE;
  try {
    logToSpreadsheet(_spreadsheetId, event.parameter, _checkInRate);
  } catch (e) {
    Logger.log(e);
  }
  logToExternalWebsite(_externalUrl, event.parameter);
  return ContentService.createTextOutput(_checkInRate);
}

function logToSpreadsheet(spreadsheetId, data, rate) {
  var ss = SpreadsheetApp.openById(spreadsheetId),
      sheet = ss.getSheetByName('data'),
      row = [new Date()];

  for (var key in data) {
    if (!data.hasOwnProperty(key) || data[key] === '') continue;
    var value = data[key];
    if (key.toLowerCase().indexOf('csv') > -1) {
      value = value.split(',');
      for (var i = 0; i < value.length; i ++) {
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
    sheet.deleteRows(1, Math.round(24 * 3600 / rate)); //Delete 1 day worth of values, starting row #1
    sheet.appendRow(row);
  }
}

function logToExternalWebsite(url, data) {
  var params = '';
  var i = 1;
  for (var key in data) {
    if (!data.hasOwnProperty(key) || data[key] === '') continue;
    var value = data[key];
    if (key.toLowerCase().indexOf('csv') > -1) {
      value = value.split(',');
      for (var j = 0; j < value.length; j ++) {
        if (value[j] !== '') {
          params += '&field' + i + '=' + value[j];
        }
        i++;
      }
    } else {
      params += '&field' + i + '=' + value;
      i++;
    }
  }
  UrlFetchApp.fetch(url + params);
}
