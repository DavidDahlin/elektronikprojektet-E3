#ifndef UIDSCAN_HPP
#define UIDSCAN_HPP

#include <SPI.h>
#include <MFRC522.h>
//#include <PrintEx.h>

unsigned long startTime;

#define RST_PIN  5
#define SS_PIN   53
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setupReader(){

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID reader succesfully setup");
}

String scanForTags(){
  startTime = millis();

  while(millis() - startTime < 10000){
    if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
      Serial.println("Läser..."); 
      String scannedUID;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) scannedUID += "0";
        scannedUID += String(mfrc522.uid.uidByte[i], HEX);
        scannedUID += " ";
      }
    scannedUID.trim(); // Remove trailing space
    Serial.println("Scanned: " + scannedUID);
    return scannedUID;
    }
  }
  mfrc522.PICC_HaltA(); // Stop communication
  Serial.println("Did not find anything");
  return "";
}

bool quickScanFor(String uid){
  startTime = millis();
  while(millis() - startTime < 400){
    if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
      String scannedUID;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) scannedUID += "0";
        scannedUID += String(mfrc522.uid.uidByte[i], HEX);
        scannedUID += " ";
      }
      scannedUID.trim(); // Remove trailing space
      if(scannedUID.equals(uid)){
        Serial.println("Wrong cat detected");
        return true;
      }
    }
  }
  mfrc522.PICC_HaltA(); // Stop communication
  return false;
}



#endif
