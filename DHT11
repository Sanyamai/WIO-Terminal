// ================================
// แสดงค่า DHT11 บนหน้าจอ TFT
// Wio Terminal
// ================================

#include <TFT_eSPI.h>
#include <DHT.h>

TFT_eSPI tft;

// กำหนดขาที่เชื่อมต่อ DHT11
#define DHTPIN D0

// กำหนดชนิดเซ็นเซอร์
#define DHTTYPE DHT11

// สร้างออบเจ็กต์ DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // เริ่มต้นเซ็นเซอร์
  dht.begin();

  // เริ่มต้นหน้าจอ TFT
  tft.begin();

  // หมุนหน้าจอเป็นแนวนอน
  tft.setRotation(3);

  // พื้นหลังสีดำ
  tft.fillScreen(TFT_BLACK);

  // กำหนดสีและขนาดตัวอักษร
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  // หัวข้อ
  tft.drawString("DHT11 Sensor", 70, 10);

}

void loop() {

  // อ่านค่าอุณหภูมิ
  float temp = dht.readTemperature();

  // อ่านค่าความชื้น
  float hum = dht.readHumidity();

  // ลบข้อมูลเดิม
  tft.fillRect(0, 50, 320, 120, TFT_BLACK);

  // แสดงอุณหภูมิ
  tft.setTextColor(TFT_RED);
  tft.drawString("Temperature", 20, 50);

  tft.setTextColor(TFT_WHITE);
  tft.drawString(String(temp) + " C", 180, 50);

  // แสดงความชื้น
  tft.setTextColor(TFT_CYAN);
  tft.drawString("Humidity", 20, 100);

  tft.setTextColor(TFT_WHITE);
  tft.drawString(String(hum) + " %", 180, 100);

  // แสดงบน Serial Monitor
  Serial.print("Temp : ");
  Serial.println(temp);

  Serial.print("Humidity : ");
  Serial.println(hum);

  delay(1000);

}
