#ifndef AVSTANDSMATNING_HPP
#define AVSTANDSMATNING_HPP

#include <math.h>

#define TRIG_PIN 12
#define ECHO_PIN_1 11
#define ECHO_PIN_2 10

const float SPEED_OF_SOUND = 343;

void setup_avstandsmatare(){
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN_1, INPUT);
	pinMode(ECHO_PIN_2, INPUT);
	digitalWrite(TRIG_PIN, LOW);
}

void avstand_test(){
	digitalWrite(TRIG_PIN,HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN,LOW);

	long duration_1 = pulseIn(ECHO_PIN_1, HIGH, 25000);

	delay(500);
	digitalWrite(TRIG_PIN,HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN,LOW);

	long duration_2 = pulseIn(ECHO_PIN_2, HIGH, 25000);

	float distance_1 = duration_1 / 2 * SPEED_OF_SOUND * pow(10, -3);
	/*float distance_1 = duration_1 *0.1715;*/

	float distance_2 = duration_2 / 2 * SPEED_OF_SOUND * pow(10, -3);
	/*float distance_2 = duration_2 *0.1715;*/

	Serial.print("Distance 1: ");
	Serial.print(distance_1);
	Serial.println(" mm");
	
	delay(500);
	Serial.print("Distance 2: ");
	Serial.print(distance_2);
	Serial.println(" mm");

	delay(500);
}

float getDistance1(){
	float avg = 0;

	int i;
	int n = 10;

	for(i = 0; i < n ; i++){
		digitalWrite(TRIG_PIN,HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIG_PIN,LOW);
		
		long duration = pulseIn(ECHO_PIN_1, HIGH, 25000);
		float distance = duration / 2 * SPEED_OF_SOUND * pow(10, -3); 
		
		if(distance > 1){
			avg += distance/n;
		}else{
		i--;
		}
	}

	return avg;

}

#endif 

