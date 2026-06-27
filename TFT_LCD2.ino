#include <TFT_eSPI.h>
TFT_eSPI tft;

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("Hello Wio Terminal",20,30);
}

void loop() {

}