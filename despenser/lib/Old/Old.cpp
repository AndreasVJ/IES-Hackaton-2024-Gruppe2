#include "Old.h"
#include "Arduino.h"
#include <FirebaseJson.h>
#include "addons/TokenHelper.h"

#include "addons/RTDBHelper.h"

OldPerson::OldPerson(String input_name, int input_address){
    name = input_name;
    adress = input_address;
}

