#include "config.h"
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;


void setup() {
  Serial.begin(115200);
  Serial.println("Starting");

  // Set up a GPIO pin for powering the sensor
  pinMode(SOIL_POWER, OUTPUT);

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

}

void loop() {
  // Power up the sensor
  digitalWrite(SOIL_POWER, HIGH);
  delay(1000);    // Wait for it to stabilise

  String data = "{\"host\": \"";
  data += deviceName;
  data += "\"sourcetype\": \"datafarm\",";
  data += "\"index\": \"datafarm\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"";
  data += sensorType;
  data += "\"moisture\": \"" + String(analogRead(SOIL_PIN)) + "\",";
  data += "\"battery\": \"" + String(analogRead(BATTERY_PIN)) + "\"";
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
  
  digitalWrite(SOIL_POWER, LOW);  // Sensor shutdown

  delay(1000 * 59);
}