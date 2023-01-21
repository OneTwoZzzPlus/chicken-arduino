void setup_serial() {
  atmega.begin(9600);
  atmega.flush();
  DEBUG("Atmega serial started")   
}

void setup_server() {
  DEBUGf("Start AP: ")
  DEBUG_ENR WiFi.softAP(connectionPref.AP_SSID, 
              connectionPref.AP_PASS, 
              connectionPref.AP_CHANNEL, 
              connectionPref.AP_HIDDEN, 
              connectionPref.AP_MAX_CONNECTION);
  DEBUG_ENW
  DEBUGf("IP: ") DEBUG(WiFi.softAPIP())

  // SERVER REQUEST HANDLE
  for (int r = 0; r < request_count; r++) {
    server.on(request_commands[r], request_functions[r]);
  }
  //server.onNotFound(handle_NotFound); 

  server.begin();
  DEBUG("Server started")     
}
