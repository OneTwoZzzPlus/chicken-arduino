const struct {
  byte ARX = D2;
  byte ATX = D1;
} PIN;

#define AP_SSID "OneTwoZzz Wemos"
#define AP_PASS "12345678"

#define STA_PERIOD 5000
#define NETW_COUNT 4
String STA_SSID[NETW_COUNT];
String STA_PASS[NETW_COUNT];

const String memory_default[NETW_COUNT*2] = {
  "Galaxy A10180C",
  "OneTwoZzz",
  "o",
  "o",
  "caak1842",
  "plz12345",
  "o",
  "o"
};

const struct {
  // Can edit only last byte of ip.main
  IPAddress main = IPAddress(192,168,43,45); 
  IPAddress gateway = IPAddress(192,168,43,1);
  IPAddress subnet = IPAddress(255,255,255,0);
  IPAddress dns1 = IPAddress(8, 8, 8, 8);
  IPAddress dns2 = IPAddress(8, 8, 4, 4);
} ip;
