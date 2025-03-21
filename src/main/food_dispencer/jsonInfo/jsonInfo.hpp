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
		"dir": 1 
	},
	"cat2": {
		"name": "Cocos",
		"uid": "4e 5d d0 6f",
		"food weight, grams": 200,
		"dir": 0
	},	
	"wifi": {
		"ssid" = "...",
		"password" = "..."
	}
}
)";


const char* wifiJson = R"(
{	
	"wifi": {
		"ssid" = "...",
		"password" = "..."
	}
}
)";




DynamicJsonDocument catDoc(1024);
DynamicJsonDocument wifiDoc(1024);

void getCatDoc(){
	DeserializationError error = deserializeJson(catDoc, catJson);

	if (error) {
		Serial.print("JSON parsing failed: ");
		Serial.println(error.c_str());
		return;
	}
}

void getwifiDoc(){
	DeserializationError error = deserializeJson(wifiDoc, wifiJson);

	if (error) {
		Serial.print("JSON parsing failed: ");
		Serial.println(error.c_str());
		return;
	}
}

int getMatchDirection(String scannedUID){	
	getCatDoc();

	for(JsonPair entry: catDoc.as<JsonObject>()){
		const char* storedUID = entry.value()["uid"].as<const char*>();
		int dir = entry.value()["dir"].as<int>();
		
		String storedUIDString= String(storedUID);
		storedUIDString.toLowerCase();

		if(scannedUID.equals(storedUIDString)){
			return dir;
		}
	}

	return -1;
}


int getFoodweight(String cat){	
	
	getCatDoc();

	for(JsonPair entry: catDoc.as<JsonObject>()){
		const char* storedCat = entry.key().c_str();
		int foodWeight = entry.value()["food weight, grams"].as<int>();
		
		String storedCatString = String(storedCat);
		storedCatString.toLowerCase();

		if(cat.equals(storedCatString)){
			return foodWeight;
		}
	}

	return -1;
}




#endif
