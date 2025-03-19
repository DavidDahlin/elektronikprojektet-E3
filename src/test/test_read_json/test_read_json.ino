#include <ArduinoJson.h> 



const char* json = R"(
  {
    "Cat1": {
      "uid": "C5 E0 F0 75",
      "mat": 100
	  },
    "Cat2": {
	    "uid": 456,
	    "mat": 200
	  }
  }
)";


void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial connection

  // Allocate memory for parsing (adjust size if needed)
  StaticJsonDocument<256> doc;

  // Parse JSON
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract values from Cat1
  String cat1_uid = doc["Cat1"]["uid"]; // 123
  int cat1_mat = doc["Cat1"]["mat"]; // 100

  // Extract values from Cat2
  int cat2_uid = doc["Cat2"]["uid"]; // 456
  int cat2_mat = doc["Cat2"]["mat"]; // 200

  delay(1000);

  // Print results
  Serial.println("Cat1:");
  Serial.print("UID: ");
  Serial.println(cat1_uid);
  Serial.print("MAT: ");
  Serial.println(cat1_mat);

  Serial.println("\nCat2:");
  Serial.print("UID: ");
  Serial.println(cat2_uid);
  Serial.print("MAT: ");
  Serial.println(cat2_mat);
}

void loop() {
  // Empty
}