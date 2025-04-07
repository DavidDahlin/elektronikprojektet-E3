#include "masterHelpers.h"

const char* ssid;
const char* password;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(2000);

  

  ssid = getWifiSSID();
  password = getWifiPassword();
  
  setupI2C();

  while(!i2cSecured());

  sendSSID(ssid);
  sendPassword(password);

  while(!wifiSecured()){
    sendSSID(ssid);
    sendPassword(password);
  } 


  // setupReader();
  // setup_avstandsmatare();

  delay(2000);
}

void loop() {

  String t = getTime();
  Serial.println("time: " + t); 
  // String uid = scanForTags();
  // if(!uid.equals("")){
  //   Serial.print("Successfully found:");
  //   Serial.println(uid);

  //   int dir = getMatchDirection(uid);
  //   Serial.println(dir);

  // }else{
  //   Serial.println("No tag found");
  // }

  // bool go = isNotFull1();
  // Serial.print("go 1: ");
  // Serial.println(go);
  

  // delay(500);
  // go = isNotFull2();
  // Serial.print("go 2: ");
  // Serial.println(go);

  // avstand_test();
  delay(2000);
  
}
