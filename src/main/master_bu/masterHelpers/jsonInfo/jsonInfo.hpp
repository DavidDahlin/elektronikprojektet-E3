#ifndef JSONINFO_HPP
#define JSONINFO_HPP

#include <ArduinoJson.h>


//jsonfilen
const char* catJson = R"(
{
	"cat1": {
		"name": "Milo",
		"uid": "C5 e0 f0 75",
		"food weight, grams": 100,
		"dir": 1,
		"fill time":"12:13, 12:14, 16:00"
	},
	"cat2": {
		"name": "Cocos",
		"uid": "4e 5d d0 6f",
		"food weight, grams": 200,
		"dir": 0,
		"fill time":"08:50, 12:30, 18:50"
	}
}
)";


const char* wifiJson = R"(
{
	"wifi": {
		"ssid": "dawifi",
		"password": "dahlin01"
	}
}
)";

StaticJsonDocument<256> catDoc;
StaticJsonDocument<256> wifiDoc;
// DynamicJsonDocument catDoc(1024);
// DynamicJsonDocument wifiDoc(1024);



void getCatDoc(){
	DeserializationError error = deserializeJson(catDoc, catJson);

	if (error) {
		Serial.print("JSON parsing failed: ");
		Serial.println(error.c_str());
		return;
	}
}

void getWifiDoc(){
	DeserializationError error = deserializeJson(wifiDoc, wifiJson);

	if (error) {
		Serial.print("JSON parsing failed: ");
		Serial.println(error.c_str());
		return;
	}
}

void setupJSON(){
	getWifiDoc();
	getCatDoc();
}


int getMatchDirection(String scannedUID){	
	for(JsonPair entry: catDoc.as<JsonObject>()){
		const char* storedUID = entry.value()["uid"].as<const char*>();
		int dir = entry.value()["dir"].as<int>();
		
		String storedUIDString= String(storedUID);
		storedUIDString.toLowerCase();

		if(scannedUID.equals(storedUIDString)){
			Serial.println("matched uid found, direction returned");
			return dir;
		}
	}
	
	Serial.println("matched uid not found, -1 returned");
	return -1;
}

String getOtherCatUID(String scannedUID){
	for(JsonPair entry: catDoc.as<JsonObject>()){
		const char* storedUID = entry.value()["uid"].as<const char*>();
		
		String storedUIDString= String(storedUID);
		storedUIDString.toLowerCase();

		if(!scannedUID.equals(storedUIDString)){
			Serial.println("Othercat uid: " + storedUIDString + ", found");
			return storedUIDString;
		}
	}
	Serial.println("Other cat uid not found");
	return "";
}

double getFoodweight(String cat){	
	for(JsonPair entry: catDoc.as<JsonObject>()){
		const char* storedCat = entry.key().c_str();
		double foodWeight = entry.value()["food weight, grams"].as<double>();
		
		String storedCatString = String(storedCat);
		storedCatString.toLowerCase();

		if(cat.equals(storedCatString)){
			return foodWeight;
		}
	}
	return -1;
}

const char* getFillTime(String cat){
	for(JsonPair entry: catDoc.as<JsonObject>()){
		const char* storedCat = entry.key().c_str();
		const char* fillTime = entry.value()["fill time"].as<const char*>();
		
		String storedCatString = String(storedCat);
		storedCatString.toLowerCase();

		if(cat.equals(storedCatString)){
			return fillTime;
		}
	}
}


const char* getWifiSSID(){
	for(JsonPair entry: wifiDoc.as<JsonObject>()){
		const char* ssid = entry.value()["ssid"].as<const char*>();

		return ssid;
	}
	Serial.print("Något gick snett med att hämta ssid");
	return NULL;
}

const char* getWifiPassword(){
	for(JsonPair entry: wifiDoc.as<JsonObject>()){
		const char* password = entry.value()["password"].as<const char*>();

		return password;
	}
	Serial.print("Något gick snett med att hämta password");
	return NULL;
}


#endif
