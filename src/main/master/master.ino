#include "masterHelpers.h"

const char* ssid;
const char* password;
const long feedingTime = 1000*60*5; //5 minuter i millisekunder
const int nFillings = 3;

double cat1FT[nFillings];
double cat2FT[nFillings]; 
bool resetFill;
int pos;

void fillCatFTArray(char* cs, String cat){ // används bara i resetFillList
  Serial.println(cs);
  char buffer[64];
  strcpy(buffer, cs);
  char* token = strtok(buffer, ",");
  int i = 0;
  while (token != NULL) {
    int hour, minute;
    // sscanf() reads the two ints separated by a colon.
    sscanf(token, " %d:%d", &hour, &minute);
    double fillTime = (double)(hour + (double)minute/60);
    if(fillTime > getTimeDouble()){
      fillTime = 24;
    }
    if(cat.equals("cat1")){
      cat1FT[i] = fillTime;
    }else if(cat.equals("cat2")){
      cat2FT[i] = fillTime;
    }
    token = strtok(NULL, ",");
    i++;
  }
}

void resetFillList(){
  double resetTime = getTimeDouble();
  if(resetTime < 1 && resetTime > 0 && resetFill == true){
    fillCatFTArray(getFillTime("cat1"), "cat1");
    fillCatFTArray(getFillTime("cat2"), "cat2");
    resetFill = false;
  }else if(resetFill = false && resetTime > 23){
    resetFill = true;
  }
}

void fillBowl(){
  double weight;
  double timeDouble = getTimeDouble();
  for(int i = 0; i < nFillings; i++){
    if(cat1FT[i]< 24 && cat1FT[i] < timeDouble){
      if(!isFull1()){
        weight = getFoodweight("cat1");
        fill(weight, 1);
        cat1FT[i] = 24;
      }
    }
    if(cat2FT[i]< 24 && cat2FT[i] < timeDouble){
      if(!isFull2()){
        weight = getFoodweight("cat2");
        fill(weight, 2);
        cat2FT[i] = 24;
      }
    }
  }
}

void midFeedSwitch(String uid){
  int dir = !getMatchDirection(uid);
  if(dir == -1){
    return;
  }
  String otherUid = getOtherCatUID(uid);
  // motorSpinn(dir);
  pos = !dir;
  //control time and search for other cat
  long start = millis();
  while(millis()-start < feedingTime){
    if(quickScanFor(otherUid)){
      //midFeedSwitch(uid);
      return;
    }
  }
  //turnToBase(pos)
}

void feedFromBowl(String uid){
  int dir = getMatchDirection(uid);
  if(dir == -1){
    return;
  }
  String otherUid = getOtherCatUID(uid);
  //motorSpinnRegular(dir);
  pos = dir;
  //control time and search for other cat
  long start = millis();
  while(millis()-start < feedingTime){
    if(quickScanFor(otherUid)){
    //midFeedSwitch(uid);
    return;
    }
  }
  //....
  //turnToBase(pos)
}




void setup() {
  Serial.begin(115200);
  delay(2000);

  ssid = getWifiSSID();
  password = getWifiPassword();
  
  setupI2C();

  while(!i2cSecured());

  sendSSID(ssid);
  sendPassword(password);

  while(!wifiSecured()){
    sendSSID(ssid);
    sendPassword(password);
  } 

  
  fillCatFTArray(getFillTime("cat1"), "cat1");
  fillCatFTArray(getFillTime("cat2"), "cat2");
  resetFill = true;

  // setupReader();
  // setup_avstandsmatare();

  delay(2000);
}

void loop() {
  //for testing
  String t = getTime();
  double d = getTimeDouble();
  Serial.println("time: " + t);
  Serial.print("double time: ");
  Serial.println(d); 



  //Feeding
  // String uid = scanForTags();
  // if(!uid.equals("")){
  //   //feedFromBowl(uid)
  // }

  for(int i = 0; i < nFillings; i++){
    
    // Serial.print(cat1FT[0]);
    // Serial.print(", ");
    // Serial.print(cat1FT[1]);
    // Serial.print(", ");
    // Serial.println(cat1FT[2]);
    // cat1FT[i] = 24;

  
  }
  
  // String uid = scanForTags();
  // if(!uid.equals("")){
  //   Serial.print("Successfully found:");
  //   Serial.println(uid);

  //   int dir = getMatchDirection(uid);
  //   Serial.println(dir);

  // }else{
  //   Serial.println("No tag found");
  // }

  // bool go = isNotFull1();
  // Serial.print("go 1: ");
  // Serial.println(go);
  

  // delay(500);
  // go = isNotFull2();
  // Serial.print("go 2: ");
  // Serial.println(go);

  // avstand_test();
  
  //hamta nya tider för matning
  resetFillList();
  


  delay(2000);
  
}
