#include "masterHelpers.h"
int dir;
// float posAcc(float t_d){
//   t_d = t_d / 1e6;
//   float t_min_l = t_min / 1e6;
//   t_d  = 1/(acc_term*t_d + 1/t_d);
//   if (t_d > t_min_l){
//     return t_d*1e6;
//   }
//   return t_min;
// }

// float negAcc(float t_d){
//   t_d = t_d / 1e6;
//   float t_min_l = t_min / 1e6;
//   t_d  = 1/(-acc_term*t_d + 1/t_d);
//   if (t_d < t_min){
//     return t_d*1e6;
//   }
//   return t_min;
// }

// void printTime(float t_d){
//   int x = 1;
//   while(t_d > t_min){
//     Serial.print(x);
//     Serial.print(": Delay t: ");
//     Serial.print(t_d);
//     Serial.print(",   t_min = ");
//     Serial.println(t_min);
//     x++;
//     t_d = posAcc(t_d);
//     delay(10);
//   }
// }

// void printNegAcc(float t_d){
//   int x = 1;
//   float t_min_l = t_min;
//   while(t_min_l < t_d){
//     Serial.print(x);
//     Serial.print(": Delay t: ");
//     Serial.print(t_d);
//     Serial.print(",   t_min = ");
//     Serial.println(t_min_l);
//     x++;
//     t_min_l = negAcc(t_min_l);
//     delay(10);
//   }
// }




void setup(){
  Serial.begin(115200);
  setupMotor();
  setTurnStep();
  // // setFullStep();
  // findBase();
  // printTime(t_d);
  // printNegAcc(1500);
  dir = 1;

  // findBase();
  delay(2000);

}

void loop(){
  // fill(200, 1);
  // int dir = !digitalRead(DIR_PIN);
  // Serial.print("Dir: ");
  // Serial.println(dir);
  // digitalWrite(DIR_PIN, dir);

  

  // turn(dir);

  // turnToBase(dir);

  // turn(dir);
  // delay(10000);

  fill(10, 1);

  // dir = !dir;
  
  // ms(200*8);
  // certStep(5000);
  // delay(5000);

  // turn(dir);


  // dir = !dir;
  // delay(2000);

  // turnLive();
  // delay(2000);

  // turnToBase();
  delay(2000);


}


