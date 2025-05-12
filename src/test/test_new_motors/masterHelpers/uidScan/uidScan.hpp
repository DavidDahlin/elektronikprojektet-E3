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

String scanForTags(int milliWaitingTime){
  Serial.println("[Scan started]");
  startTime = millis();
  while(millis() - startTime < milliWaitingTime){
    if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){ 
      String scannedUID;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) scannedUID += "0";
        scannedUID += String(mfrc522.uid.uidByte[i], HEX);
        scannedUID += " ";
      }
    scannedUID.trim(); // Remove trailing space
    mfrc522.PICC_HaltA(); // Stop communication
    return scannedUID;
    }
  }
  mfrc522.PICC_HaltA(); // Stop communication
  Serial.println("Did not find anything");
  return "";
}

bool quickScanFor(String uid){
      String scannedUID = scanForTags(400);
      if(scannedUID.equals(uid)){
        Serial.println("Wrong cat detected");
        return true;
      }
  return false;
}



#endif
