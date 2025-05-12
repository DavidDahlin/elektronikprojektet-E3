#ifndef MOTORS_HPP
#define MOTORS_HPP

const int STEP_PIN_FILL_CAT_1 = 22;
const int STEP_PIN_FILL_CAT_2 = 24;
const int STEP_PIN_ROTATE = 23;

const int DIR_PIN = 25;

const int ENABLE_PIN_ROTATE = 31;
const int ENABLE_PIN_FILL_CAT_1 = 30;
const int ENABLE_PIN_FILL_CAT_2 = 26;

const int MODE0_PIN = 27;
const int MODE1_PIN = 28;
const int MODE2_PIN = 29;

const int PIN_SIGNAL = 8;
const int PIN_DETECT = 9;

const int POS_1 = 537;
const int BASE_SHORT_POS = -48;
const int BASE_LONG_POS = -80;

const int QUART = 100;
const int FILL_SPEED = 12000;
const int FILL_ACC = 10000;

AccelStepper stepper_turn(1, STEP_PIN_ROTATE, DIR_PIN);
AccelStepper stepper_fill_1(1, STEP_PIN_FILL_CAT_1, DIR_PIN);
AccelStepper stepper_fill_2(1, STEP_PIN_FILL_CAT_2, DIR_PIN);

void setupMotor() {
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
  
  stepper_turn.setMaxSpeed(300);
  stepper_turn.setAcceleration(200);

  stepper_fill_1.setMaxSpeed(FILL_SPEED);
  stepper_fill_1.setAcceleration(FILL_ACC);

  stepper_fill_2.setMaxSpeed(FILL_SPEED);
  stepper_fill_2.setAcceleration(FILL_ACC);

  delay(500);
}

void setFillStep() {
  digitalWrite(MODE0_PIN, HIGH);
  digitalWrite(MODE1_PIN, HIGH);
  digitalWrite(MODE2_PIN, LOW);
}

void setTurnStep() {
  digitalWrite(MODE0_PIN, HIGH);
  digitalWrite(MODE1_PIN, HIGH);
  digitalWrite(MODE2_PIN, LOW);
}

int getFillQuarters(double weight) {
  return (int) weight * 60/15;
  // formel för mängd mat i form av kvartar vridna
}


void run(AccelStepper runner) {
  while (!runner.distanceToGo() == 0) {
    runner.run();
  }
}


void oneStepBackTwoStepsForward(AccelStepper filler) {
	filler.moveTo(QUART);
	run(filler);
	filler.moveTo(-2*QUART);
	run(filler);
}

void fill(double weight, int cat) {
	int quarters = getFillQuarters(weight);
	setFillStep();
	if (cat == 1) {
		digitalWrite(ENABLE_PIN_FILL_CAT_1, LOW);
		stepper_fill_1.setCurrentPosition(0);
		stepper_fill_1.moveTo(QUART);
		run(stepper_fill_1);
		for(int i = 0; i < quarters; i++){
			stepper_fill_1.setCurrentPosition(0);
			oneStepBackTwoStepsForward(stepper_fill_1);
		}
		digitalWrite(ENABLE_PIN_FILL_CAT_1, HIGH);
	} else {
		digitalWrite(ENABLE_PIN_FILL_CAT_2, LOW);
		stepper_fill_2.setCurrentPosition(0);
		stepper_fill_2.moveTo(QUART);
		run(stepper_fill_2);
		for(int i = 0; i < quarters; i++){
			stepper_fill_2.setCurrentPosition(0);
			oneStepBackTwoStepsForward(stepper_fill_2);
		}
		digitalWrite(ENABLE_PIN_FILL_CAT_2, HIGH);
	}
}

void turn(int dir) {
	setTurnStep();
	int pos;
	if (dir) {
		stepper_turn.moveTo(POS_1);
		pos = POS_1;
	} else {
		stepper_turn.moveTo(-POS_1);
		pos = -POS_1;
	}
	run(stepper_turn);
	stepper_turn.setCurrentPosition(pos);
}

void turnLive() {

	setTurnStep();
  long currentPos = stepper_turn.currentPosition();
  if (currentPos == POS_1) {
    stepper_turn.moveTo(currentPos + POS_1);
    run(stepper_turn);
    stepper_turn.setCurrentPosition(-POS_1);
    return;
  }

  stepper_turn.moveTo(currentPos - POS_1);
  run(stepper_turn);
  stepper_turn.setCurrentPosition(POS_1);
}

void findBase() {
  setTurnStep();

  if (digitalRead(PIN_DETECT)) {
    stepper_turn.setCurrentPosition(0);
    stepper_turn.moveTo(100);
    run(stepper_turn);
  }

  stepper_turn.setSpeed(-100);

  while (!digitalRead(PIN_DETECT)) {
    stepper_turn.runSpeed();
  }
  stepper_turn.stop();
  stepper_turn.setSpeed(300);
  stepper_turn.setCurrentPosition(BASE_SHORT_POS);
  stepper_turn.moveTo(0);
  run(stepper_turn);
}


void turnToBase() {
  Serial.println(stepper_turn.currentPosition());
  if(stepper_turn.currentPosition()>0){
    findBase();
  }else{
    setTurnStep();

    if (digitalRead(PIN_DETECT)) {
      stepper_turn.setCurrentPosition(0);
      stepper_turn.moveTo(100);
      run(stepper_turn);
    }

    stepper_turn.setSpeed(150);

    while (!digitalRead(PIN_DETECT)) {
    stepper_turn.runSpeed();
    }
    stepper_turn.stop();
    stepper_turn.setSpeed(300);
    stepper_turn.setCurrentPosition(BASE_LONG_POS);
    stepper_turn.moveTo(0);
    run(stepper_turn);
  }

}

#endif
