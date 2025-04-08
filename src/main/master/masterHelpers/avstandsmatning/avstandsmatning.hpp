#ifndef AVSTANDSMATNING_HPP
#define AVSTANDSMATNING_HPP

#include <math.h>

//Set pins
#define TRIG_PIN_1 12
#define TRIG_PIN_2 13
#define ECHO_PIN_1 11
#define ECHO_PIN_2 10

const float SPEED_OF_SOUND = 343;
const float MIN_DIST =50;

void setup_avstandsmatare(){
	pinMode(TRIG_PIN_1, OUTPUT);
	pinMode(TRIG_PIN_2, OUTPUT);
	pinMode(ECHO_PIN_1, INPUT);
	pinMode(ECHO_PIN_2, INPUT);
	digitalWrite(TRIG_PIN_1, LOW);
	digitalWrite(TRIG_PIN_2, LOW);
}


float getDistance1(){
	float avg = 0;
	int n = 100;

	for(int i = 0; i < n ; i++){
		digitalWrite(TRIG_PIN_1,HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIG_PIN_1,LOW);
		
		long duration = pulseIn(ECHO_PIN_1, HIGH, 25000);
		float distance = duration / 2 * SPEED_OF_SOUND * pow(10, -3); 
		
		if(distance > 1){
			avg += distance/n;
		}else{
		i--;
		}
		delayMicroseconds(10);
	}
	return avg;
}

float getDistance2(){
	float avg = 0;
	int n = 100;

	for(int i = 0; i < n ; i++){
		digitalWrite(TRIG_PIN_2,HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIG_PIN_2,LOW);
		
		long duration = pulseIn(ECHO_PIN_2, HIGH, 25000);
		float distance = duration / 2 * SPEED_OF_SOUND * pow(10, -3); 
		
		if(distance > 1){
			avg += distance/n;
		}else{
		i--;
		}
		delayMicroseconds(10);
	}
	return avg;
}

bool isFull1(){

	float avg = 0;
	int n = 100;

	for(int i = 0; i < n ; i++){
		digitalWrite(TRIG_PIN_1,HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIG_PIN_1,LOW);
		
		long duration = pulseIn(ECHO_PIN_1, HIGH, 25000);
		float distance = duration / 2 * SPEED_OF_SOUND * pow(10, -3); 
		
		if(distance > 1){
			avg += distance/n;
		}else{
		i--;
		}
		delayMicroseconds(10);
	}
	if(avg > MIN_DIST){
		return false;
	}
	return true;
}

bool isFull2(){

	float avg = 0;
	int n = 100;

	for(int i = 0; i < n ; i++){
		digitalWrite(TRIG_PIN_2,HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIG_PIN_2,LOW);
		
		long duration = pulseIn(ECHO_PIN_2, HIGH, 25000);
		float distance = duration / 2 * SPEED_OF_SOUND * pow(10, -3); 
		
		if(distance > 1){
			avg += distance/n;
		}else{
		i--;
		}
		delayMicroseconds(10);
	}
	if(avg > MIN_DIST){
		return false;
	}
	return true;
}


#endif 

