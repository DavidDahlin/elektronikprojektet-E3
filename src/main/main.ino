#include "mainHelpers.h"

const char* ssid;
const char* password;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(1000);

  setupReader();

  ssid = getWifiSSID();
  password = getWifiPassword();
  
  Serial.print("ssid: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);

}

void loop() {
  put your main code here, to run repeatedly:
  String uid = scanForTags();
  if(!uid.equals("")){
    Serial.print("Successfully found:");
    Serial.println(uid);

    int dir = getMatchDirection(uid);
    Serial.println(dir);

  }else{
    Serial.println("No tag found");
  }

  

  
}
