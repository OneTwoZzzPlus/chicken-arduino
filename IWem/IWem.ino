#include "painter.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <FastBot.h>

ESP8266WebServer server(80);

#define VERSION "0.1"
#define INIT_BYTE 'x'

#define DEBUG
#define DEBUG_WIFI_LIST
#define DEBUG_MEM_LIST

/****** TELEGRAM ******/
//This is a crutch, this function should be in this file
void event(FB_msg& msg);
void event_r(FB_msg& msg) {
  event(msg);
}
