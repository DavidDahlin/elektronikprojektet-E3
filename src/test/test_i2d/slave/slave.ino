#include <Wire.h>

uint8_t buffer[32];
size_t bufferLength = 32;

String ssid;
String psswrd;

String receivedMessage;
String responseMessage;
bool secureSetup = true;
// String responseMessage = "Hello from ESP32!";

void updateBuffer(String s){
  s.getBytes(buffer, sizeof(buffer));
}

void setup()
{
  
  Wire.setPins(9, 8);
  Wire.begin(4);
  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
}


void loop()
{
  delay(100);
}



void receiveEvent(int howMany){
  receivedMessage = "";
  while (Wire.available()) {
    receivedMessage += (char)Wire.read();
  }
  receivedMessage.trim();

  Serial.print("Master Says: ");
  Serial.println(receivedMessage);
  

}

void requestEvent(){

  char setup = '0';

  if(receivedMessage.charAt(0) == setup){
    responseMessage = receivedMessage;
  }else{
    responseMessage = "Hej, inget att hämta har";
  }

  // String ssd = "00100";
  updateBuffer(responseMessage);
  Wire.write(buffer, bufferLength);

}


