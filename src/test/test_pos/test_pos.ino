
#define PIN_SIGNAL 8
#define PIN_DETECT 9


int x;
int sign;

void setup(){
  Serial.begin(115200);
  pinMode(PIN_SIGNAL, OUTPUT);
  pinMode(PIN_DETECT, INPUT);
  digitalWrite(PIN_SIGNAL, HIGH);
  digitalWrite(PIN_DETECT, LOW);
  delay(2000);
  
  

  x = 0;

  
}

void loop(){
  if(digitalRead(PIN_DETECT)){
    Serial.print(x);
    Serial.println(": In position");
    delay(50);

    
    x++;
  }
}
