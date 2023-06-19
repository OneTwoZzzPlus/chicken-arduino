#include "painter.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

#define VERSION "0.1"
#define INIT_BYTE 'i'

#define DEBUG
#define DEBUG_WIFI_LIST
#define DEBUG_NETW_LIST
