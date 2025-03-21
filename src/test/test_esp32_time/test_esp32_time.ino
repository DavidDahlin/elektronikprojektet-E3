
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "Dawifi";
const char* password = "dahlin01";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000); // UTC+1

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  // Start NTP client
  timeClient.begin();
  timeClient.update(); // Fetch current time
}

void loop() {
  timeClient.update(); // Refresh time (optional)
  
  // Get epoch time (seconds since 1970-01-01)
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch time: ");
  Serial.println(epochTime);

  // Get formatted time (HH:MM:SS)
  String formattedTime = timeClient.getFormattedTime();
  int hour = timeClient.getHours();
  Serial.print("Formatted time: ");
  Serial.println(formattedTime);
  Serial.print("Hours: ");
  Serial.println(hour);

  delay(1000); // Wait 1 second
}