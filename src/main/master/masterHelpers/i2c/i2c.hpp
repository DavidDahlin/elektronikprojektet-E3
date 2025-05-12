#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>

#define SLAVE_ADDRESS 4

void setupI2C(){
	Wire.begin();
}

void print(String s){
	Serial.print("Sent: ");
	Serial.println(s);
}

bool i2cSecured(){
	Serial.println("i2c initialized");
	String org = "00100";
	unsigned long startTime = millis();
	const unsigned long timeout = 20000; 
	while((millis() - startTime < timeout)){
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
double getTimeDouble(){
	int hour, minute;
	sscanf(getTime().c_str(), " %d:%d", &hour, &minute);
	return (double)(hour + (double)minute/60);
}

void sendSSID(String ssid){
	String formated = "2:" + ssid;
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(formated.c_str());
	Wire.endTransmission();
	print(ssid);
}

void sendPassword(String pw){
	String formated = "3:" + pw;
	Wire.beginTransmission(SLAVE_ADDRESS);
	Wire.write(formated.c_str());
	Wire.endTransmission();
	print(pw);
}


#endif
