#ifndef UIDSCAN_HPP
#define UIDSCAN_HPP

#include <SPI.h>
#include <MFRC522.h>
//#include <PrintEx.h>

unsigned long startTime;

#define RST_PIN  9
#define SS_PIN   10
MFRC522 mfrc522(SS_PIN, RST_PIN);

void test(){
  Serial.println("Hej");
}

void setupReader(){

  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("RFID reader succesfully setup");
}

String scanForTags(){
  startTime = millis();

  while(millis() - startTime < 10000){
    if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
      String scannedUID;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) scannedUID += "0";
        scannedUID += String(mfrc522.uid.uidByte[i], HEX);
        scannedUID += " ";
      }
    scannedUID.trim(); // Remove trailing space
    return scannedUID;
    }
  }
  mfrc522.PICC_HaltA(); // Stop communication
  return "";
}


#endif
