#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

ESP8266WebServer server(80);

#define VERSION "0.1"
#define INIT_BYTE 'x'

#define DEBUG
#define DEBUG_WIFI_LIST
