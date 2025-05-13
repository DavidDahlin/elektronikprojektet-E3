#include "masterHelpers.h"

const char* ssid;
const char* password;
const long feedingTime = 1000*10; //10 s i millisekunder
const int nFillings = 3;

double cat1FT[nFillings];
double cat2FT[nFillings]; 
bool resetFill;

int state;

String uid;

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
    Serial.print(cat + " feeding time n.");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(fillTime);
    if(fillTime < getTimeDouble()){
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
      if(!isFull(1)){
        Serial.println("Cat 1 fill, started");
        weight = getFoodweight("cat1");
        fill(weight, 1);
        marioPlayMusic();
        cat1FT[i] = 24;
      }
    }
    if(cat2FT[i]< 24 && cat2FT[i] < timeDouble){
      if(!isFull(2)){
        Serial.println("Cat 2 fill, started");
        weight = getFoodweight("cat2");
        fill(weight, 2);
        crayFrogPlayMusic();
        cat2FT[i] = 24;
      }
    }
  }
}

void feedLive(String uid){
  String otherUid = getOtherCatUID(uid);
  turnLive();
  long start = millis();
  while(millis()-start < feedingTime){
    if(quickScanFor(otherUid)){
      feedLive(otherUid);
      return;
    }
  }
  turnToBase();
}

void feed(String uid){
  int dir = getMatchDirection(uid);
  if(dir == -1){
    return;
  }
  String otherUid = getOtherCatUID(uid);
  turn(dir);
  //control time and search for other cat
  long start = millis();
  while(millis()-start < feedingTime){
    if(quickScanFor(otherUid)){
    feedLive(otherUid);
    return;
    }
  }
  turnToBase();
}

void getWifiInfo(){

}


void setup(){
  delay(5000); // Vänta på att esp ska komma igång.
  Serial.begin(115200);
  delay(2000);
  

  
  setupI2C();
  setupMotor();
  setup_avstandsmatare();
  setupJSON();

  
  setupReader();
 
  delay(2000);

  // scanForTags(10000);//TA bort

  ssid = getWifiSSID();
  Serial.print("SSID: ");
  Serial.println(ssid);

  password = getWifiPassword();
  Serial.print("Password: ");
  Serial.println(password);
  
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

  // crayFrogPlayMusic();
  windowsPlayMusic();

  findBase();
  
  delay(2000);
  

}

void loop(){


  bool one = isFull(1);
  Serial.print("Is full:");
  Serial.println(one);

  uid = scanForTags(5000);
  Serial.print("uid: ");
  Serial.println(uid);

  if(!uid.equals("")){
    Serial.println("RFID detected"); 
    feed(uid);
  }

  fillBowl();
  resetFillList();

  Serial.print("Time: ");
  Serial.println(getTimeDouble());


}


