#include <Arduino.h>
#include "rfid_id.h"

void RFID_ID_Scanner::printHex(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

RFID_ID_Scanner::RFID_ID_Scanner() {
    // Initilize SPI interface and rfid
    rfid = new MFRC522(SS_PIN, RST_PIN);
    
    SPI.begin();
    rfid->PCD_Init();
    
    // Initilize key
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    Serial.println(F("This code scan the MIFARE Classsic NUID."));
    Serial.print(F("Using the following key:"));
    printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}

String RFID_ID_Scanner::Scan() {
    return "Hei";
}
