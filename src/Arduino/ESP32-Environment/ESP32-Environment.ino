#include "config.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <Wire.h>
#include <BME280I2C.h>

WiFiMulti WiFiMulti;
BME280I2C bme;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting");

  // Initialise the WiFi Connection
  WiFiMulti.addAP(STASSID, STAPSK);
  Serial.print("Waiting for WiFi (");
  Serial.print(STASSID);
  Serial.print(")");
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);

  // Initialise the BME280BME280::PresUnit presUnit(BME280::PresUnit_Pa);
  Serial.println("BME280 Startup");
  Wire.begin();
  while(!bme.begin()) {
    Serial.println("Looking for BME280");
    delay(1000);
  }
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);
}

void loop() {
  String data = "{\"host\": \"";
  data += deviceName;
  data += "\"sourcetype\": \"datafarm\",";
  data += "\"index\": \"datafarm\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"";
  data += sensorType;
  data += "\"temperature\": \"" + String(bme.temp()) + "\",";
  data += "\"humidity\": \"" + String(bme.pres()) + "\",";
  data += "\"pressure\": \"" + String(bme.hum()) + "\"";
  data += "}}";

  WiFiClient client;
  Serial.print("Connecting to ");
  Serial.println(host);x`
  if (client.connect(host, port)) {
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
  delay(1000 * 60);
}
