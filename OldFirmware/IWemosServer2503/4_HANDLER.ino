void handleGetVersion(){ server.send(200, "text/plain", VERSION); }

void handleGetMessage() {
  if (atmega.messageIsEmpty()) server.send(200, "text/plain", F("No messages!"));
  else server.send(200, "text/plain", atmega.putMessage());
  DEBUGf(F("MESSAGE request: "));
  DEBUG(atmega.putMessage());
}

void handleDeleteMessage () {
  atmega.delMessage();
  server.send(200, "text/plain", F("No messages!"));
  DEBUGf(F("MESSAGE deleted "));
  DEBUG(atmega.putMessage());
}

void handleLed() {
  atmega.send_command("c0");
  server.send(200, "text/plain", "c0");
  DEBUG(F("Send command c0 to atmega"))
}

void handleInfo() {
  DEBUGf(F("Send command i0 to atmega with return: "))
  atmega.create_request("ci");
  String s = atmega.send_request();
  server.send(200, "text/plain", s);
  DEBUG(s)
}

void handleResetMemory() {
  DEBUGf(F("RESET MEMORY: "))
  atmega.create_request("cr");
  String s = atmega.send_request();
  server.send(200, "text/plain", s);
  DEBUG(s)
}

void handleModuleList() {
  DEBUGf(F("List modules: "))
  atmega.create_request("cl");
  String s = atmega.send_request();
  server.send(200, "text/plain", s);
  DEBUG(s)
}

bool checkInt(String s, int down, int up) {
    int n = 0;
    for (int i = 0; i < s.length(); i++) {
      if ('0' <= s[i] && s[i] <= '9') n = (10*n)+(s[i]-'0');
      else {
        return false;
      }
    }
    return (down<=n&&n<=up);
}

void handleModuleInfo() {
  DEBUGf(F("Info timers: "))
  if (server.arg("n")== "") {
    // no "n" arg
    server.send(200, "text/plain", F("Missing 'n' arg"));
    DEBUG(F("Missing 'n' arg"))
  } else {
    String ns = server.arg("n");
    if (checkInt(ns, 0, 255)) {
      atmega.create_request("cm");
      atmega.arg_request(ns);
      String s = atmega.send_request();
      server.send(200, "text/plain", s);
      DEBUG(s)
    } else {
      server.send(200, "text/plain", F("Invalide 'n' arg")+ns); 
      DEBUG(F("Invalide 'n' arg")+ns) 
      return;
    }
  }
}

void handleModuleEdit() {
  DEBUGf(F("Edit timer: "))
  if (server.arg("n")== "" || server.arg("mode")== "") {
    // no arg
    server.send(200, "text/plain", F("No args! Must be 'n', 'mode'"));
    DEBUG(F("No args! Must be 'n', 'mode'"))
  } else {
    atmega.create_request("ce");
    atmega.arg_request(server.arg("n"));
    atmega.arg_request(server.arg("mode"));
    if (server.arg("n") == "1" || server.arg("n") == "2" || server.arg("n") == "3" || server.arg("n") == "4") {
      if (server.arg("pos")== "" || server.arg("val0")== "" || server.arg("val1")== "") {
        // no arg
        server.send(200, "text/plain", F("No args! Must be 'pos', 'val0', 'val1'"));
        DEBUG(F("No args! Must be 'pos', 'val0', 'val1'"))
        return;
      }
      atmega.arg_request(server.arg("pos"));
      atmega.arg_request(server.arg("val0"));
      atmega.arg_request(server.arg("val1"));
    }
    DEBUGf("SEND: ") 
    DEBUG(atmega.request_string)
    String s = atmega.send_request();
    server.send(200, "text/plain", s);
  }
}
