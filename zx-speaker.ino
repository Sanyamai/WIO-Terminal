// ======================================================
// Wio Terminal + ZX-Speaker
// Mario Style 8-Bit
// Speaker -> D0
// ======================================================

#define SPEAKER_PIN D0

// ======================================================
// ความถี่โน้ต
// ======================================================

#define C4  262
#define D4  294
#define E4  330
#define F4  349
#define G4  392
#define A4  440
#define B4  494

#define C5  523
#define D5  587
#define E5  659
#define F5  698
#define G5  784
#define A5  880
#define B5  988

#define C6  1047
#define D6  1175
#define E6  1319
#define G6  1568

#define REST 0

// ======================================================
// ฟังก์ชันเล่นโน้ต
// ======================================================

void playNote(int frequency, int duration) {

  if (frequency == REST) {
    noTone(SPEAKER_PIN);
    delay(duration);
  }
  else {
    tone(SPEAKER_PIN, frequency);
    delay(duration);
    noTone(SPEAKER_PIN);
  }

  // เว้นระหว่างโน้ต
  delay(20);
}

// ======================================================
// INTRO
// ======================================================

void intro() {

  playNote(E5, 120);
  playNote(E5, 120);
  playNote(REST, 100);

  playNote(E5, 120);
  playNote(C5, 120);
  playNote(E5, 120);

  playNote(G5, 220);
  playNote(REST, 120);

  playNote(G4, 180);

  playNote(REST, 200);
}

// ======================================================
// MAIN - Mario Style
// ======================================================

void marioPart1() {

  playNote(C5, 120);
  playNote(G4, 120);
  playNote(E4, 120);

  playNote(A4, 120);
  playNote(B4, 120);
  playNote(A4, 120);

  playNote(G4, 150);
  playNote(E5, 150);
  playNote(G5, 180);

  playNote(A5, 150);
  playNote(F5, 150);
  playNote(G5, 180);

  playNote(E5, 150);
  playNote(C5, 150);
  playNote(D5, 150);
  playNote(B4, 220);

  playNote(REST, 100);
}

// ======================================================
// PART 2
// ======================================================

void marioPart2() {

  playNote(C5, 130);
  playNote(G4, 130);
  playNote(E4, 130);

  playNote(A4, 130);
  playNote(B4, 130);
  playNote(A4, 130);

  playNote(G4, 130);
  playNote(E5, 130);
  playNote(G5, 180);

  playNote(A5, 130);
  playNote(F5, 130);
  playNote(G5, 180);

  playNote(E5, 130);
  playNote(C5, 130);
  playNote(D5, 130);
  playNote(B4, 250);

  playNote(REST, 150);
}

// ======================================================
// HIGH PART
// ======================================================

void highPart() {

  playNote(E5, 100);
  playNote(G5, 100);
  playNote(C6, 150);

  playNote(B5, 100);
  playNote(A5, 100);
  playNote(G5, 150);

  playNote(E5, 100);
  playNote(G5, 100);
  playNote(A5, 150);

  playNote(G5, 100);
  playNote(E5, 100);
  playNote(C5, 200);

  playNote(REST, 100);
}

// ======================================================
// GAME EFFECT
// ======================================================

void gameEffect() {

  playNote(C5, 80);
  playNote(E5, 80);
  playNote(G5, 80);
  playNote(C6, 180);

  playNote(G5, 80);
  playNote(E5, 80);
  playNote(C5, 200);

  playNote(REST, 100);
}

// ======================================================
// ENDING
// ======================================================

void ending() {

  playNote(G5, 120);
  playNote(E5, 120);
  playNote(C5, 150);

  playNote(G4, 120);
  playNote(E4, 120);
  playNote(C4, 300);

  playNote(C5, 150);
  playNote(E5, 150);
  playNote(G5, 150);
  playNote(C6, 400);

  noTone(SPEAKER_PIN);
}

// ======================================================
// SETUP
// ======================================================

void setup() {

  pinMode(SPEAKER_PIN, OUTPUT);

}

// ======================================================
// LOOP
// ======================================================

void loop() {

  // -----------------------------
  // เริ่มเพลง
  // -----------------------------
  intro();

  // -----------------------------
  // ท่อนหลัก
  // -----------------------------
  marioPart1();

  marioPart2();

  // -----------------------------
  // ท่อนเสียงสูง
  // -----------------------------
  highPart();

  // -----------------------------
  // เอฟเฟกต์เกม
  // -----------------------------
  gameEffect();

  // -----------------------------
  // เล่นท่อนหลักอีกครั้ง
  // -----------------------------
  marioPart1();

  // -----------------------------
  // จบเพลง
  // -----------------------------
  ending();

  // -----------------------------
  // พักก่อนวนใหม่
  // -----------------------------
  delay(1500);
}
