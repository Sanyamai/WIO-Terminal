// Wio Terminal - Delay Module
// ตัวอย่าง: เปิด 3 วินาที / ปิด 3 วินาที

#define DELAY_PIN BCM0

void setup() {
  pinMode(DELAY_PIN, OUTPUT);

  // เริ่มต้นปิด
  digitalWrite(DELAY_PIN, LOW);
}

void loop() {

  // เปิด
  digitalWrite(DELAY_PIN, HIGH);
  delay(3000);

  // ปิด
  digitalWrite(DELAY_PIN, LOW);
  delay(3000);
}
