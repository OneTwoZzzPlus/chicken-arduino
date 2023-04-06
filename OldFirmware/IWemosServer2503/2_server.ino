void setup_server() {
  DEBUGf("Start AP: ")
  DEBUG_ENR WiFi.softAP(connectionPref.AP_SSID,
                        connectionPref.AP_PASS,
                        connectionPref.AP_CHANNEL,
                        connectionPref.AP_HIDDEN,
                        connectionPref.AP_MAX_CONNECTION);
  DEBUG_ENW
  DEBUGf("IP: ") DEBUG(WiFi.softAPIP())

  REQUEST();

  server.begin();
  DEBUG("Server started")
}

#define R(x, y) server.on(F(x), y);
