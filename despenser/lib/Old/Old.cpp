#include "Old.h"
#include "Arduino.h"
#include "Firebase.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "WiFi.h"

OldPerson::OldPerson(String input_name, int input_address){
    name = input_name;
    adress = input_address;
}

OldPerson::oldInit(String SSID, String Password,String key, String url){
    #define WIFI_SSID SSID
    #define WIFI_PASSWORD Password
    #define API_KEY key
    #define DATABASE_URL url
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;

    int count = 0;
    bool signupOK = false;

    Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

OldPerson::GetDrugs(String uid, bool signupOK){
if (Firebase.ready() && signupOK) {
    if (Firebase.RTDB.getInt(&fbdo, "/test/int")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }





}

