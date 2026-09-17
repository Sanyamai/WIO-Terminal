function saveWioData(e) {

  try {

    // =================================================
    // Google Spreadsheet
    // =================================================

    const ss = SpreadsheetApp.getActiveSpreadsheet();

    const sheet =
      ss.getSheetByName('Sheet1') ||
      ss.getSheets()[0];


    // =================================================
    // รับค่าจาก Wio Terminal
    // =================================================

    const temperature =
      e.parameter.temperature || '';

    const humidity =
      e.parameter.humidity || '';

    const device =
      e.parameter.device || 'Wio Terminal';


    // =================================================
    // บันทึกข้อมูล
    // =================================================

    sheet.appendRow([
      new Date(),
      temperature,
      humidity,
      device
    ]);


    // =================================================
    // ส่งผลกลับไป Wio
    // =================================================

    return ContentService
      .createTextOutput('OK')
      .setMimeType(
        ContentService.MimeType.TEXT
      );


  } catch (error) {

    return ContentService
      .createTextOutput(
        'ERROR: ' + error.toString()
      )
      .setMimeType(
        ContentService.MimeType.TEXT
      );

  }
}
