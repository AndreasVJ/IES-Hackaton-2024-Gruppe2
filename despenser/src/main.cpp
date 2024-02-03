#include <Arduino.h>
#include "rfid_id.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "Firebase.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> 
#include "Old.h"

#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4

RFID_ID_Scanner* id_scanner;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Old Oldperson("SSID", "Password", "key", "URL"); // Dette må settes inn!!


void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:
  id_scanner = new RFID_ID_Scanner();
}

void loop() {
  // put your main code here, to run repeatedly:
  String scanned_id = id_scanner->Scan();
  Serial.print(scanned_id);
}




