#include <Arduino.h>
#include "rfid_id.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Adafruit_GFX.h>   
#include <Adafruit_ST7789.h> 
#include "Old.h"
#include "DrugServo.h"

// #define TFT_MOSI 19
// #define TFT_SCLK 18
// #define TFT_CS 5
// #define TFT_DC 16
// #define TFT_RST 23
// #define TFT_BL 4

// Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

Old* drugfetcher;
String lastScannerID = "";
unsigned long lastFlush = 0;
RFID_ID_Scanner* id_scanner;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting RFID\n");

  // put your setup code here, to run once:
  id_scanner = new RFID_ID_Scanner();

  drugfetcher = new Old("AndreasVJ iPhone", "12345679", "AIzaSyBMdIr9yelGR95c8WQnh93mpVvEY9NRrss");
}

void loop() {
  	// put your main code here, to run repeatedly:
	String scanned_id = id_scanner->Scan();
	if (scanned_id != "") {
		Serial.println(scanned_id);

		// Has scanned card
		String drugString = drugfetcher->GetDrugs(scanned_id);
		if (drugString != "") {
			Serial.print("Albert needs these drugs: ");
			Serial.println(drugString);
      ServoDispence(drugString);
		}
	}
  // ServoDispence("EA");

  delay(500);
}