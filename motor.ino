#include <TFT_eSPI.h>

TFT_eSPI tft;

// =====================
// DC MOTOR 1 ตัว
// =====================
#define MOTOR_IN1 BCM2
#define MOTOR_IN2 BCM3
#define MOTOR_PWM BCM4


// =====================
// แสดงข้อความบน TFT
// =====================
void showStatus(String text)
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("DC MOTOR", 100, 20);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextSize(3);
  tft.drawString(text, 70, 70);
}


// =====================
// เดินหน้า
// =====================
void forward(int speed)
{
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_PWM, speed);
}


// =====================
// ถอยหลัง
// =====================
void backward(int speed)
{
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  analogWrite(MOTOR_PWM, speed);
}


// =====================
// หยุด
// =====================
void stopMotor()
{
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_PWM, 0);
}


void setup()
{
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

  // TFT
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  showStatus("READY");

  delay(2000);
}


void loop()
{
  // =====================
  // เดินหน้า
  // =====================
  showStatus("FORWARD");

  forward(200);

  delay(3000);


  // =====================
  // หยุด
  // =====================
  showStatus("STOP");

  stopMotor();

  delay(1000);


  // =====================
  // ถอยหลัง
  // =====================
  showStatus("BACKWARD");

  backward(200);

  delay(3000);


  // =====================
  // หยุด
  // =====================
  showStatus("STOP");

  stopMotor();

  delay(1000);
}
