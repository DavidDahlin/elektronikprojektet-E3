#include <SoftwareSerial.h>
SoftwareSerial espSerial(0, 1); // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  // Send "Hello from Arduino" to ESP32 every 1 second
  espSerial.println("Hello from Arduino");
  delay(1000);

  // Check for incoming data from ESP32
  if (espSerial.available()) {
    String response = espSerial.readStringUntil('\n');
    Serial.print("ESP32 says: ");
    Serial.println(response);
  }
}