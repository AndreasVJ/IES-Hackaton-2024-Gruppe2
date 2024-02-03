#include <Arduino.h>
#include "rfid_id.h"

void RFID_ID_Scanner::printHex(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

void RFID_ID_Scanner::printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
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
    Serial.print("\n");
}

String RFID_ID_Scanner::Scan() {
    if (!rfid->PICC_IsNewCardPresent())
        return "No new card present\n";

    if (!rfid->PICC_ReadCardSerial())
        return "Cant read card serial\n";

    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = rfid->PICC_GetType(rfid->uid.sak);
    Serial.println(rfid->PICC_GetTypeName(piccType));

    // Check is the PICC of Classic MIFARE type
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && 
        piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("Your tag is not of type MIFARE Classic."));
        return "";
    }

    if (rfid->uid.uidByte[0] != nuidPICC[0] || 
        rfid->uid.uidByte[1] != nuidPICC[1] || 
        rfid->uid.uidByte[2] != nuidPICC[2] || 
        rfid->uid.uidByte[3] != nuidPICC[3] ) {
        Serial.println(F("A new card has been detected."));

        // Store NUID into nuidPICC array
        for (byte i = 0; i < 4; i++) {
            nuidPICC[i] = rfid->uid.uidByte[i];
        }

        Serial.println(F("The NUID tag is:"));
        Serial.print(F("In hex: "));
        printHex(rfid->uid.uidByte, rfid->uid.size);
        Serial.println();
        Serial.print(F("In dec: "));
        printDec(rfid->uid.uidByte, rfid->uid.size);
        Serial.println();
    }
    else {
        Serial.println(F("Card read previously."));
    }
    
    return "";
}
