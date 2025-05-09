#ifndef MOTORS_HPP
#define MOTORS_HPP

//WARNING: HAr bytt mellan rotate och step 2
const int STEP_PIN_FILL_CAT_1 = 22;
const int STEP_PIN_FILL_CAT_2 = 24;
const int STEP_PIN_ROTATE = 23;

const int DIR_PIN = 25;

//WARNING: HAr bytt mellan rotate och step 2
const int ENABLE_PIN_ROTATE = 31;
const int ENABLE_PIN_FILL_CAT_1 = 30;
const int ENABLE_PIN_FILL_CAT_2 = 26;

const int MODE0_PIN = 27;
const int MODE1_PIN = 28;
const int MODE2_PIN = 29;

const int PIN_SIGNAL = 8;
const int PIN_DETECT= 9;

const int fillingMicroSecondsDelay = 500;
const int turnMicroSecondsDelay = 12000; //(10 000 000) / (120/1.8/2 * 2) 

//FIX: TESTA DESSA
const int BASE_LONG_POS = -100; 
const int BASE_SHORT_POS  = -80; 


AccelStepper stepper(1, STEP_PIN_ROTATE, DIR_PIN);


void setupMotor(){
	pinMode(STEP_PIN_FILL_CAT_1, OUTPUT);
	pinMode(STEP_PIN_FILL_CAT_2, OUTPUT);
	pinMode(STEP_PIN_ROTATE, OUTPUT);

	pinMode(DIR_PIN, OUTPUT);

	pinMode(ENABLE_PIN_ROTATE, OUTPUT);
	pinMode(ENABLE_PIN_FILL_CAT_1, OUTPUT);
	pinMode(ENABLE_PIN_FILL_CAT_2, OUTPUT);

	pinMode(MODE0_PIN, OUTPUT);
	pinMode(MODE1_PIN, OUTPUT);
	pinMode(MODE2_PIN, OUTPUT);
	
	pinMode(PIN_SIGNAL, OUTPUT);
	pinMode(PIN_DETECT, INPUT);

	digitalWrite(ENABLE_PIN_ROTATE, HIGH);
	digitalWrite(ENABLE_PIN_FILL_CAT_1, HIGH);
	digitalWrite(ENABLE_PIN_FILL_CAT_2, HIGH);

	digitalWrite(STEP_PIN_FILL_CAT_1, LOW);
	digitalWrite(STEP_PIN_FILL_CAT_2, LOW);
	digitalWrite(STEP_PIN_ROTATE, LOW);

	
	digitalWrite(PIN_SIGNAL, HIGH);
	digitalWrite(PIN_DETECT, LOW);

	digitalWrite(ENABLE_PIN_ROTATE, LOW);

	stepper.setMaxSpeed(300);
	stepper.setAcceleration(200);
	
	delay(500);
}


void setFullStep(){
	digitalWrite(MODE0_PIN, LOW);
	digitalWrite(MODE1_PIN, LOW);
	digitalWrite(MODE2_PIN, LOW);
}

void setTurnStep(){//Testa fram senare	
	digitalWrite(MODE0_PIN, HIGH);
	digitalWrite(MODE1_PIN, HIGH);
	digitalWrite(MODE2_PIN, LOW);
}




int getFillSteps(double weight){
	return 1000;
	// formula for getting the right amount of food
}

void moveStepper(int steps, int microSecondsDelay, int stepPin){

	for(int i = 0; i < steps; i++){
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(microSecondsDelay);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(microSecondsDelay);
	}
}

void fill(double weight, int cat){
	int stepPin;
	int steps = getFillSteps(weight);
	setFullStep();

	if(cat == 1){
		
		digitalWrite(ENABLE_PIN_FILL_CAT_1, LOW);
		stepPin = STEP_PIN_FILL_CAT_1;
		moveStepper(steps, fillingMicroSecondsDelay, STEP_PIN_FILL_CAT_1);
		digitalWrite(ENABLE_PIN_FILL_CAT_1, HIGH);
	} else{
		digitalWrite(ENABLE_PIN_FILL_CAT_2, LOW);
		stepPin = STEP_PIN_FILL_CAT_2;
		moveStepper(steps, fillingMicroSecondsDelay, STEP_PIN_FILL_CAT_2);
		digitalWrite(ENABLE_PIN_FILL_CAT_2, LOW);
	}

} 

void turn(int dir){

	if(dir){
		stepper.moveTo(533);
	}else{
		stepper.moveTo(-533);
	}

	stepper.run();
	
}

void findBase(){
	setTurnStep();
	
	if(digitalRead(PIN_DETECT)){
		stepper.setCurrentPosition(0);	
		stepper.moveTo(300);
		stepper.run();
	}	

	stepper.setSpeed(-100); 

	while(!digitalRead(PIN_DETECT)){
		stepper.runSpeed();
	}
	stepper.stop();
	stepper.setSpeed(300);
	stepper.setCurrentPosition(0);
	stepper.moveTo(80);
	stepper.run();
	stepper.setCurrentPosition(0);
}

void turnToBase(int pos){
	
	setTurnStep();
	// int dir = pos;
	// digitalWrite(DIR_PIN, dir);
	// while(!digitalRead(PIN_DETECT)) {
	// 	moveStepper(2, turnMicroSecondsDelay, STEP_PIN_ROTATE);
	// }
	// if(dir){
	// 	moveStepper(STEPS_TO_BASE_DIR_LONG, turnMicroSecondsDelay, STEP_PIN_ROTATE);
	// }else{
	// 	digitalWrite(DIR_PIN,!dir);
	// 	moveStepper(STEPS_TO_BASE_DIR_SHORT, turnMicroSecondsDelay, STEP_PIN_ROTATE);
	// }
	//

	stepper.moveTo(0);
	stepper.run();
}





#endif
