#include <Servo.h>
#include <TFT_eSPI.h>

Servo myservo;
TFT_eSPI tft = TFT_eSPI();

void setup() {
  // เริ่มต้นหน้าจอ
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  // ตั้งค่า Servo
  myservo.attach(BCM9);

  // เริ่มที่ 20 องศา
  showServo(20);
}

void loop() {

  showServo(20);
  delay(2000);

  showServo(90);
  delay(2000);

  showServo(170);
  delay(2000);
}

void showServo(int angle) {

  // สั่ง Servo
  myservo.write(angle);

  // ล้างหน้าจอ
  tft.fillScreen(TFT_BLACK);

  // หัวข้อ
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(3);
  tft.setCursor(30, 30);
  tft.print("SERVO TEST");

  // แสดงมุม
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(5);
  tft.setCursor(70, 90);
  tft.print(angle);
  tft.print((char)247);
  tft.print("C");

  // ข้อความสถานะ
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(2);
  tft.setCursor(50, 160);
  tft.print("Servo D9");

  tft.setCursor(50, 190);
  tft.print("Angle: ");
  tft.print(angle);
  tft.print(" deg");
}
