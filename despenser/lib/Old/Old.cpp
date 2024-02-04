#include "Old.h"
#include "WiFi.h"
#include "Arduino.h"
#include "Firebase.h"
#include "NTPClient.h"
#include "ArduinoJson.h"

Old::Old(String SSID, String Password, String key) {
    WIFI_SSID = SSID;
    WIFI_PASSWORD = Password;
    API_KEY = key;

    ntpUDP = new WiFiUDP();
    timeClient = new NTPClient(*ntpUDP);

    // Firebase
    fbdo = new FirebaseData();
    auth = new FirebaseAuth();
    config = new FirebaseConfig();

    // WiFi
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

    /* Assign the api key (required) */
    config->api_key = API_KEY;
    
    auth->user.email = "gamlis@uid.com";
    auth->user.password = "gamlis";

    Firebase.reconnectNetwork(true);

    fbdo->setBSSLBufferSize(4096, 1024);
    fbdo->setResponseSize(2048);

    Firebase.begin(config, auth);

    timeClient->begin();
}

String Old::GetDrugs(String uid){
  	String documentPath = "users/";
  	documentPath += String(uid);

  	Serial.print("Getting drugs\n");
  	if (Firebase.ready()) {
      	Serial.print("Firebase ready\n");
      
      	String mask = "medication";
      	StaticJsonDocument<512> doc;
      	if (Firebase.Firestore.getDocument(fbdo, "ies-hackaton-2024-gruppe2", "", documentPath.c_str(), mask.c_str())) {
			      deserializeJson(doc, fbdo->payload().c_str());
  			    Serial.print("Got dem drugs...\n");
			
			      const char* drugString = doc["fields"]["medication"]["stringValue"];
			      return String(drugString);
        }
        else {
            Serial.println(fbdo->errorReason());
        }
  	}

    return "";
}


