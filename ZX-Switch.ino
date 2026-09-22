#include <TFT_eSPI.h>  // ไลบรารีสำหรับควบคุมจอ TFT ของ Wio Terminal

// สร้างออบเจกต์สำหรับใช้งานจอ TFT
TFT_eSPI tft = TFT_eSPI();

void setup() {

  // เริ่มต้นการสื่อสาร Serial Monitor
  Serial.begin(115200);

  // กำหนดขาของ ZX-Switch / 5-Way Switch
  // INPUT_PULLUP หมายถึง เมื่อกดสวิตช์จะอ่านค่าเป็น LOW
  pinMode(WIO_5S_UP, INPUT_PULLUP);       // ปุ่มขึ้น
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);     // ปุ่มลง
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);     // ปุ่มซ้าย
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);    // ปุ่มขวา
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);    // ปุ่มกดตรงกลาง

  // เริ่มต้นการทำงานของจอ TFT
  tft.begin();

  // กำหนดทิศทางของหน้าจอ
  tft.setRotation(3);

  // ล้างหน้าจอและกำหนดพื้นหลังเป็นสีดำ
  tft.fillScreen(TFT_BLACK);

  // กำหนดสีตัวอักษรเป็นสีขาว
  // รูปแบบคือ สีตัวอักษร, สีพื้นหลัง
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // กำหนดขนาดตัวอักษร
  tft.setTextSize(3);

  // กำหนดตำแหน่งเริ่มต้นของข้อความ
  tft.setCursor(40, 80);

  // แสดงข้อความบนหน้าจอ
  tft.println("ZX-Switch");

  // กำหนดตำแหน่งข้อความถัดไป
  tft.setCursor(40, 130);

  // แสดงสถานะเริ่มต้น
  tft.println("Ready");
}

void loop() {

  // ตรวจสอบว่ากดปุ่มขึ้นหรือไม่
  if (digitalRead(WIO_5S_UP) == LOW) {
    showMessage("UP");
  }

  // ตรวจสอบว่ากดปุ่มลงหรือไม่
  else if (digitalRead(WIO_5S_DOWN) == LOW) {
    showMessage("DOWN");
  }

  // ตรวจสอบว่ากดปุ่มซ้ายหรือไม่
  else if (digitalRead(WIO_5S_LEFT) == LOW) {
    showMessage("LEFT");
  }

  // ตรวจสอบว่ากดปุ่มขวาหรือไม่
  else if (digitalRead(WIO_5S_RIGHT) == LOW) {
    showMessage("RIGHT");
  }

  // ตรวจสอบว่ากดปุ่มตรงกลางหรือไม่
  else if (digitalRead(WIO_5S_PRESS) == LOW) {
    showMessage("PRESS");
  }

  // หน่วงเวลาเล็กน้อยเพื่อป้องกันการอ่านค่าซ้ำเร็วเกินไป
  delay(100);
}


// ฟังก์ชันสำหรับแสดงข้อความบนจอ TFT
void showMessage(const char* message) {

  // ล้างหน้าจอเป็นสีดำ
  tft.fillScreen(TFT_BLACK);

  // กำหนดสีข้อความเป็นสีฟ้า
  tft.setTextColor(TFT_CYAN, TFT_BLACK);

  // กำหนดขนาดตัวอักษร
  tft.setTextSize(3);

  // กำหนดตำแหน่งแสดงชื่ออุปกรณ์
  tft.setCursor(35, 50);

  // แสดงชื่อ ZX-Switch
  tft.println("ZX-Switch");

  // เปลี่ยนสีข้อความเป็นสีเหลือง
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);

  // ขยายขนาดข้อความคำสั่ง
  tft.setTextSize(4);

  // กำหนดตำแหน่งแสดงคำสั่ง
  tft.setCursor(50, 110);

  // แสดงคำสั่งที่ได้รับจาก ZX-Switch
  tft.println(message);

  // แสดงคำสั่งใน Serial Monitor ด้วย
  Serial.println(message);

  // หน่วงเวลาเพื่อป้องกันการกดติดซ้ำ
  delay(300);
}
