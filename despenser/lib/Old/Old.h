#pragma once
#include "Arduino.h"


class OldPerson{
    private:
        String name;
    public:
        int adress;
        OldPerson(String input_name, int input_address);
        void oldInit(String SSID, String Password,String key, String url);
        String GetDrugs(String uid, bool signupOK);
};

