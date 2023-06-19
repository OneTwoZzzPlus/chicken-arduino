/**************** ADDRES ****************/
#define ADDR_INIT 0
#define ADDR_SSID 32
#define ADDR_PASS 200
#define ADDR_STEP 32

#define GET_ADDR_SSID(x) ADDR_STEP*x+ADDR_SSID
#define GET_ADDR_PASS(x) ADDR_STEP*x+ADDR_PASS
/**************** LOAD ****************/

String get_string(uint16_t addr) {
  String s = "";
  uint16_t len = EEPROM[addr];
  for (uint16_t i = 0; i < len; i++) {
    s += char(EEPROM[addr + i + 1]);
  }
  return s;
}
void put_string(uint16_t addr, String s) {
  EEPROM[addr] = s.length();
  for (uint8_t i = 0; i < s.length(); i++) {
    EEPROM[addr + i + 1] = s[i];
  }
}

void write_network(int n, String ssid, String pass) {
  STA_SSID[n] = ssid;
  STA_PASS[n] = pass;
  put_string(GET_ADDR_SSID(n), ssid);
  put_string(GET_ADDR_PASS(n), pass);
  EEPROM.commit();
}

void setup_memory() {

  EEPROM.begin(2048);

  if (EEPROM[ADDR_INIT] != INIT_BYTE) {
    Df("###MEMORY RESET###")
    EEPROM[ADDR_INIT] = INIT_BYTE;
    
    for (int i = 0; i < NETW_COUNT; i++) {
      put_string(GET_ADDR_SSID(i), memory_default[i]);
    }
    for (int i = 0; i < NETW_COUNT; i++) {
      put_string(GET_ADDR_PASS(i), memory_default[i+NETW_COUNT]);
    }

    EEPROM.commit();
  }

  Df("#Memory setup")
  
  for (uint8_t i = 0; i < NETW_COUNT; i++) {
    STA_SSID[i] = get_string(GET_ADDR_SSID(i));
#ifdef DEBUG_NETW_LIST
    Serial.printf(PSTR("   %d SSID = %s \n"),
                  i, STA_SSID[i].c_str());
#endif
  }
  for (uint8_t i = 0; i < NETW_COUNT; i++) {
    STA_PASS[i] = get_string(GET_ADDR_PASS(i));
#ifdef DEBUG_NETW_LIST
    Serial.printf(PSTR("   %d PASS = %s \n"),
                  i, STA_PASS[i].c_str());
#endif
  }
  d(NETW_COUNT) Df(" networks readed")
}
