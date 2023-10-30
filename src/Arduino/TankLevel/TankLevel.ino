#include "config.h"
#include <WiFi.h>
#include <HTTPClient.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
}

void loop() {
  Serial.println();
  Serial.println("Starting measurement");
  int adc_val = analogRead(TANK_LEVEL);
  float depth = (float)adc_val * (float)TANK_ADC_VALUE;
  Serial.print("Depth");
  Serial.println(depth);
  delay(60000);
}
