/**************** ADDRES ****************/
#define ADDR_INIT 0
#define ADDR_SSID 1
#define ADDR_PASS 256
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

void setup_memory() {

  EEPROM.begin(2048);

  if (EEPROM[ADDR_INIT] != INIT_BYTE) {
    Df("###MEMORY RESET###")
    EEPROM[ADDR_INIT] = INIT_BYTE;

    range(MAX_NETW) put_string(GET_ADDR_SSID(itter), STA_SSID[itter]);
    range(MAX_NETW) put_string(GET_ADDR_PASS(itter), STA_PASS[itter]);

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
}

void handleGetWifi() {
  Df("HANDLE GetWifi")
  CLEAR_JSON;
  J(F("max_count"), MAX_NETW);
  J(F("count"), count_networks);
  range(count_networks) {
    J(itter, STA_SSID[itter]);
  }
  SEND_JSON;
}

void handleSetWifi() {
  Df("HANDLE SetWifi")

  if ((!checkInt(server.arg("n"), 0, MAX_NETW))
      || server.arg("ssid") == ""
      || server.arg("pass") == "") {
    SEND_BAD_REQUEST;
    return;
  }
  
  if (server.arg("ssid").length() >= ADDR_STEP || server.arg("pass").length() >= ADDR_STEP) {
    SEND_BAD_REQUEST;
    return;
  }

  if (write_network(String(server.arg("n")).toInt(), server.arg("ssid"), server.arg("pass"))) SEND_OK;
  else SEND_BAD_REQUEST;
}

void start_AP() {
  WiFi.mode(WIFI_AP);
  //WiFi.softAPConfig(ip.main, ip.gateway, ip.subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  Df("#STARTED AP")
  df("IP: ") D(WiFi.softAPIP())
}

bool start_STA(uint8_t i) {
  WiFi.mode(WIFI_STA);
  //WiFi.config(ip.main, ip.gateway, ip.subnet, ip.dns1, ip.dns2
  WiFi.begin(STA_SSID[i], STA_PASS[i]);
  d(STA_SSID[i])
  for (uint32_t br = 0; br < STA_PERIOD; br++) {
    if (!(br % 100)) {
      d(".")
    }
    // CONNECT
    if (WiFi.status() == WL_CONNECTED) {
      Df("\n#STARTED STA")
      df("SSID: ") D(STA_SSID[i])
      df("IP: ") D(WiFi.localIP())
      return true;
    }
    delay(1);
  }
  D("")
  return false;
}

void wifi_connect() {
  Df("#START wi-fi connecting")

  Df("Starting WiFi scan");
  int scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);
  if (scanResult == 0) {
    Df("No networks found")
    start_AP();
    return;
  } else if (scanResult < 0) {
    Df("ERROR NETWORK SCAN")
    start_AP();
    return;
  } else {
    String ssid;
    int32_t rssi, channel;
    uint8_t encType;
    uint8_t* bssid;
    bool hidden;
    d(scanResult) Df(" networks found")
#ifdef DEBUG_WIFI_LIST
    for (uint8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encType, rssi, bssid, channel, hidden);
      Serial.printf(PSTR("   %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                    i,
                    channel,
                    bssid[0], bssid[1], bssid[2],
                    bssid[3], bssid[4], bssid[5],
                    rssi,
                    (encType == ENC_TYPE_NONE) ? ' ' : '*',
                    hidden ? 'H' : 'V',
                    ssid.c_str());
      delay(0);
    }
#endif
    for (uint8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encType, rssi, bssid, channel, hidden);
      for (uint8_t k = 0; k < count_networks; k++) {
        if (STA_SSID[k] == ssid) {
          if (start_STA(k)) return;
        }
      }
    }
    Df("No available networks")
    start_AP();
    return;
  }
}

void setup_network(){
  REQUEST();
  server.on("/getWifi", handleGetWifi)
  server.on("/setWifi", handleSetWifi)
  server.begin();
}
