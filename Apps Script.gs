function doGet(e) {

  const sheet = SpreadsheetApp
    .getActiveSpreadsheet()
    .getSheets()[0];

  const temperature = e.parameter.temperature || "";
  const humidity = e.parameter.humidity || "";
  const device = e.parameter.device || "Wio Terminal";

  sheet.appendRow([
    new Date(),
    temperature,
    humidity,
    device
  ]);

  return ContentService
    .createTextOutput("OK");
}
