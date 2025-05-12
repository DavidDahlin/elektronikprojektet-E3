#ifndef WIFI_HPP
#define WIFI_HPP

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000); // pool.ntp.org (närmaste ntp server)

bool setupWifi(String ssid, String password){
	WiFi.begin(ssid, password);
	
	unsigned long startTime = millis();
	const unsigned long timeout = 20000; // 20 seconds in milliseconds
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
		if (millis() - startTime > timeout) {
			Serial.println("Something went wrong while connecting to wifi, check ssid and password");
			return false; // Time exceeded 20 seconds
		}
	}
	Serial.println("\nWi-Fi connected!");

	// Start NTP client
	timeClient.begin();
	timeClient.update(); // Fetch current time
	Serial.println("timeClient begun");

	return true;
}

bool isConnectedToWiFi() {
	return (WiFi.status() == WL_CONNECTED);
}

String getTime(){
	timeClient.update(); // Refresh time (optional)
	String formattedTime = timeClient.getFormattedTime();
	Serial.println("time: "+ formattedTime);
	return formattedTime;
}

#endif
