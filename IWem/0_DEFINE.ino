int itter = 0;
#define range(start,end,step) for(itter=start;itter<end;itter+=step)
#define range(start,end) for(itter=start;itter<end;itter++)
#define range(end) for(itter=0;itter<end;itter++)

/******************* PIN *******************/
const struct {
  byte ARX = D2;
  byte ATX = D1;
} PIN;

/***************** TELEGRAM ****************/
#define MAX_TG 2
String access_tg[MAX_TG] = {
  "0", ""
};

/***************** NETWORK *****************/

#define AP_SSID "OneTwoZzz Wemos"
#define AP_PASS "12345678"

#define STA_PERIOD 5000 // >3000ms
#define NETW_COUNT 4
String STA_SSID[NETW_COUNT];
String STA_PASS[NETW_COUNT];
const String default_ssid[NETW_COUNT] = {
  "Galaxy A10180C", "OneTwoZzz", "o", "o"
};
const String default_pass[NETW_COUNT] = {
  "caak1842", "plz12345", "o", "o"
};

const struct {
  // Can edit only last byte of ip.main
  IPAddress main = IPAddress(192,168,43,45); 
  IPAddress gateway = IPAddress(192,168,43,1);
  IPAddress subnet = IPAddress(255,255,255,0);
  IPAddress dns1 = IPAddress(8, 8, 8, 8);
  IPAddress dns2 = IPAddress(8, 8, 4, 4);
} ip;
