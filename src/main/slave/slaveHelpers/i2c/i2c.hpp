#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>

#define SLAVE_ADDRESS 4
String mssg;

uint8_t buffer[32];
size_t bufferLength = 32;

void updateBuffer(String s){
	s.getBytes(buffer, sizeof(buffer));
}


void send(String s){
	Serial.println("Sending: " + s);
	updateBuffer(s);
	Wire.write(buffer, bufferLength);
}


#endif
