
#ifndef STASSID
#define STASSID "SSID"
#define STAPSK "Password"
#endif

const char* deviceName = "vehicle1";
const char* sensorType = "vehicle";

const char* host = "splunk";
const uint16_t port = 8088;

#define SPLUNK_TOKEN "Authorization: Splunk"
#define GPS_BAUD 9600
#define RXD2 17
#define TXD2 16

// Thermistor definitions
#define NTC_PIN   34
#define NTC_RES   10000
#define NTC_BETA   3950
