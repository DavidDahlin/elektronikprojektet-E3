#ifndef JSONINFO_HPP
#define JSONINFO_HPP

#include <ArduinoJson.h>


//jsonfilen
const char* json = R"(
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
	}
}
)";



DynamicJsonDocument doc(1024);

void getDoc(){
	DeserializationError error = deserializeJson(doc, json);

	if (error) {
		Serial.print("JSON parsing failed: ");
		Serial.println(error.c_str());
		return;
	}
}

int getMatchDirection(String scannedUID){	
	getDoc();

	for(JsonPair entry: doc.as<JsonObject>()){
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
	getDoc();

	for(JsonPair entry: doc.as<JsonObject>()){
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
