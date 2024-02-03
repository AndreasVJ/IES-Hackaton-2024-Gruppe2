#include "Old.h"
#include "Arduino.h"
#include "Firebase.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "WiFi.h"

Old::Old(String SSID, String Password,String key, String url){
    String WIFI_SSID = SSID;
    String WIFI_PASSWORD = Password;
    String API_KEY = key;
    String DATABASE_URL = url;
}

void Old::oldInit(){
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    int count = 0;
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

String Old::GetDrugs(String uid){
  String path = uid;
  path += "/String";
  String numDrugs;
if (Firebase.ready() && signupOK) {
    if (Firebase.RTDB.getString(&fbdo, path)) {
      if (fbdo.dataType() == "String") {
        numDrugs = fbdo.intData();
        Serial.println(numDrugs);
        return numDrugs;
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
}
}

