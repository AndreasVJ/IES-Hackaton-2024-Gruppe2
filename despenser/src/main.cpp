#include <Arduino.h>
#include "rfid_id.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "Firebase.h"

RFID_ID_Scanner* id_scanner;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting RFID\n");

  // put your setup code here, to run once:
  id_scanner = new RFID_ID_Scanner();
}

void loop() {
  // put your main code here, to run repeatedly:
  String scanned_id = id_scanner->Scan();
  Serial.print(scanned_id);

  delay(500);
}
