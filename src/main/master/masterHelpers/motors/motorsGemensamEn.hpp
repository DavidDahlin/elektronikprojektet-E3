#ifndef MOTORS_HPP
#define MOTORS_HPP

const int STEP_PIN_FILL_CAT_1 = 22;
const int STEP_PIN_FILL_CAT_2 = 23;
const int STEP_PIN_ROTATE = 24;

const int DIR_PIN = 25;
const int ENABLE_PIN = 26;

const int MODE0_PIN = 27;
const int MODE1_PIN = 28;
const int MODE2_PIN = 29;

const int fillingMicroSecondsDelay = 2500;
const int turnMicroSecondsDelay = 151515; //(10 000 000) / (120/1.8/2 * 2) 

double step;

void setupMotor(){
	pinMode(STEP_PIN_FILL_CAT_1, OUTPUT);
	pinMode(STEP_PIN_FILL_CAT_2, OUTPUT);
	pinMode(STEP_PIN_ROTATE, OUTPUT);

	pinMode(DIR_PIN, OUTPUT);

	pinMode(ENABLE_PIN, OUTPUT);

	pinMode(MODE0_PIN, OUTPUT);
	pinMode(MODE1_PIN, OUTPUT);
	pinMode(MODE2_PIN, OUTPUT);

	digitalWrite(ENABLE_PIN, HIGH);
	digitalWrite(STEP_PIN_FILL_CAT_1, LOW);
	digitalWrite(STEP_PIN_FILL_CAT_2, LOW);
	digitalWrite(STEP_PIN_ROTATE, LOW);
	
	delay(500);
	digitalWrite(ENABLE_PIN, LOW);
}

void setFullStep(){
	digitalWrite(MODE0_PIN, LOW);
	digitalWrite(MODE1_PIN, LOW);
	digitalWrite(MODE2_PIN, LOW);
	step = 100;  
}

void setTurnStep(){//Testa fram senare	
	//half step
	digitalWrite(MODE0_PIN, HIGH);
	digitalWrite(MODE1_PIN, LOW);
	digitalWrite(MODE2_PIN, LOW);
	step = 50;//100/2  
}

int getFillSteps(double weight){
	return 1000;
	// formula for getting the right amount of food
}

void moveStepper(int steps, int microSecondsDelay, int stepPin){
	for(int i = 0; i < steps; i++){
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(microSecondsDelay); //För ett varv per sekund
		digitalWrite(stepPin, LOW);
		delayMicroseconds(microSecondsDelay);
	}
}

void fill(double weight, int cat){
	int stepPin;
	if(cat == 1){
		stepPin = STEP_PIN_FILL_CAT_1;
	} else{
		stepPin = STEP_PIN_FILL_CAT_2;
	}
	setFullStep();
	//digitalWrite(DIR_PIN, XXX);
	int steps = getFillSteps(weight);
	moveStepper(steps, fillingMicroSecondsDelay, stepPin);

} 

void turn(int dir){	
	setTurnStep();
	digitalWrite(DIR_PIN, dir);
	
	int steps = 133; //33 halfSteps = 120
	moveStepper(steps, turnMicroSecondsDelay, STEP_PIN_ROTATE);
}
void turnToBase(int pos){
	int dir = !pos; 
	turn(dir);
}





#endif
