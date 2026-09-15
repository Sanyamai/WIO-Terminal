// ======================================================
// Wio Terminal + ZX-LED
// ทดสอบไฟกระพริบ
// ZX-LED SIG -> D0
// ======================================================

#define LED_PIN D0

void setup() {

  // กำหนด D0 เป็นขา OUTPUT
  pinMode(LED_PIN, OUTPUT);

}

void loop() {

  // -----------------------------
  // เปิด LED
  // -----------------------------
  digitalWrite(LED_PIN, HIGH);
  delay(500);

  // -----------------------------
  // ปิด LED
  // -----------------------------
  digitalWrite(LED_PIN, LOW);
  delay(500);

}
