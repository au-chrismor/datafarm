#define HAS_ESP32

#ifdef HAS_ESP32
#include <pgmspace.h>
#endif

#define _DEBUG
#define BATTERY_VOLTS   36
#define BATTERY_ADC_VALUE  0.001611328125  // 2 * Vmax / ADC_Resolution)
#define DALLAS_PIN      4
#define BME_ADDRESS     0x76
const char* WIFI_SSID = "WIFI";
const char* WIFI_PASSWORD = "ShouldBeASecret";
const char* SPLUNK_HOST = "splunk";
const uint16_t SPLUNK_PORT = 8088;
const char* INDEX_NAME = "datafarm";
const char* HOST_NAME = "environment";
const char* SENSOR_TYPE = "environment";
const char* SOURCE_TYPE = "datafarm";
const char* SPLUNK_TOKEN = "Authorization: Splunk 01234567-89ab-def0-1234-56789abcdef0";
