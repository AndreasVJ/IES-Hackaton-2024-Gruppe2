#pragma once
#include "Arduino.h"
#include "Firebase.h"


class Old{
    public:
        bool signupOK = false;
        String WIFI_SSID;
        String WIFI_PASSWORD;
        String API_KEY;
        String DATABASE_URL;
        FirebaseData fbdo;
        FirebaseAuth auth;
        FirebaseConfig config;
        Old(String SSID, String Password,String key, String url);
        void oldInit();
        String GetDrugs(String uid);
};

