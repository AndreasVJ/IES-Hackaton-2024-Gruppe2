#include <Arduino.h>
#include "rfid_id.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> 
#include "Old.h"

// #define TFT_MOSI 19
// #define TFT_SCLK 18
// #define TFT_CS 5
// #define TFT_DC 16
// #define TFT_RST 23
// #define TFT_BL 4

// Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

RFID_ID_Scanner* id_scanner;
Old* drugfetcher;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting RFID\n");

  // put your setup code here, to run once:
  id_scanner = new RFID_ID_Scanner();

  drugfetcher = new Old("AndreasVJ iPhone", "12345679", "AIzaSyBMdIr9yelGR95c8WQnh93mpVvEY9NRrss", "URL");
}

bool hasWritten = false;

void loop() {
  // put your main code here, to run repeatedly:
  String scanned_id = id_scanner->Scan();
  // Serial.print(scanned_id);
  if (hasWritten == false) {
    drugfetcher->GetDrugs("1234");
    hasWritten = true;
  }
}




