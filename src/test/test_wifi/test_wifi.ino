
#define LED 13

void  setup(){
  pinMode(LED, OUTPUT);
  
  digitalWrite(LED, LOW);
  delay(1000);
  digitalWrite(LED, 1);
  delay(3000);
  digitalWrite(LED, 0);
  delay(5000);
  digitalWrite(LED, LOW);
}


void loop(){

}