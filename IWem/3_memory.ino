/**************** ADDRES ****************/
#define ADDR_INIT 0
#define ADDR_SSID 1
#define ADDR_PASS 256
#define ADDR_STEP 32
#define ADDR_TG 512
#define ADDR_TG_STEP 32
#define ADDR_TG_TOKEN 1024

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

bool write_network(int n, String ssid, String pass) {
  if (n < 0 || n >= MAX_NETW) return false;
  else if (n < count_networks) {
    STA_SSID[n] = ssid;
    STA_PASS[n] = pass;
  } else {
    STA_SSID[count_networks] = ssid;
    STA_PASS[count_networks] = pass;
    count_networks++;
  }
  range(MAX_NETW) put_string(GET_ADDR_SSID(itter), STA_SSID[itter]);
  range(MAX_NETW) put_string(GET_ADDR_PASS(itter), STA_PASS[itter]);
  EEPROM.commit();
  return true;
}

bool write_chatId_tg(int n, String s) {
  if (n < 0 || n >= MAX_TG) return false;
  else if (n < count_chatId_tg) {
    chatId_tg[n] = s;
  } else {
    chatId_tg[count_chatId_tg] = s;
    count_chatId_tg++;
  }
  range(count_chatId_tg) put_string(GET_ADDR_TG(itter), chatId_tg[itter]);
  EEPROM.commit();
  return true;
}

bool write_token_tg(String s) {
  token = s;
  put_string(ADDR_TG_TOKEN, token);
  EEPROM.commit();
  return true;
}

void setup_memory() {

  EEPROM.begin(2048);

  if (EEPROM[ADDR_INIT] != INIT_BYTE) {
    Df("###MEMORY RESET###")
    EEPROM[ADDR_INIT] = INIT_BYTE;

    range(MAX_NETW) put_string(GET_ADDR_SSID(itter), STA_SSID[itter]);
    range(MAX_NETW) put_string(GET_ADDR_PASS(itter), STA_PASS[itter]);
    range(MAX_TG) put_string(GET_ADDR_TG(itter), chatId_tg[itter]);
    put_string(ADDR_TG_TOKEN, token);

    EEPROM.commit();
  }

  Df("#Memory setup")

  range(MAX_NETW) {
    if (EEPROM[GET_ADDR_SSID(itter)]) {
      STA_SSID[count_networks] = get_string(GET_ADDR_SSID(itter));
      STA_PASS[count_networks] = get_string(GET_ADDR_PASS(itter));
      count_networks++;
    }
  }

  range(MAX_TG) {
    if (EEPROM[GET_ADDR_TG(itter)]) {
      chatId_tg[count_chatId_tg] = get_string(GET_ADDR_TG(itter));
      chatId+=chatId_tg[count_chatId_tg];
      chatId+=",";
      count_chatId_tg++;
    }
  }
  chatId.remove(chatId.length()-1);
  token = get_string(ADDR_TG_TOKEN);

  /****** DEBUG ******/
  d(count_networks) Df(" networks readed")
#ifdef DEBUG_MEM_LIST
  range(count_networks) {
    Serial.printf(PSTR("   %d SSID = %s \n"),
                  itter, STA_SSID[itter].c_str());
    Serial.printf(PSTR("   %d PASS = %s \n"),
                  itter, STA_PASS[itter].c_str());
  }
#endif
  d(count_chatId_tg) Df(" tg access")
#ifdef DEBUG_MEM_LIST
  range(count_chatId_tg) {
    Serial.printf(PSTR("   %d key = %s \n"),
                  itter, chatId_tg[itter].c_str());
  }
  Serial.println(chatId);
#endif
  df("Token: ") D(token);
}
