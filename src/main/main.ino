#include "mainHelpers.h"

const char* ssid;
const char* password;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(1000);

  // setupReader();
  setup_avstandsmatare();

  ssid = getWifiSSID();
  password = getWifiPassword();
  
  Serial.print("ssid: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);

}

void loop() {
  
  // String uid = scanForTags();
  // if(!uid.equals("")){
  //   Serial.print("Successfully found:");
  //   Serial.println(uid);

  //   int dir = getMatchDirection(uid);
  //   Serial.println(dir);

  // }else{
  //   Serial.println("No tag found");
  // }

  float len = getDistance1();
  Serial.println(len);

  

  
}
