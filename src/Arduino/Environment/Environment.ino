#include "config.h"
#ifdef HAS_ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif
#ifdef HAS_ESP8266
#include <ESP8266WiFi.h>
#endif
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

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
  Serial.print("Local Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("BME280 Startup");
  bool bme_status = bme.begin(BME_ADDRESS);
  if(!bme_status) {
    Serial.println("BME280 Not found");
    while(1);
  }
}

void loop() {
  Serial.println();
  Serial.println("Starting measurement");
  int adc_val = analogRead(BATTERY_VOLTS);
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure();
  
  String data = "{\"host\": \"" + String(HOST_NAME) + "\",";
  data += "\"sourcetype\": \"" + String(SOURCE_TYPE) + "\",";
  data += "\"index\": \"" + String(INDEX_NAME) + "\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"" + String(SENSOR_TYPE) + "\",";
  data += "\"temperature\": \"" + String(temperature) + "\",";
  data += "\"humidity\": \"" + String(humidity) + "\",";
  data += "\"pressure\": \"" + String(pressure) + "\",";
  data += "\"battery\": \"" + String(adc_val) + "\",";
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
