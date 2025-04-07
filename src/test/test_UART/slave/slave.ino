// HardwareSerial Serial1(1); // Use UART1

void setup() {
  // Serial.begin(9600); // For debugging
  // Serial1.begin(9600, SERIAL_8N1, 18, 17); // Baud, config, RX, TX
}

void loop() {
  // // Check for incoming data from Arduino
  // if (Serial1.available()) {
  //   String message = Serial1.readStringUntil('\n');
  //   Serial.print("Arduino says: ");
  //   Serial.println(message);

  //   // Send reply to Arduino
  //   Serial1.println("Hello from ESP32");
  // }
}