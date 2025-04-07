#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>

#define SLAVE_ADDRESS 4

void setupI2C(){
	Wire.begin();
}

bool i2cSecured(){
	String org = "00100";
	unsigned long startTime = millis();
	const unsigned long timeout = 20000; // 20 seconds in milliseconds
	while(true && (millis() - startTime < timeout)){
		Wire.beginTransmission(SLAVE_ADDRESS);
		Wire.write(org.c_str());
		Wire.endTransmission();
		Serial.println("Sent: " + org);
		Wire.requestFrom(SLAVE_ADDRESS, 6);
		String word = "";
		while(Wire.available()){	
			word += (char)Wire.read();
		}
		word.trim();
		Serial.println("Received: " + word);
		if(word.equals(org)){
			Serial.println("I2C connection secured");	
			return true;
		}
		delay(500);
	}
	Serial.println("Could not connect to esp32");
	return false;
}

bool wifiSecured(){
	String s = "4";
	String connected = "t";
	String nConnected = "f";

	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(s.c_str());
	Wire.endTransmission();

	Wire.requestFrom(SLAVE_ADDRESS, 2);
	String word = "";
	while(Wire.available()){
		word += (char)Wire.read();
	}
	word.trim();
	Serial.println("Received wifi status: "+ word);
	if(word.equals(connected)){
		Serial.println("Connected to Wifi");
		return true;
	}else if(word.equals(nConnected)){
		Serial.println("Not connected to wifi");
		return false;
	}
	Serial.println("Something went wrong in wifi status report");
	return false;
}

String getTime(){
	Wire.requestFrom(SLAVE_ADDRESS, 6);
	String time = "";
	while(Wire.available()){
		time += (char)Wire.read();
	}
	time.trim();
	return time;
}

void sendSSID(String ssid){
	String formated = "2:" + ssid;
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(formated.c_str());
	Wire.endTransmission();
}

void sendPassword(String pw){
	String formated = "3:" + pw;
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(formated.c_str());
	Wire.endTransmission();
}


#endif
