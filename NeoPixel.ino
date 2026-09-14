#include <Servo.h>
#include <TFT_eSPI.h>

// สร้างออบเจ็กต์ Servo
Servo myservo;

// สร้างออบเจ็กต์สำหรับหน้าจอ Wio Terminal
TFT_eSPI tft = TFT_eSPI();


void setup() {

  // เริ่มต้นการทำงานของหน้าจอ
  tft.begin();

  // กำหนดทิศทางหน้าจอ
  tft.setRotation(3);

  // ล้างหน้าจอให้เป็นสีดำ
  tft.fillScreen(TFT_BLACK);

  // กำหนด Servo ให้ควบคุมที่ขา D9
  myservo.attach(D9);

  // เริ่มต้น Servo ที่ 20 องศา
  showServo(20);
}


void loop() {

  // หมุน Servo ไปที่ 20 องศา
  showServo(20);
  delay(2000);

  // หมุน Servo ไปที่ 90 องศา
  showServo(90);
  delay(2000);

  // หมุน Servo ไปที่ 170 องศา
  showServo(170);
  delay(2000);
}


// ฟังก์ชันสำหรับควบคุม Servo และแสดงผลบนหน้าจอ
void showServo(int angle) {

  // สั่ง Servo ไปยังมุมที่กำหนด
  myservo.write(angle);

  // ล้างหน้าจอ
  tft.fillScreen(TFT_BLACK);


  // -------------------------
  // แสดงหัวข้อ
  // -------------------------

  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(3);

  tft.setCursor(45, 25);
  tft.print("SERVO TEST");


  // -------------------------
  // แสดงค่ามุม Servo
  // -------------------------

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(6);

  tft.setCursor(70, 80);
  tft.print(angle);

  // แสดงเครื่องหมายองศา
  tft.print((char)247);


  // -------------------------
  // แสดงขาที่ใช้
  // -------------------------

  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(2);

  tft.setCursor(80, 160);
  tft.print("Servo : D9");


  // -------------------------
  // แสดงสถานะ
  // -------------------------

  tft.setTextColor(TFT_YELLOW);

  tft.setCursor(80, 190);
  tft.print("Angle : ");

  tft.print(angle);
  tft.print(" deg");
}
