#include "masterHelpers.h"

void setup(){

  setupMotor();

}

void loop(){
  turn(0);
  turnToBase(0);
  turn(1);
  turnToBase(1);
  fill(100, 1);
  fill(200, 2);


  delay(1000);

}
