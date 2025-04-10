
#ifndef STASSID
#define STASSID "YOUR_SSID"
#define STAPSK "YOUR_PASSWORD"
#endif

const char* host = "splunk.domain";
const uint16_t port = 8088;

const char* deviceName = "tankmonitor1";
const char* sensorType = "tankdepth";

#define DEPTH_SENSOR A0
#define DEPTH_CALC_VAL 0.001611328
#define SPLUNK_TOKEN "Authorization: Splunk Token"
