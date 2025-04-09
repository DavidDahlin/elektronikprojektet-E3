#ifndef MOTORS_HPP
#define MOTORS_HPP

const int STEP_PIN = 22;
const int DIR_PIN = 23;

const int ENABLE_PIN_FILL_CAT_1 = 24;
const int ENABLE_PIN_FILL_CAT_2 = 25;
const int ENABLE_PIN_ROTATION_MOTOR = 26;

const int MODE0_PIN = 27;
const int MODE1_PIN = 28;
const int MODE2_PIN = 29;

const int fillingMicroSecondsDelay = 2500;
const int turnMicroSecondsDelay = 151515; //(10 000 000) / (120/1.8/2 * 2) 

double step;

void setupMotor(){
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);

	pinMode(ENABLE_PIN_FILL_CAT_1, OUTPUT);
	pinMode(ENABLE_PIN_FILL_CAT_2, OUTPUT);
	pinMode(ENABLE_PIN_ROTATION_MOTOR, OUTPUT);

	pinMode(MODE0_PIN, OUTPUT);
	pinMode(MODE1_PIN, OUTPUT);
	pinMode(MODE2_PIN, OUTPUT);

	digitalWrite(ENABLE_PIN_FILL_CAT_1, HIGH);
	digitalWrite(ENABLE_PIN_FILL_CAT_2, HIGH);
	digitalWrite(ENABLE_PIN_ROTATION_MOTOR, HIGH);
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

void moveStepper(int steps, int microSecondsDelay){
	for(int i = 0; i < steps; i++){
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(2500); //För ett varv per sekund
		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(2500);
	}
}

void fill(double weight, int cat){
	if(cat == 1){
		digitalWrite(ENABLE_PIN_FILL_CAT_1, LOW);
	} else{
		
		digitalWrite(ENABLE_PIN_FILL_CAT_2, LOW);
	}
	setFullStep();
	//digitalWrite(DIR_PIN, XXX);
	int steps = getFillSteps(weight);
	moveStepper(steps, fillingMicroSecondsDelay);

	if(cat == 1){//Disables 
		digitalWrite(ENABLE_PIN_FILL_CAT_1, HIGH);
	} else{		
		digitalWrite(ENABLE_PIN_FILL_CAT_2, HIGH);
	}
} 

void turn(int dir){	
	digitalWrite(ENABLE_PIN_ROTATION_MOTOR, LOW);
	setTurnStep();
	digitalWrite(DIR_PIN, dir);
	
	int steps = 33; //33 halfSteps = 120
	moveStepper(steps, turnMicroSecondsDelay); 
	

	digitalWrite(ENABLE_PIN_ROTATION_MOTOR, HIGH);//reset
}
void turnToBase(int pos){
	int dir = !pos; 
	turn(dir);
}





#endif
