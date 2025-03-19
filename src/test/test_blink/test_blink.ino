
const int pin = 13;

void setup(){

  pinMode(pin, OUTPUT);

  delay(2000);
  digitalWrite(pin, HIGH);
  delay(2000);
  digitalWrite(pin, LOW);
  delay(2000);
}

void loop(){

  int i;
  for(i = 0; i < 10; i++){
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
  }

}