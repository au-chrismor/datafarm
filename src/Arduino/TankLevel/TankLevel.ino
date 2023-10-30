#include "config.h"
#include <WiFi.h>
#include <HTTPClient.h>

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#ifdef _DEBUG
  Serial.println("Connecting");
#endif
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
#ifdef _DEBUG
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
#endif
}

void loop() {
}
