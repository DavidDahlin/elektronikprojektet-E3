#include "mainHelpers.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(1000);

  setupReader();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  String uid = scanForTags();
  if(!uid.equals("")){
    Serial.print("Successfully found:");
    Serial.println(uid);
  }else{
    Serial.println("No tag found");
  }
}
