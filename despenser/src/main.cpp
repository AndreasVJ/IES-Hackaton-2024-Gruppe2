#include <Arduino.h>
#include "rfid_id.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <NTPClient.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> 
#include "Old.h"

#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4

RFID_ID_Scanner* id_scanner;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Old Oldperson("SSID", "Password", "key", "URL");

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool hasWritten = false;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting RFID\n");

  // put your setup code here, to run once:
  id_scanner = new RFID_ID_Scanner();

  WiFi.begin("AndreasVJ iPhone", "12345679");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  config.api_key = "AIzaSyBMdIr9yelGR95c8WQnh93mpVvEY9NRrss";
  auth.user.email = "gamlis@uid.com";
  auth.user.password = "gamlis";

  Firebase.reconnectNetwork(true);

  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // Initialize an NTPClient to get time
  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  String scanned_id = id_scanner->Scan();
  Serial.print(scanned_id);

  if (Firebase.ready() && hasWritten == false) {
      hasWritten = true;
      timeClient.update();

      // Get the epoch time (seconds since January 1, 1970)
      unsigned long epochTime = timeClient.getEpochTime();
      Serial.println(epochTime);


      FirebaseJson content;
      String documentPath = "test/" + String(epochTime);

      String dataPath = "fields/time/integerValue";
      content.set(dataPath, epochTime);

      if (Firebase.Firestore.createDocument(&fbdo, "ies-hackaton-2024-gruppe2", "", documentPath.c_str(), content.raw()))
        Serial.println("Data uploaded successfully");
      else
        Serial.println("Failed to upload data");

      delay(1000);
    }

    delay(100);
}




