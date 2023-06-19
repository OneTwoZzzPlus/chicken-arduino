/**************** ADDRES ****************/
#define ADDR_INIT 0
#define ADDR_SSID 1
#define ADDR_PASS 256
#define ADDR_STEP 32
#define ADDR_TG 512
#define ADDR_TG_STEP 32

#define GET_ADDR_SSID(x) ADDR_STEP*x+ADDR_SSID
#define GET_ADDR_PASS(x) ADDR_STEP*x+ADDR_PASS
#define GET_ADDR_TG(x) ADDR_TG_STEP*x+ADDR_TG
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

    range(MAX_TG) put_string(GET_ADDR_TG(itter), access_tg[itter]);
    range(NETW_COUNT) put_string(GET_ADDR_SSID(itter), default_ssid[itter]);
    range(NETW_COUNT) put_string(GET_ADDR_PASS(itter), default_pass[itter]);

    EEPROM.commit();
  }

  Df("#Memory setup")

  d(NETW_COUNT) Df(" networks read")
  range(NETW_COUNT) {
    STA_SSID[itter] = get_string(GET_ADDR_SSID(itter));
#ifdef DEBUG_NETW_LIST
    Serial.printf(PSTR("   %d SSID = %s \n"),
                  itter, STA_SSID[itter].c_str());
#endif
  }
  range(NETW_COUNT) {
    STA_PASS[itter] = get_string(GET_ADDR_PASS(itter));
#ifdef DEBUG_NETW_LIST
    Serial.printf(PSTR("   %d PASS = %s \n"),
                  itter, STA_PASS[itter].c_str());
#endif
  }

  uint16_t countr = 0;
  range(MAX_TG) {
    if (EEPROM[GET_ADDR_TG(itter)]) {
      access_tg[itter] = get_string(GET_ADDR_TG(itter));
      countr++;
    }
  }
  d(countr) Df(" tg access")
#ifdef DEBUG_NETW_LIST
  range(countr) {
    Serial.printf(PSTR("   %d key = %s \n"),
                  itter, access_tg[itter].c_str());
  }
#endif
}
