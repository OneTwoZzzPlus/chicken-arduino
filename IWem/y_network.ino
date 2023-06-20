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
