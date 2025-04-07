#include <Wire.h>

#define SLAVE_ADDRESS 4


String data = "0Det här är data";                  

void setup(){
  Wire.begin();        
  Serial.begin(115200);
  delay(500);
  // secureConnection();

}


void loop()
{
  Wire.beginTransmission(SLAVE_ADDRESS);
  
  Wire.write(data.c_str());
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDRESS, 32);

  String ssid = "";
  while (Wire.available()){
    char c = Wire.read();
    ssid += c;
  }
  ssid.trim();
  Serial.println(ssid);
  
  delay(5000);
}

void secureConnection(){
  bool connection = false;
	String org = "00100";
	while(!connection){
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(org.c_str());
		Wire.endTransmission();

		Wire.requestFrom(SLAVE_ADDRESS, 32);
		String word = "";
		while(Wire.available()){
			word += Wire.read();
		}
		if(word.equals(org)){
			connection = true;
			Serial.println("I2C connection secured");
		}
    delay(2000);
	}
}