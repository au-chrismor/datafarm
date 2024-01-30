#include <ESP8266WiFi.h>
#include "config.h"

const char* ssid = STASSID;
const char* password = STAPSK;


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Local Address: ");
  Serial.println(WiFi.macAddress());
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  int analog_0 = analogRead(DEPTH_SENSOR);
  float level = (float)analog_0 * DEPTH_CALC_VAL;
  Serial.print("Analog: ");
  Serial.println(analog_0);
  Serial.print("Depth: ");
  Serial.println(level);
  String data = "{\"host\": \"tankmonitor1\",";
  data += "\"sourcetype\": \"datafarm\",";
  data += "\"index\": \"datafarm\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"tankdepth\",";
  data += "\"level\": \"" + String(analog_0) + "\"";
  data += "}}";
  Serial.print("Connecting to: ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);
  WiFiClient client;
  if(client.connect(host, port)) {
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
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000 * 60);
}
