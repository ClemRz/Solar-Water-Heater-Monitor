function doGet(event) {
  const SECOND = 1;
  const MINUTE = 60 * SECOND;
  const HOUR = 60 * MINUTE;
  const DAY = 24 * HOUR;
  const WEEK = 7 * DAY;
  
  var _spreadsheetId = 'YOUR_GOOGLE_SPREADSHEET_ID',
      _checkInRate = 5 * MINUTE;
  
  logToSpreadsheet(_spreadsheetId, event.parameter);
  return ContentService.createTextOutput(_checkInRate);
}

function logToSpreadsheet(spreadsheetId, data) {
  var ss = SpreadsheetApp.openById(spreadsheetId),
      sheet = ss.getSheetByName('data'),
      row = [new Date()];

  for (var key in data) {
    if (!data.hasOwnProperty(key)) continue;
    row.push(data[key]);
  }
  sheet.appendRow(row);
}