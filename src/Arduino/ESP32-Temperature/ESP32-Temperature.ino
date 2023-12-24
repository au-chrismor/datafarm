#include "config.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <OneWire.h>
#include <DallasTemperature.h>

WiFiMulti WiFiMulti;
OneWire oneWire(ONEWIRE_PIN);
DallasTemperature sensors(&oneWire);


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

  // Start up the DS18B20
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  String data = "{\"host\": \"temperature1\",";
  data += "\"sourcetype\": \"datafarm\",";
  data += "\"index\": \"datafarm\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"temperature\",";
  data += "\"temperature\": \"" + String(sensors.getTempCByIndex(0)) + "\",";
  data += "\"battery\": \"-1\"";
  data += "}}";

  WiFiClient client;
  Serial.print("Connecting to ");
  Serial.println(host);
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
