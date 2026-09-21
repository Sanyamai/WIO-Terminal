#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define IR_PIN BCM0 // ต่อ gpio 0

void setup() {

  Serial.begin(115200);

  pinMode(IR_PIN, INPUT);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  // หัวข้อ
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(70, 25);
  tft.println("IR SENSOR");

  // Pin
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(100, 75);
  tft.println("Pin: BCM0");
}

void loop() {

  int sensorValue = digitalRead(IR_PIN);

  // ล้างพื้นที่สถานะ
  tft.fillRect(0, 110, 320, 110, TFT_BLACK);

  // =================================================
  // HIGH = พบวัตถุ
  // =================================================
  if (sensorValue == HIGH) {

    Serial.println("OBJECT DETECTED");

    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(55, 130);
    tft.println("DETECTED");

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(75, 180);
    tft.println("Object Found");
  }

  // =================================================
  // LOW = ไม่พบวัตถุ
  // =================================================
  else {

    Serial.println("NO OBJECT");

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(75, 130);
    tft.println("CLEAR");

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(80, 180);
    tft.println("No Object");
  }

  delay(100);
}
