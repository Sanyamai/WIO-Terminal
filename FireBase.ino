#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <TFT_eSPI.h>


// ================= TFT =================

TFT_eSPI tft = TFT_eSPI();


// ================= WiFi =================

const char* ssid = "MAI";
const char* password = "88888888";


// ================= Firebase =================

String firebaseURL =
"https://dht11-firebase-f859f-default-rtdb.asia-southeast1.firebasedatabase.app/sensor.json";


// ================= DHT11 =================

#define DHTPIN D0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


// ================= Sensor =================

float temperature;
float humidity;



// ================= Display =================

void showDisplay(String status){


  tft.fillScreen(TFT_BLACK);


  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.setTextSize(2);


  tft.setCursor(10,10);

  tft.println("Wio Terminal");


  tft.setTextSize(2);


  tft.setCursor(10,60);

  tft.setTextColor(TFT_YELLOW);

  tft.print("Temp: ");

  tft.print(temperature);

  tft.println(" C");



  tft.setCursor(10,100);

  tft.setTextColor(TFT_CYAN);

  tft.print("Hum : ");

  tft.print(humidity);

  tft.println(" %");



  tft.setCursor(10,150);

  tft.setTextColor(TFT_WHITE);

  tft.println(status);


}



// ================= Setup =================

void setup() {


  Serial.begin(115200);


  delay(1000);



  // TFT Start

  tft.begin();

  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);


  tft.setTextSize(2);

  tft.setTextColor(TFT_GREEN);

  tft.setCursor(10,20);

  tft.println("Starting...");



  // DHT

  dht.begin();



  // WiFi

  WiFi.disconnect();

  delay(1000);


  WiFi.mode(WIFI_STA);


  tft.println("WiFi");


  Serial.println("Connect WiFi");


  WiFi.begin(ssid,password);



  while(WiFi.status()!=WL_CONNECTED){

    delay(500);

    Serial.print(".");

  }



  Serial.println();

  Serial.println("WiFi Connected");


  tft.println("Connected");


  delay(1000);

}



// ================= Firebase =================

void sendFirebase(){


  if(WiFi.status()==WL_CONNECTED){



    Serial.println("Read DHT11");


    temperature = dht.readTemperature();

    humidity = dht.readHumidity();



    if(isnan(temperature) || isnan(humidity)){


      Serial.println("DHT Error");


      showDisplay("DHT ERROR");


      return;

    }



    Serial.print("Temp : ");

    Serial.println(temperature);


    Serial.print("Hum : ");

    Serial.println(humidity);



    showDisplay("Sending...");



    HTTPClient http;


    http.begin(firebaseURL);


    http.addHeader(
      "Content-Type",
      "application/json"
    );



    String json = "{";


    json += "\"device\":\"WioTerminal\",";

    json += "\"sensor\":\"DHT11\",";

    json += "\"temperature\":" + String(temperature,1) + ",";

    json += "\"humidity\":" + String(humidity,1);


    json += "}";



    int httpCode = http.PUT(json);



    Serial.print("Firebase : ");

    Serial.println(httpCode);



    if(httpCode == 200){

      showDisplay("Firebase OK");

    }
    else{

      showDisplay("Firebase FAIL");

    }



    http.end();



  }

}



// ================= Loop =================

void loop(){


  sendFirebase();


  delay(10000);


}
