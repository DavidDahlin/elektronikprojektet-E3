#include "slaveHelpers.h"

#define SLAVE_ADDRESS 4
#define SDA_PIN 9
#define SCL_PIN 8

String receivedMessage;
// String responceMessage;
String ssid;
String password;

char flag;

// uint8_t buffer[32];
// size_t bufferLength = 32;

// void updateBuffer(String s){
// 	s.getBytes(buffer, sizeof(buffer));
// }

// void send(String s){
// 	responceMessage = "Tjaba";
// 	updateBuffer(responceMessage);
// 	Wire.write(buffer, bufferLength);
// 	Serial.println("Sent: " + s);
 
// }



void connectWifi(){
  if(ssid.length()>0 and password.length()>0){
    if(setupWifi(ssid, password)){
      flag = '1';
    }
  }
}

void sendWifiStatus(){
  String sant = "t";
  String falskt = "f";
  if(isConnectedToWiFi()){
    send(sant);
  }else {
    send(falskt);
  }
  flag = '1';
}


void receiveEvent(int howMany){
  receivedMessage = "";
  while (Wire.available()) {
    receivedMessage += (char)Wire.read();
  }
  receivedMessage.trim();
  flag = receivedMessage.charAt(0);
  String data  = receivedMessage.substring(2);

  
  Serial.println("data: " + data);
  

  switch(flag){
    case '2': 
      ssid = data;
      connectWifi();
      break;
    case '3':
      password = data;
      connectWifi();
      break;
    default:
      break;
    
  }
}

void sendTime(){
  String time = getTime();
  
  send(time);
}

void requestEvent(){
  switch(flag){
    case '0':
      send(receivedMessage);
      break;
    case '1':
      sendTime();
      break;
    case '4':
      sendWifiStatus();
      break;
    default:
      break;
  }
}

void setupI2C(int sda_pin, int scl_pin){
	Wire.setPins(sda_pin, scl_pin);
	Wire.begin(SLAVE_ADDRESS);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
  Serial.println("I2C setup");
}

void setup(){
  Serial.begin(115200);
  delay(2000);
  setupI2C(SDA_PIN,SCL_PIN);

  
}

void loop(){

  delay(100);
}


