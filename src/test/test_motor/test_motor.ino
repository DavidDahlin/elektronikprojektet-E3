
#define STEP_PIN 3
#define DIR_PIN 4
#define ENABLE_PIN 7

#define MODE0_PIN 10
#define MODE1_PIN 11
#define MODE2_PIN 12






const int stepsPer180 = 100; // Adjust based on microstepping (100 for full step)

void movestepper(int steps){
  for(int i = 0; i < steps; i++){
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500); //För ett varv per sekund
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);
  }
}

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(MODE0_PIN, OUTPUT);
  pinMode(MODE1_PIN, OUTPUT);
  pinMode(MODE2_PIN, OUTPUT);

  digitalWrite(DIR_PIN, LOW);
  
  digitalWrite(ENABLE_PIN, HIGH);
  delay(100);
  digitalWrite(ENABLE_PIN, LOW);

  //Sätter stegen till 1/8
  digitalWrite(MODE0_PIN, HIGH);
  digitalWrite(MODE1_PIN, HIGH);
  digitalWrite(MODE2_PIN, LOW);
}

void loop() {
  // Rotate 180 degrees clockwise
  
  int n = int(8*360/1.8/3);

  movestepper(n);
  delay(2000);
  digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));

  
}