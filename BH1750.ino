#include <TFT_eSPI.h>      // ผนวกไลบรารีควบคุมการแสดงผล LCD
#include "BH1750.h"        // ผนวกไลบรารีสำหรับ BH1750
#include <Wire.h>          // ผนวกไลบรารีสำหรับบัส I2C

BH1750 lightMeter;         // สร้างออบเจ็กต์ชื่อ lightMeter จากคลาส BH1750
                           // สำหรับอ่านค่าความส่องสว่างแสง

TFT_eSPI tft;              // สร้างออบเจ็กต์ชื่อ tft จากคลาส TFT_eSPI
                           // สำหรับควบคุม LCD

void setup()
{
  Wire.begin();            // เริ่มต้นการทำงานของบัส I2C

  lightMeter.begin();      // เริ่มต้นการทำงานของ BH1750

  tft.begin();             // เริ่มต้นการทำงานของ LCD

  tft.setRotation(3);      // กำหนดทิศทางการหมุนหน้าจอ LCD

  tft.setTextSize(3);      // กำหนดขนาดฟอนต์เป็น 3

  tft.fillScreen(TFT_BLACK);  // กำหนดพื้นหลังของจอแสดงผลเป็นสีดำ

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
                              // กำหนดตัวอักษรเป็นสีขาว พื้นหลังสีดำ

  tft.drawString("BH1750", 50, 30);
                              // แสดงข้อความแจ้งการทำงาน

  tft.drawString("Lux meter", 50, 80);
                              // แสดงข้อความแจ้งการทำงานบรรทัดที่สอง

  tft.setTextSize(2);       // กำหนดขนาดฟอนต์เป็น 2
}

void loop()
{
  int lux = (int)lightMeter.readLightLevel();
                              // อ่านค่าความส่องสว่างแสงมาเก็บไว้ในตัวแปร lux

  tft.drawString(
    String("Light: ") + String(lux) + String(" lx "),
    50,
    120
  );
                              // แสดงค่าความส่องสว่างแสงในหน่วย lx
}
