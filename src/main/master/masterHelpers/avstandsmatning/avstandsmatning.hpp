#ifndef AVSTANDSMATNING_HPP
#define AVSTANDSMATNING_HPP

#include <math.h>

#define TRIG_PIN_2 44
#define TRIG_PIN_1 46
#define ECHO_PIN_2 45
#define ECHO_PIN_1 47


const float SPEED_OF_SOUND = 343;
const float MIN_DIST_1 = 7.69 + 1;
const float MIN_DIST_2 = 8.2 + 1;

class distSensor{
	public:
		int trigPin;
		int echoPin;
		float minDist;
		
		distSensor(int trigPin, int echoPin, float minDist){
			this->trigPin = trigPin;
			this->echoPin = echoPin;
			this->minDist = minDist;	
		}
		
		void setupPins(){
			pinMode(trigPin, OUTPUT);
			pinMode(echoPin, INPUT);
			digitalWrite(trigPin, LOW);
			digitalWrite(echoPin, LOW);
		}
		
		float getDistance(){
			float avg = 0;
			int n  = 50;
			float dur;
			float dis;
			for(int i = 0; i < n; i++){
				digitalWrite(trigPin, HIGH);
				delayMicroseconds(10);
				digitalWrite(trigPin, LOW);
				dur = pulseIn(echoPin, HIGH) * 1e-6;
				dis = dur * SPEED_OF_SOUND /2 * 100;//cm 
				avg += dis/n;
			}
			return avg;
		}

		bool isFull(){
			if(getDistance() < minDist){
				return true;
			}
			return false;
		}
		
};


distSensor ds1(TRIG_PIN_1,ECHO_PIN_1, MIN_DIST_1);
distSensor ds2(TRIG_PIN_2,ECHO_PIN_2, MIN_DIST_2);
	
void setup_avstandsmatare(){
	ds1.setupPins();
	ds2.setupPins();
}


float getDistance(int nr){
	float avg;
	if(nr == 1){
		avg = ds1.getDistance();
	}else{
		avg = ds2.getDistance();
	}
	return avg;
}

bool isFull(int nr){
	if(nr == 1){
		return ds1.isFull();
	}
	return ds2.isFull();
}

#endif
