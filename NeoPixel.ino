#include <Adafruit_NeoPixel.h>

// กำหนดขาพอร์ต D0 สำหรับติดต่อกับ NeoPixel
#define PIN D0

// กำหนดจำนวนดวง LED RGB ที่ใช้งาน
#define NUMPIXELS 12

// สร้างออบเจ็กต์ pixels เพื่อควบคุมการแสดงผล
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
  NUMPIXELS,
  PIN,
  NEO_GRB + NEO_KHZ800
);

void setup()
{
  // เริ่มต้นกระบวนการทำงานของ LED RGB
  pixels.begin();

  // กำหนดค่าความสว่างระดับ 10 (ช่วง 0–255)
  pixels.setBrightness(10);

  // ปรับปรุงการแสดงผลล่าสุดของ LED
  pixels.show();
}

void loop()
{
  // วนแสดงผล LED ให้ครบทุกดวง
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // จับ LED แสดงแสงสีแดง
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    // ปรับปรุงการแสดงผลล่าสุดของ LED
    pixels.show();
  }

  // หน่วงเวลา 1 วินาที
  delay(1000);

  // วนแสดงผล LED ให้ครบทุกดวง
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // จับ LED แสดงแสงสีเขียว
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));

    // ปรับปรุงการแสดงผลล่าสุดของ LED
    pixels.show();
  }

  // หน่วงเวลา 1 วินาที
  delay(1000);

  // วนแสดงผล LED ให้ครบทุกดวง
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // จับ LED แสดงแสงสีน้ำเงิน
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    // ปรับปรุงการแสดงผลล่าสุดของ LED
    pixels.show();
  }

  // หน่วงเวลา 1 วินาที
  delay(1000);
}
