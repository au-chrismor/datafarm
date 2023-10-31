#define HAS_ESP32

#ifdef HAS_ESP32
#include <pgmspace.h>
#endif

#define _DEBUG
#define TANK_LEVEL      36
#define TANK_ADC_VALUE  0.001611328125
const char* WIFI_SSID = "WIFI";
const char* WIFI_PASSWORD = "ShouldBeASecret";
const char* SPLUNK_HOST = "splunk";
const uint16_t SPLUNK_PORT = 8088;
const char* SPLUNK_TOKEN = "Authorization: Splunk 01234567-89ab-def0-1234-56789abcdef0";
