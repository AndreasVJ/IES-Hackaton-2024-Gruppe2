#pragma once
#include "Arduino.h"
#include "Firebase.h"
#include "NTPClient.h"
#include "WiFi.h"

class Old{
    public:
        String WIFI_SSID;
        String WIFI_PASSWORD;
        String API_KEY;
        String DATABASE_URL;
        FirebaseData fbdo;
        FirebaseAuth auth;
        FirebaseConfig config;

        WiFiUDP* ntpUDP;
        NTPClient* timeClient;

    public:
        Old(String SSID, String Password,String key, String url);
        
        void oldInit();
        
        String GetDrugs(String uid);
};

