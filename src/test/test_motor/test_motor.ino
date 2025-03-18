const int dirPin = 4;      // Direction pin
const int stepPin = 1;     // Step pin
const int stepsPer180 = 100; // Adjust based on microstepping (100 for full step)

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void loop() {
  // Rotate 180 degrees clockwise
  digitalWrite(dirPin, HIGH); // Set direction (HIGH or LOW may vary)
  for (int i = 0; i < stepsPer180; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10);   // Minimum pulse width for DRV8825
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10); // Adjust delay to control speed (smaller = faster)
  }

  delay(1000); // Pause between movements

  // Rotate 180 degrees counter-clockwise
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < stepsPer180; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10);
  }

  delay(10); // Pause before repeating
}