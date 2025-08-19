#include "wifi_utils.h"

void connect_to_wifi() {
  const char* WIFI_NAME = "Knowledge";
  const char* WIFI_PASSWORD = "71434599";

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("WiFi connected! IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("Failed to connect to WiFi.");
  }
}

void create_apn() {
  WiFi.softAP("ESP32_AP", "12345678");
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());
}
