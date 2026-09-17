function testWioData() {

  try {

    // -----------------------------------------------
    // Google Spreadsheet
    // -----------------------------------------------

    const ss =
      SpreadsheetApp.getActiveSpreadsheet();


    // -----------------------------------------------
    // Sheet
    // -----------------------------------------------

    const sheet =
      ss.getSheetByName('Sheet1') ||
      ss.getSheets()[0];


    // -----------------------------------------------
    // จำลองข้อมูลจาก Wio Terminal
    // -----------------------------------------------

    const temperature = 30.5;
    const humidity = 70.2;
    const device = 'TEST';


    // -----------------------------------------------
    // บันทึกข้อมูล
    // -----------------------------------------------

    sheet.appendRow([
      new Date(),
      temperature,
      humidity,
      device
    ]);


    // -----------------------------------------------
    // Log
    // -----------------------------------------------

    Logger.log(
      'Wio test data saved successfully'
    );


    return 'OK';


  } catch (error) {

    Logger.log(
      'ERROR: ' + error.toString()
    );


    return (
      'ERROR: ' +
      error.toString()
    );

  }

}
