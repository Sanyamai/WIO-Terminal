#include <TFT_eSPI.h>  // ไลบรารีสำหรับควบคุมจอ TFT

TFT_eSPI tft = TFT_eSPI();

// กำหนดขา D0 สำหรับปุ่ม
#define BUTTON_PIN D0

void setup() {

  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนด D0 เป็น INPUT_PULLUP
  // เมื่อไม่กดปุ่ม = HIGH
  // เมื่อกดปุ่ม = LOW
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // เริ่มต้นจอ TFT
  tft.begin();

  // กำหนดแนวหน้าจอ
  tft.setRotation(3);

  // ล้างหน้าจอเป็นสีดำ
  tft.fillScreen(TFT_BLACK);

  // กำหนดสีตัวอักษร
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // กำหนดขนาดตัวอักษร
  tft.setTextSize(3);

  // กำหนดตำแหน่งข้อความ
  tft.setCursor(40, 70);

  // แสดงข้อความเริ่มต้น
  tft.println("ZX-Switch");

  tft.setCursor(40, 120);
  tft.println("Ready");
}

void loop() {

  // ตรวจสอบว่ามีการกดปุ่มหรือไม่
  if (digitalRead(BUTTON_PIN) == LOW) {

    // ล้างหน้าจอ
    tft.fillScreen(TFT_BLACK);

    // กำหนดสีข้อความ
    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    // กำหนดขนาดตัวอักษร
    tft.setTextSize(4);

    // กำหนดตำแหน่ง
    tft.setCursor(60, 90);

    // แสดงข้อความเมื่อกดปุ่ม
    tft.println("PRESSED");

    // แสดงข้อความใน Serial Monitor
    Serial.println("Button Pressed");

    // หน่วงเวลาเพื่อป้องกันการอ่านซ้ำ
    delay(300);
  }
}
