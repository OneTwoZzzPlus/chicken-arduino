int itter = 0;
//#define range(start,end,step) for(itter=start;itter<end;itter+=step)
//#define range(start,end) for(itter=start;itter<end;itter++)
#define range(end) for(itter=0;itter<end;itter++)

/******************* PIN *******************/
const struct {
  byte ARX = D2;
  byte ATX = D1;
} PIN;

/***************** TELEGRAM ****************/
#define MAX_TG 2
uint8_t count_chatId_tg = 0;
String chatId_tg[MAX_TG] = {
  "2112185652", ""
};
String chatId = "";
String token = "5942130526:AAGpj0XXj9MzCIiYlvMZvNUe_TZZdEnkbeg";
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
  "caak1842", "plz12345", "", ""
};

const struct {
  // Can edit only last byte of ip.main
  IPAddress main = IPAddress(192,168,1,17); 
  IPAddress gateway = IPAddress(192,168,1,1);
  IPAddress subnet = IPAddress(255,255,255,0);
  IPAddress dns1 = IPAddress(8, 8, 8, 8);
  IPAddress dns2 = IPAddress(8, 8, 4, 4);
} ip;
