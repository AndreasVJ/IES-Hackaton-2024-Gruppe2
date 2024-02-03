#pragma once
#include "Arduino.h"
#include "Firebase.h"


class OldPerson{
    public:
        String WIFI_SSID;
        String WIFI_PASSWORD;
        String API_KEY;
        String DATABASE_URL;
        FirebaseData fbdo;
        FirebaseAuth auth;
        FirebaseConfig config;
        OldPerson(String SSID, String Password,String key, String url);
        void oldInit();
        String GetDrugs(String uid, bool signupOK);
};

