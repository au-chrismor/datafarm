#include "config.h"
#ifdef HAS_ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif
#ifdef HAS_ESP8266
#include <ESP8266WiFi.h>
#endif


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("WiFi Status: ");
    Serial.println(WiFi.status());
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
  String data = "{\"host\": \"tankmonitor1\",";
  data += "\"sourcetype\": \"datafarm\",";
  data += "\"index\": \"datafarm\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"tankdepth\",";
  data += "\"depth\": \"" + String(adc_val) + "\"";
  data += "}}";

  Serial.print("Connecting to: ");
  Serial.print(SPLUNK_HOST);
  Serial.print(":");
  Serial.println(SPLUNK_PORT);
  WiFiClient client;
  if(client.connect(SPLUNK_HOST, SPLUNK_PORT)) {
    Serial.println("Connected");
    String url = "/services/collector/event";
    client.println("POST " + url + " HTTP/1.1");
    client.println(SPLUNK_TOKEN);
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    client.println();
    delay(100);
    if(client.connected()) {
      client.flush();
      client.stop();
    }
  }
  else {
    Serial.println("Connect failed");
  }

  delay(60000);
}
