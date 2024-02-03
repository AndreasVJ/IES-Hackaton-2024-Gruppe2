#include "Old.h"
#include "Arduino.h"
#include "Firebase.h"
#include "NTPClient.h"
#include "WiFi.h"

Old::Old(String SSID, String Password,String key, String url) {
    WIFI_SSID = SSID;
    WIFI_PASSWORD = Password;
    API_KEY = key;
    DATABASE_URL = url;

    ntpUDP = new WiFiUDP();
    timeClient = new NTPClient(*ntpUDP);

    oldInit();
}

void Old::oldInit(){
  FirebaseData fbdo;
  FirebaseAuth auth;
  FirebaseConfig config;
  int count = 0;

  Serial.print("Connecting to Wi-Fi:\n");
  Serial.print(WIFI_SSID);
  Serial.print(WIFI_PASSWORD);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.println(API_KEY);

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  
  auth.user.email = "gamlis@uid.com";
  auth.user.password = "gamlis";

  Firebase.reconnectNetwork(true);

  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  timeClient->begin();
}

String Old::GetDrugs(String uid){
  String numDrugs;
  String DrugAddr;

  String documentPath = "test/hei";

  Serial.print("Getting drugs\n");
  if (Firebase.ready()) {
      Serial.print("Firebase ready\n");
      
      unsigned long epochTime = timeClient->getEpochTime();
      Serial.println(epochTime);
      
      FirebaseJson content;
      String dataPath = "fields/time/integerValue";

      content.set(dataPath, 2);

      if (Firebase.Firestore.createDocument(&fbdo, "ies-hackaton-2024-gruppe2", "", documentPath.c_str(), content.raw()))
        Serial.println("Data uploaded successfully");
      else {
        Serial.println("Failed to upload data");
        Serial.println(fbdo.errorReason());
      }
      
  }
  Serial.print("Got dem drugs...\n");

  return "test";
}

