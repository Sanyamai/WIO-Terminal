#include <rpcWiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <TFT_eSPI.h>
#include <time.h>

// =====================================================
// TFT
// =====================================================

TFT_eSPI tft = TFT_eSPI();


// =====================================================
// WiFi
// =====================================================

const char* ssid = "🐴🦄";
const char* password = "88888888";


// =====================================================
// Firebase
// =====================================================

String firebaseBaseURL =
"https://dht11-firebase-f859f-default-rtdb.asia-southeast1.firebasedatabase.app";


// =====================================================
// DHT11
// =====================================================

#define DHTPIN D0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


// =====================================================
// Sensor
// =====================================================

float temperature = 0;
float humidity = 0;


// =====================================================
// Timer
// =====================================================

// ส่งข้อมูลทุก 1 นาที
const unsigned long SEND_INTERVAL = 60000;

unsigned long lastSendTime = 0;


// =====================================================
// NTP
// =====================================================

WiFiUDP udp;

const char* ntpServer = "pool.ntp.org";

const int NTP_PACKET_SIZE = 48;

byte packetBuffer[NTP_PACKET_SIZE];

// ประเทศไทย UTC+7
const long TIMEZONE_OFFSET = 7 * 60 * 60;

unsigned long epochTime = 0;


// =====================================================
// DISPLAY
// =====================================================

void showDisplay(String status) {

  tft.fillScreen(TFT_BLACK);

  // -------------------------
  // Title
  // -------------------------

  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.setTextSize(2);

  tft.setCursor(10, 10);

  tft.println("Wio Terminal");


  // -------------------------
  // Temperature
  // -------------------------

  tft.setCursor(10, 60);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);

  tft.print("Temp: ");

  tft.print(temperature, 1);

  tft.println(" C");


  // -------------------------
  // Humidity
  // -------------------------

  tft.setCursor(10, 100);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);

  tft.print("Hum : ");

  tft.print(humidity, 1);

  tft.println(" %");


  // -------------------------
  // Status
  // -------------------------

  tft.setCursor(10, 150);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println(status);
}


// =====================================================
// CONNECT WIFI
// =====================================================

bool connectWiFi() {

  // ถ้าเชื่อมอยู่แล้ว ไม่ต้องทำอะไร
  if (WiFi.status() == WL_CONNECTED) {

    return true;
  }


  Serial.println();
  Serial.println("==============================");
  Serial.println("Connecting WiFi...");
  Serial.print("SSID: ");
  Serial.println(ssid);


  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.setTextSize(2);

  tft.setCursor(10, 20);

  tft.println("Connecting WiFi");


  // ===================================================
  // สำคัญ:
  // ไม่ใช้ WiFi.disconnect()
  // ===================================================

  WiFi.mode(WIFI_STA);

  delay(500);


  // เริ่มเชื่อมต่อ
  WiFi.begin(ssid, password);


  // รอสูงสุดประมาณ 20 วินาที
  int count = 0;

  while (WiFi.status() != WL_CONNECTED && count < 40) {

    delay(500);

    Serial.print(".");

    count++;
  }


  Serial.println();


  // ===================================================
  // CONNECT SUCCESS
  // ===================================================

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi Connected");

    Serial.print("IP Address: ");

    Serial.println(WiFi.localIP());


    Serial.print("RSSI: ");

    Serial.print(WiFi.RSSI());

    Serial.println(" dBm");


    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    tft.setTextSize(2);

    tft.setCursor(10, 20);

    tft.println("WiFi Connected");


    tft.setCursor(10, 60);

    tft.setTextSize(1);

    tft.println(WiFi.localIP());


    delay(1500);


    Serial.println("==============================");

    return true;
  }


  // ===================================================
  // CONNECT FAILED
  // ===================================================

  Serial.println("WiFi Connection Failed");

  Serial.print("WiFi Status: ");

  Serial.println(WiFi.status());


  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_RED, TFT_BLACK);

  tft.setTextSize(2);

  tft.setCursor(10, 20);

  tft.println("WiFi FAILED");


  tft.setCursor(10, 60);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.setTextSize(1);

  tft.print("Status: ");

  tft.println(WiFi.status());


  Serial.println("==============================");


  return false;
}


// =====================================================
// NTP PACKET
// =====================================================

void sendNTPpacket(const char* address) {

  memset(packetBuffer, 0, NTP_PACKET_SIZE);


  // NTP request

  packetBuffer[0] = 0b11100011;

  packetBuffer[1] = 0;

  packetBuffer[2] = 6;

  packetBuffer[3] = 0xEC;


  packetBuffer[12] = 49;

  packetBuffer[13] = 0x4E;

  packetBuffer[14] = 49;

  packetBuffer[15] = 52;


  udp.beginPacket(address, 123);

  udp.write(packetBuffer, NTP_PACKET_SIZE);

  udp.endPacket();
}


// =====================================================
// GET NTP TIME
// =====================================================

bool getNTPTime() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("NTP: WiFi not connected");

    return false;
  }


  Serial.println();

  Serial.println("Getting time from NTP...");


  udp.begin(2390);


  // ส่ง NTP request
  sendNTPpacket(ntpServer);


  unsigned long startTime = millis();


  while (millis() - startTime < 5000) {

    int size = udp.parsePacket();


    if (size >= NTP_PACKET_SIZE) {

      udp.read(packetBuffer, NTP_PACKET_SIZE);


      unsigned long highWord =
      word(packetBuffer[40], packetBuffer[41]);


      unsigned long lowWord =
      word(packetBuffer[42], packetBuffer[43]);


      unsigned long secsSince1900 =
      (highWord << 16) | lowWord;


      // NTP epoch 1900
      // Unix epoch 1970

      const unsigned long seventyYears =
      2208988800UL;


      epochTime =
      secsSince1900 - seventyYears;


      // UTC+7 Thailand

      epochTime += TIMEZONE_OFFSET;


      udp.stop();


      Serial.println("NTP Time OK");

      return true;
    }


    delay(100);
  }


  udp.stop();


  Serial.println("NTP Time FAILED");


  return false;
}


// =====================================================
// CONVERT TIME
// =====================================================

void getDateTime(
  unsigned long epoch,
  char* dateString,
  char* timeString
) {

  time_t rawTime = epoch;


  struct tm* timeinfo;


  timeinfo = gmtime(&rawTime);


  // YYYY-MM-DD

  sprintf(
    dateString,
    "%04d-%02d-%02d",
    timeinfo->tm_year + 1900,
    timeinfo->tm_mon + 1,
    timeinfo->tm_mday
  );


  // HH:MM:SS

  sprintf(
    timeString,
    "%02d:%02d:%02d",
    timeinfo->tm_hour,
    timeinfo->tm_min,
    timeinfo->tm_sec
  );
}


// =====================================================
// SEND FIREBASE
// =====================================================

void sendFirebase() {

  // ===================================================
  // ตรวจสอบ WiFi
  // ===================================================

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi not connected");

    if (!connectWiFi()) {

      return;
    }
  }


  // ===================================================
  // READ DHT
  // ===================================================

  Serial.println();

  Serial.println("==============================");

  Serial.println("Read DHT11");


  temperature = dht.readTemperature();

  humidity = dht.readHumidity();


  // ตรวจสอบค่า

  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("DHT ERROR");

    showDisplay("DHT ERROR");

    return;
  }


  // ===================================================
  // GET TIME
  // ===================================================

  if (!getNTPTime()) {

    Serial.println("Time ERROR");

    showDisplay("TIME ERROR");

    return;
  }


  // ===================================================
  // DATE / TIME
  // ===================================================

  char dateString[20];

  char timeString[20];


  getDateTime(
    epochTime,
    dateString,
    timeString
  );


  // ===================================================
  // SERIAL
  // ===================================================

  Serial.print("Date        : ");

  Serial.println(dateString);


  Serial.print("Time        : ");

  Serial.println(timeString);


  Serial.print("Timestamp   : ");

  Serial.println(epochTime);


  Serial.print("Temperature : ");

  Serial.print(temperature, 1);

  Serial.println(" C");


  Serial.print("Humidity    : ");

  Serial.print(humidity, 1);

  Serial.println(" %");


  showDisplay("Sending...");


  // ===================================================
  // CURRENT
  // ===================================================

  String currentURL =
  firebaseBaseURL +
  "/sensor/current.json";


  HTTPClient httpCurrent;


  httpCurrent.begin(currentURL);


  httpCurrent.addHeader(
    "Content-Type",
    "application/json"
  );


  String currentJson = "{";


  currentJson += "\"device\":\"WioTerminal\",";

  currentJson += "\"sensor\":\"DHT11\",";

  currentJson += "\"temperature\":" +
                 String(temperature, 1) + ",";

  currentJson += "\"humidity\":" +
                 String(humidity, 1) + ",";

  currentJson += "\"date\":\"" +
                 String(dateString) + "\",";

  currentJson += "\"time\":\"" +
                 String(timeString) + "\",";

  currentJson += "\"timestamp\":" +
                 String(epochTime);


  currentJson += "}";


  Serial.println();

  Serial.println("Sending CURRENT...");


  int currentCode =
  httpCurrent.PUT(currentJson);


  Serial.print("Current Firebase : ");

  Serial.println(currentCode);


  if (currentCode != 200) {

    Serial.print("Current response: ");

    Serial.println(
      httpCurrent.getString()
    );
  }


  httpCurrent.end();


  // ===================================================
  // HISTORY
  // ===================================================

  String historyURL =
  firebaseBaseURL +
  "/sensor/history.json";


  HTTPClient httpHistory;


  httpHistory.begin(historyURL);


  httpHistory.addHeader(
    "Content-Type",
    "application/json"
  );


  String historyJson = "{";


  historyJson += "\"device\":\"WioTerminal\",";

  historyJson += "\"sensor\":\"DHT11\",";

  historyJson += "\"timestamp\":" +
                 String(epochTime) + ",";

  historyJson += "\"date\":\"" +
                 String(dateString) + "\",";

  historyJson += "\"time\":\"" +
                 String(timeString) + "\",";

  historyJson += "\"temperature\":" +
                 String(temperature, 1) + ",";

  historyJson += "\"humidity\":" +
                 String(humidity, 1);


  historyJson += "}";


  Serial.println();

  Serial.println("Sending HISTORY...");


  // POST = Firebase สร้าง ID อัตโนมัติ

  int historyCode =
  httpHistory.POST(historyJson);


  Serial.print("History Firebase : ");

  Serial.println(historyCode);


  if (historyCode != 200) {

    Serial.print("History response: ");

    Serial.println(
      httpHistory.getString()
    );
  }


  // ===================================================
  // RESULT
  // ===================================================

  if (
    currentCode == 200 &&
    historyCode == 200
  ) {

    Serial.println();

    Serial.println("Firebase Saved OK");

    showDisplay("Firebase OK");
  }

  else {

    Serial.println();

    Serial.println("Firebase Save FAIL");

    showDisplay("Firebase FAIL");
  }


  httpHistory.end();


  Serial.println("==============================");
}


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

  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.setCursor(10, 20);

  tft.println("Starting...");


  // ===================================================
  // DHT
  // ===================================================

  dht.begin();

  delay(2000);


  // ===================================================
  // WIFI
  // ===================================================

  bool wifiOK = connectWiFi();


  // ===================================================
  // NTP
  // ===================================================

  if (wifiOK) {

    getNTPTime();
  }


  // ===================================================
  // SEND FIRST DATA
  // ===================================================

  if (wifiOK) {

    sendFirebase();
  }


  lastSendTime = millis();
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  // ===================================================
  // ตรวจสอบ WiFi
  // ===================================================

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println();

    Serial.println("WiFi disconnected!");

    connectWiFi();
  }


  // ===================================================
  // ส่งข้อมูลทุก 1 นาที
  // ===================================================

  if (
    WiFi.status() == WL_CONNECTED &&
    millis() - lastSendTime >= SEND_INTERVAL
  ) {

    lastSendTime = millis();

    sendFirebase();
  }


  delay(100);
}
