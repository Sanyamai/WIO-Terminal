#include <Wire.h>
#include <TFT_eSPI.h>
#include <Adafruit_MLX90614.h>

// =====================================================
// Objects
// =====================================================
TFT_eSPI tft = TFT_eSPI();
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// =====================================================
// Setup
// =====================================================
void setup() {

  Serial.begin(115200);
  delay(1000);

  // ---------------------------------------------------
  // I2C
  // Wio Terminal ใช้ I2C ของบอร์ด
  // ---------------------------------------------------
  Wire.begin();

  // ---------------------------------------------------
  // TFT
  // ---------------------------------------------------
  tft.begin();
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(20, 20);
  tft.println("MLX90614");

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(20, 50);
  tft.println("Infrared Thermometer");

  // ---------------------------------------------------
  // MLX90614
  // ---------------------------------------------------
  if (!mlx.begin()) {

    Serial.println("MLX90614 NOT FOUND!");

    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(20, 100);
    tft.println("MLX90614 ERROR");

    tft.setCursor(20, 130);
    tft.println("Check wiring!");

    while (1) {
      delay(1000);
    }
  }

  Serial.println("MLX90614 OK");

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(20, 100);
  tft.println("Sensor OK");

  delay(1500);

  tft.fillScreen(TFT_BLACK);
}

// =====================================================
// Loop
// =====================================================
void loop() {

  // ---------------------------------------------------
  // Read temperature
  // ---------------------------------------------------
  float ambientTemp = mlx.readAmbientTempC();
  float objectTemp  = mlx.readObjectTempC();

  // ---------------------------------------------------
  // Serial Monitor
  // ---------------------------------------------------
  Serial.println("==========================");
  Serial.print("Ambient : ");
  Serial.print(ambientTemp, 2);
  Serial.println(" C");

  Serial.print("Object  : ");
  Serial.print(objectTemp, 2);
  Serial.println(" C");

  // ---------------------------------------------------
  // TFT
  // ---------------------------------------------------
  tft.fillScreen(TFT_BLACK);

  // Title
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(3);

  tft.setCursor(20, 20);
  tft.println("MLX90614");

  // Line
  tft.drawLine(
    20, 60,
    300, 60,
    TFT_DARKGREY
  );

  // Ambient
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(20, 85);
  tft.println("Ambient");

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextSize(4);

  tft.setCursor(20, 115);
  tft.print(ambientTemp, 1);
  tft.println(" C");

  // Object
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(20, 175);
  tft.println("Object");

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(4);

  tft.setCursor(20, 205);
  tft.print(objectTemp, 1);
  tft.println(" C");

  // ---------------------------------------------------
  // Update every 1 second
  // ---------------------------------------------------
  delay(1000);
}
