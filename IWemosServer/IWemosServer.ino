#define DEBUG_ENABLE

#define VERSION "v0.0"

const struct {
  byte RX = D2;
  byte TX = D1; 
} PINS;

const struct {
  String AP_SSID = "OneTwoZzz Wemos";
  String AP_PASS = "12345678";
  byte AP_CHANNEL = 1; // default: 1
  bool AP_HIDDEN = false;
  byte AP_MAX_CONNECTION = 4; //default:4
} connectionPref;
/****************************************/
#ifdef DEBUG_ENABLE
bool debug_state = false;
#define DEBUG_BEGIN Serial.begin(115200);delay(100);Serial.flush();Serial.println("\nDEBUG ON");
#define DEBUG(x) Serial.println(x);
#define DEBUGf(x) Serial.print(x);
#define DEBUG_ENR debug_state=
#define DEBUG_ENW if(debug_state){Serial.println("Successfully");}else{Serial.println("ERROR");}
#define DEBUG_ENWf if(debug_state){Serial.print("Successfully");}else{Serial.print("ERROR");}
#else
#define DEBUG_BEGIN
#define DEBUG(x)
#define DEBUGf(x)
#define DEBUG_ENR
#define DEBUG_ENW
#define DEBUG_ENWf
#endif
/****************************************/
#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
