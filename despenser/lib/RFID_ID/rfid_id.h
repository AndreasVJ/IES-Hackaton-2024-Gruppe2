#ifndef RFID_ID_H
#define RFID_ID_H

#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

#define SS_PIN 21
#define RST_PIN 2

class RFID_ID_Scanner {
public:
    RFID_ID_Scanner();

    String Scan();

    void printHex(byte *buffer, byte bufferSize);

    void printDec(byte *buffer, byte bufferSize);

    String byteToString(byte* buffer, byte bufferSize);

private:
    MFRC522* rfid;
    MFRC522::MIFARE_Key key;

    byte nuidPICC[4];
};

#endif
