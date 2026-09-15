#include <TFT_eSPI.h>

// ======================================================
// Wio Terminal
// Soil Moisture Sensor + RYG LED + TFT
// ======================================================

TFT_eSPI tft = TFT_eSPI();


// ======================================================
// กำหนดขา Soil Moisture
// ======================================================

// BCM22 ของ Soil Moisture ต่อเข้ากับ BCM22
#define SOIL_PIN BCM22


// ======================================================
// กำหนดขา LED RYG
// ======================================================

#define RED_LED     BCM2
#define YELLOW_LED  BCM3
#define GREEN_LED   BCM4


// ======================================================
// CALIBRATION
// ======================================================
//
// ต้องนำค่าจริงจาก Serial Monitor มาใส่
//
// DRY_VALUE = ค่าเมื่อเซ็นเซอร์แห้ง
// WET_VALUE = ค่าเมื่อเซ็นเซอร์เปียก/จุ่มน้ำ
//
// ตัวอย่าง:
// แห้ง = 850
// เปียก = 500
//
// ======================================================

#define DRY_VALUE 850
#define WET_VALUE 500


// ======================================================
// กำหนดระดับความชื้น
// ======================================================

#define DRY_PERCENT     30
#define WET_PERCENT     70


// ======================================================
// SETUP
// ======================================================

void setup() {

  // เปิด Serial Monitor
  Serial.begin(115200);


  // Soil Sensor
  pinMode(SOIL_PIN, INPUT);


  // LED
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);


  // ====================================================
  // เริ่มต้น TFT
  // ====================================================

  tft.begin();

  // แนวนอน
  tft.setRotation(3);

  // พื้นหลังสีดำ
  tft.fillScreen(TFT_BLACK);

  // จัดข้อความตรงกลาง
  tft.setTextDatum(MC_DATUM);


  // ====================================================
  // หัวข้อ
  // ====================================================

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "SOIL MOISTURE",
    160,
    25,
    4
  );


  // ปิด LED ตอนเริ่มต้น
  allLEDOff();

  delay(1000);
}


// ======================================================
// LOOP
// ======================================================

void loop() {

  // ====================================================
  // อ่านค่า Sensor
  // ====================================================

  int soilValue = analogRead(SOIL_PIN);


  // ====================================================
  // แปลงค่า Analog เป็น %
  // ====================================================
  //
  // DRY_VALUE = 0%
  // WET_VALUE = 100%
  //
  // map() จะคำนวณค่าระหว่างสองจุด
  // ====================================================

  int moisturePercent = map(
    soilValue,
    DRY_VALUE,
    WET_VALUE,
    0,
    100
  );


  // จำกัดค่าไม่ให้ต่ำกว่า 0
  // และไม่ให้มากกว่า 100

  moisturePercent = constrain(
    moisturePercent,
    0,
    100
  );


  // ====================================================
  // Serial Monitor
  // ====================================================

  Serial.print("Raw Value = ");
  Serial.print(soilValue);

  Serial.print(" | Moisture = ");
  Serial.print(moisturePercent);

  Serial.println("%");


  // ====================================================
  // ล้างพื้นที่ TFT
  // ====================================================

  tft.fillRect(
    0,
    60,
    320,
    180,
    TFT_BLACK
  );


  // ====================================================
  // แสดงค่า RAW
  // ====================================================

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "RAW VALUE",
    160,
    75,
    2
  );


  char rawText[20];

  sprintf(
    rawText,
    "%d",
    soilValue
  );


  tft.drawString(
    rawText,
    160,
    105,
    4
  );


  // ====================================================
  // แสดง % ความชื้น
  // ====================================================

  char moistureText[20];

  sprintf(
    moistureText,
    "%d%%",
    moisturePercent
  );


  tft.drawString(
    moistureText,
    160,
    140,
    6
  );


  // ====================================================
  // ตรวจสอบระดับความชื้น
  // ====================================================


  // ====================================================
  // 🔴 แห้ง
  // ====================================================

  if (moisturePercent < DRY_PERCENT) {

    // เปิด RED
    digitalWrite(
      RED_LED,
      HIGH
    );

    // ปิด YELLOW
    digitalWrite(
      YELLOW_LED,
      LOW
    );

    // ปิด GREEN
    digitalWrite(
      GREEN_LED,
      LOW
    );


    // สีข้อความแดง
    tft.setTextColor(
      TFT_RED,
      TFT_BLACK
    );


    // สถานะ
    tft.drawString(
      "DRY",
      160,
      195,
      4
    );
  }


  // ====================================================
  // 🟡 ความชื้นปานกลาง
  // ====================================================

  else if (moisturePercent < WET_PERCENT) {

    // ปิด RED
    digitalWrite(
      RED_LED,
      LOW
    );

    // เปิด YELLOW
    digitalWrite(
      YELLOW_LED,
      HIGH
    );

    // ปิด GREEN
    digitalWrite(
      GREEN_LED,
      LOW
    );


    // สีข้อความเหลือง
    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );


    // สถานะ
    tft.drawString(
      "MEDIUM",
      160,
      195,
      4
    );
  }


  // ====================================================
  // 🟢 ชื้น
  // ====================================================

  else {

    // ปิด RED
    digitalWrite(
      RED_LED,
      LOW
    );

    // ปิด YELLOW
    digitalWrite(
      YELLOW_LED,
      LOW
    );

    // เปิด GREEN
    digitalWrite(
      GREEN_LED,
      HIGH
    );


    // สีข้อความเขียว
    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );


    // สถานะ
    tft.drawString(
      "WET",
      160,
      195,
      4
    );
  }


  // อ่านค่าใหม่ทุก 500 ms
  delay(500);
}


// ======================================================
// ฟังก์ชันปิด LED ทั้งหมด
// ======================================================

void allLEDOff() {

  digitalWrite(
    RED_LED,
    LOW
  );

  digitalWrite(
    YELLOW_LED,
    LOW
  );

  digitalWrite(
    GREEN_LED,
    LOW
  );
}
