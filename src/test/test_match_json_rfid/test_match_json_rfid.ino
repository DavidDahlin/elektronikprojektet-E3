

#include <ArduinoJson.h> 
#include <SPI.h>
#include <MFRC522.h>

// #include "matchUID.h"





const char* json = R"(
  {
    "Cat1": {
      "name": "Milo",
      "uid": "C5 e0 f0 75",
      "food": 100
	  },
    "Cat2": {
      "name": "Cocos",
	    "uid": "4e 5d d0 6f",
	    "food": 200
	  }
  }
)";

#define RST_PIN  9
#define SS_PIN   10
#define LED_PIN  2  // LED connected to pin 2

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Replace with your target UID (C5 E0 F0 75 in hex)
// byte targetUID[] = {0xC5, 0xE0, 0xF0, 0x75};

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial connection

  
  // // Extract values from Cat1
  // String cat1_uid = doc["Cat1"]["uid"]; // 123
  // int cat1_mat = doc["Cat1"]["mat"]; // 100

  // // Extract values from Cat2
  // String cat2_uid = doc["Cat2"]["uid"]; // 456
  // int cat2_mat = doc["Cat2"]["mat"]; // 200

  // delay(1000);

  // // Print results
  // Serial.println("Cat1:");
  // Serial.print("UID: ");
  // Serial.println(cat1_uid);
  // Serial.print("MAT: ");
  // Serial.println(cat1_mat);

  // Serial.println("\nCat2:");
  // Serial.print("UID: ");
  // Serial.println(cat2_uid);
  // Serial.print("MAT: ");
  // Serial.println(cat2_mat);

  //Start på andra 

  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(LED_PIN, OUTPUT);
  Serial.println("Scan RFID tag...");
  

}


void loop() {
  // Reset LED to OFF
  digitalWrite(LED_PIN, LOW);

  // Check for RFID tag
  if (!(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())) {
    return; // No tag detected
  }
  Serial.println("Hej");


  String scannedUID;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) scannedUID += "0";
    scannedUID += String(mfrc522.uid.uidByte[i], HEX);
    scannedUID += " ";
  }
  scannedUID.trim(); // Remove trailing space

  Serial.println(scannedUID);

  
  // Allocate memory for parsing (adjust size if needed)
  DynamicJsonDocument doc(1024);

  // Parse JSON
  DeserializationError error = deserializeJson(doc, json);

  

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  bool matchFound = false;
  for(JsonPair entry: doc.as<JsonObject>()){
    const char* cat = entry.key().c_str();
    const char* storedUID = entry.value()["uid"].as<const char*>();
    const char* name = entry.value()["name"].as<const char*>();
    
    String storedUIDString= String(storedUID);
    storedUIDString.toLowerCase();

    

    if(scannedUID.equals(storedUIDString)){
      Serial.println("Truuu");

      String catString = String(cat);
      Serial.println(catString);
    }
  

  
  // // Check if UID matches target
  // bool match = true;
  // for (byte i = 0; i < 4; i++) { // Assumes 4-byte UID
  //   if (mfrc522.uid.uidByte[i] != targetUID[i]) {
  //     match = false;
  //     break;
  //   }
  // }

  // // If UID matches, blink LED
  // if (match) {
  //   Serial.println("Access Granted!");
  //   for (int i = 0; i < 3; i++) { // Blink 3 times
  //     Serial.println("Access Approved");
  //   }
  // } else {
  //   Serial.println("Access Denied!");
  // }

  // // Print UID for debugging
  // Serial.print("UID:");
  // for (byte i = 0; i < mfrc522.uid.size; i++) {
  //   Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  //   Serial.print(mfrc522.uid.uidByte[i], HEX);
  // }
  // Serial.println();
  }

  mfrc522.PICC_HaltA(); // Stop communication
}