#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <TFT_eSPI.h>
#include <DHT.h>

// =====================================================
// WiFi
// =====================================================
const char* ssid = "ชื่อฮอตสปอต WIFI";
const char* password = "รหัสฮอตสปอต WIFI";

// =====================================================
// Google Apps Script
// =====================================================
const char* googleURL =
"ใส่ลิ้งค์ App Script ตรงนี้นะจร๊ะ";

// =====================================================
// DHT11
// =====================================================
#define DHTPIN 0 //ต่อ pin 27
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// =====================================================
// TFT
// =====================================================
TFT_eSPI tft = TFT_eSPI();

// =====================================================
// Timer
// =====================================================
unsigned long lastSend = 0;

// ส่งข้อมูลทุก 10 วินาที
const unsigned long sendInterval = 10000;

// =====================================================
// Function
// =====================================================
void connectWiFi();
void sendToGoogle(float temperature, float humidity);


// =====================================================
// SETUP
// =====================================================
void setup() {

  Serial.begin(115200);
  delay(1000);

  // ===================================================
  // TFT
  // ===================================================

  tft.begin();
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);

  tft.setCursor(10, 10);
  tft.println("Wio Terminal");

  tft.setCursor(10, 40);
  tft.println("DHT11 Monitor");


  // ===================================================
  // DHT11
  // ===================================================

  dht.begin();

  delay(1000);


  // ===================================================
  // WiFi
  // ===================================================

  connectWiFi();

  delay(2000);

  tft.fillScreen(TFT_BLACK);
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  // ===================================================
  // อ่าน DHT11
  // ===================================================

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();


  // ===================================================
  // ตรวจสอบ DHT11
  // ===================================================

  if (isnan(temperature) || isnan(humidity)) {

    Serial.println();
    Serial.println("DHT11 ERROR");

    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(TFT_RED);

    tft.setCursor(10, 30);
    tft.println("DHT11 ERROR");

    delay(2000);

    return;
  }


  // ===================================================
  // SERIAL MONITOR
  // ===================================================

  Serial.println();
  Serial.println("============================");

  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(humidity, 1);
  Serial.println(" %");


  // ===================================================
  // TFT
  // ===================================================

  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);


  // ---------------------------------------------------
  // Title
  // ---------------------------------------------------

  tft.setTextColor(TFT_WHITE);

  tft.setCursor(10, 10);
  tft.println("Wio Terminal");

  tft.setCursor(10, 35);
  tft.println("DHT11");


  // ---------------------------------------------------
  // Temperature
  // ---------------------------------------------------

  tft.setCursor(10, 75);

  tft.setTextColor(TFT_WHITE);
  tft.print("Temp : ");

  tft.setTextColor(TFT_YELLOW);
  tft.print(temperature, 1);
  tft.println(" C");


  // ---------------------------------------------------
  // Humidity
  // ---------------------------------------------------

  tft.setCursor(10, 110);

  tft.setTextColor(TFT_WHITE);
  tft.print("Hum  : ");

  tft.setTextColor(TFT_CYAN);
  tft.print(humidity, 1);
  tft.println(" %");


  // ---------------------------------------------------
  // WiFi Status
  // ---------------------------------------------------

  tft.setCursor(10, 145);

  if (WiFi.status() == WL_CONNECTED) {

    tft.setTextColor(TFT_GREEN);
    tft.println("WiFi: OK");

  }
  else {

    tft.setTextColor(TFT_RED);
    tft.println("WiFi: ERROR");

    connectWiFi();
  }


  // ===================================================
  // SEND GOOGLE SHEETS
  // ===================================================

  if (millis() - lastSend >= sendInterval) {

    lastSend = millis();

    sendToGoogle(
      temperature,
      humidity
    );
  }


  delay(1000);
}


// =====================================================
// CONNECT WIFI
// =====================================================

void connectWiFi() {

  Serial.println();
  Serial.println("Connecting WiFi...");


  // ---------------------------------------------------
  // TFT
  // ---------------------------------------------------

  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);

  tft.setCursor(10, 30);
  tft.println("Connecting WiFi");


  // ---------------------------------------------------
  // Start WiFi
  // ---------------------------------------------------

  WiFi.begin(
    ssid,
    password
  );


  int count = 0;


  while (
    WiFi.status() != WL_CONNECTED &&
    count < 30
  ) {

    delay(500);

    Serial.print(".");

    count++;
  }


  Serial.println();


  // ===================================================
  // WiFi Connected
  // ===================================================

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi Connected");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());


    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_GREEN);

    tft.setCursor(10, 30);
    tft.println("WiFi CONNECTED");


    tft.setTextColor(TFT_WHITE);

    tft.setCursor(10, 65);
    tft.println(WiFi.localIP());


    delay(1500);
  }


  // ===================================================
  // WiFi Failed
  // ===================================================

  else {

    Serial.println("WiFi FAILED");


    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_RED);

    tft.setCursor(10, 30);
    tft.println("WiFi FAILED");


    delay(2000);
  }
}


// =====================================================
// SEND TO GOOGLE SHEETS
// =====================================================

void sendToGoogle(
  float temperature,
  float humidity
) {

  // ===================================================
  // ตรวจสอบ WiFi
  // ===================================================

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi not connected");

    tft.setCursor(10, 180);

    tft.setTextColor(TFT_RED);
    tft.println("Google: No WiFi");

    return;
  }


  // ===================================================
  // SERIAL
  // ===================================================

  Serial.println();
  Serial.println("================================");
  Serial.println("Sending to Google Sheets...");


  // ===================================================
  // สร้าง URL
  // ===================================================

  String url = String(googleURL);

  // สำคัญ:
  // googleURL มี ?api=sensor อยู่แล้ว
  // ดังนั้นค่าต่อไปต้องใช้ &

  url += "&temperature=";
  url += String(temperature, 1);

  url += "&humidity=";
  url += String(humidity, 1);

  url += "&device=Wio-Terminal";


  // ===================================================
  // แสดง URL
  // ===================================================

  Serial.println("URL:");
  Serial.println(url);


  // ===================================================
  // HTTPS CLIENT
  // ===================================================

  WiFiClientSecure client;

  // ไม่ตรวจสอบ Certificate
  // ใช้สำหรับทดสอบ HTTPS
  client.setCACert(nullptr);


  // ===================================================
  // HTTP CLIENT
  // ===================================================

  HTTPClient http;

  Serial.println("Starting HTTPS...");


  // ===================================================
  // BEGIN
  // ===================================================

  if (!http.begin(client, url)) {

    Serial.println("HTTP BEGIN FAILED");


    tft.setCursor(10, 180);

    tft.setTextColor(TFT_RED);
    tft.println("Google: BEGIN ERR");


    client.stop();

    return;
  }


  // ===================================================
  // Google Apps Script Redirect
  // ===================================================

  http.setFollowRedirects(
    HTTPC_FORCE_FOLLOW_REDIRECTS
  );


  // Timeout 15 วินาที
  http.setTimeout(15000);


  // ===================================================
  // GET
  // ===================================================

  Serial.println("Sending GET...");

  int httpCode = http.GET();


  // ===================================================
  // HTTP CODE
  // ===================================================

  Serial.print("HTTP CODE: ");
  Serial.println(httpCode);


  // ===================================================
  // RESPONSE
  // ===================================================

  if (httpCode > 0) {

    String response =
      http.getString();


    Serial.println();
    Serial.println("RESPONSE:");
    Serial.println(response);


    // =================================================
    // SUCCESS
    // =================================================

    if (
      response.indexOf("OK") >= 0
    ) {

      Serial.println();
      Serial.println("GOOGLE SHEETS SUCCESS");


      tft.setCursor(10, 180);

      tft.setTextColor(TFT_GREEN);

      tft.println("Google: OK");
    }


    // =================================================
    // RESPONSE ERROR
    // =================================================

    else {

      Serial.println();
      Serial.println("GOOGLE RESPONSE ERROR");


      tft.setCursor(10, 180);

      tft.setTextColor(TFT_YELLOW);

      tft.print("Google: ");
      tft.println(httpCode);
    }
  }


  // ===================================================
  // HTTP ERROR
  // ===================================================

  else {

    Serial.println();
    Serial.print("HTTPS ERROR: ");
    Serial.println(httpCode);


    tft.setCursor(10, 180);

    tft.setTextColor(TFT_RED);

    tft.print("Google ERR: ");
    tft.println(httpCode);
  }


  // ===================================================
  // CLOSE
  // ===================================================

  http.end();

  client.stop();


  tft.setTextColor(TFT_WHITE);

  Serial.println("================================");
}
