/***************** NETWORK *****************/
#define ADRESS "esp"

#define AP_SSID "OneTwoZzz Wemos"
#define AP_PASS "12345678"

#define STA_PERIOD 5000 // >3000ms
#define MAX_NETW 4
uint8_t count_networks = 0;
String STA_SSID[MAX_NETW] = {
  "Galaxy A10180C", "OneTwoZzz", "", ""
};
String STA_PASS[MAX_NETW] = {
  "caak1842", "67812345", "", ""
};
