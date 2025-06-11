#include "config.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <TinyGPS.h>

WiFiMulti WiFiMulti;

HardwareSerial gpsSerial(2);
TinyGPS gps;


void setup() {
  Serial.begin(115200);
  Serial.println("Starting");
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);

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
  float latitude = 0.0;
  float longitude = 0.0;
  float altitude = 0.0;
  float heading = 0.0;
  float speed = 0.0;
  unsigned long satellites = 0;
  unsigned long age = 0;

  while(gpsSerial.available() > 0)
    {gps.encode(gpsSerial.read());
  }

  gps.f_get_position(&latitude, &longitude, &age);
  satellites = gps.satellites();
  speed = gps.f_speed_kmph();
  altitude = gps.f_altitude();
  heading = gps.f_course();

  String data = "{\"host\": \"";
  data += deviceName;
  data += "\",";
  data += "\"sourcetype\": \"datafarm\",";
  data += "\"index\": \"datafarm\",";
  data += "\"event\": {";
  data += "\"sensortype\": \"";
  data += sensorType;
  data += "\",";
  data += "\"latitude\": \"" + String(latitude) + "\",";
  data += "\"longitude\": \"" + String(longitude) + "\",";
  data += "\"altitude\": \"" + String(altitude) + "\",";
  data += "\"heading\": \"" + String(heading) + "\",";
  data += "\"speed\": \"" + String(speed) + "\",";
  data += "\"satellites\": \"" + String(satellites) + "\",";
  data += "\"battery\": \"-1\"";
  data += "}}";
  Serial.println(data);

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
  
  delay(1000 * 30);
}
