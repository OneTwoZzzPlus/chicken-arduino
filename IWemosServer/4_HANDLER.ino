void handleEmpty() {
  DEBUG(F("HANDLE Empty"))
  server.send(200, "text/plain", F("It's API request in develop"));
}

void handleVersion() {
  DEBUG(F("HANDLE V"))
  server.send(200, "text/plain", VERSION);
}

void handleLed() {
  DEBUG(F("HANDLE ModuleLed"))
  atmega.new_request("c0");
  atmega.NArequest();
  server.send(200, "text/plain", "c0");
}

void handleInfo() {
  DEBUG(F("HANDLE Info"))
  atmega.new_request("ci");
  String s = atmega.request();
  server.send(200, "text/plain", s);
}

void handleResetMemory() {
  DEBUG(F("HANDLE ResetMemory"))
  atmega.new_request("cr");
  String s = atmega.request();
  server.send(200, "text/plain", s);
}

void handleModuleList() {
  DEBUG(F("HANDLE ModuleList"))
  atmega.new_request("cl");
  String s = atmega.request();
  server.send(200, "text/plain", s);
}

bool checkInt(String s, int down, int up) {
  int n = 0;
  for (int i = 0; i < s.length(); i++) {
    if ('0' <= s[i] && s[i] <= '9') n = (10 * n) + (s[i] - '0');
    else {
      return false;
    }
  }
  return (down <= n && n <= up);
}

void handleModuleInfo() {
  DEBUG(F("HANDLE ModuleInfo"))
  if (server.arg("n") == "") {
    server.send(200, "text/plain", F("Missing 'n' arg"));
    DEBUG(F("Missing 'n' arg"))
    return;
  }
  String n = server.arg("n");
  if (!checkInt(n, 0, 255)) {
    server.send(200, "text/plain", F("Invalide 'n' arg: ") + n);
    DEBUG(F("Invalide 'n' arg: ") + n)
    return;
  }
  atmega.new_request("cm");
  atmega.arg_request(n);
  String s = atmega.request();
  server.send(200, "text/plain", s);
}

void handleModuleMode() {
  DEBUG(F("HANDLE ModuleMode"))
  if (server.arg("n") == "") {
    server.send(200, "text/plain", F("Missing 'n' arg"));
    DEBUG(F("Missing 'n' arg"))
    return;
  }
  String n = server.arg("n");
  if (!checkInt(n, 0, 255)) {
    server.send(200, "text/plain", F("Invalide 'n' arg: ") + n);
    DEBUG(F("Invalide 'n' arg: ") + n)
    return;
  }
  if (server.arg("mode") == "") {
    server.send(200, "text/plain", F("Missing 'mode' arg"));
    DEBUG(F("Missing 'mode' arg"))
    return;
  }
  String mode = server.arg("mode");
  if (!checkInt(mode, 0, 255)) {
    server.send(200, "text/plain", F("Invalide 'n' arg: ") + mode);
    DEBUG(F("Invalide 'mode' arg: ") + mode)
    return;
  }
  atmega.new_request("mm");
  atmega.arg_request(n);
  atmega.arg_request(mode);
  String s = atmega.request();
  server.send(200, "text/plain", s);
}

void handleModuleEdit() {
  DEBUG(F("HANDLE ModuleEdit"))
  // n
  if (server.arg("n") == "") {
    server.send(200, "text/plain", F("Missing 'n' arg"));
    DEBUG(F("Missing 'n' arg"))
    return;
  }
  String n = server.arg("n");
  if (!checkInt(n, 0, 255)) {
    server.send(200, "text/plain", F("Invalide 'n' arg: ") + n);
    DEBUG(F("Invalide 'n' arg: ") + n)
    return;
  }
  // mode
  if (server.arg("mode") == "") {
    server.send(200, "text/plain", F("Missing 'mode' arg"));
    DEBUG(F("Missing 'mode' arg"))
    return;
  }
  String mode = server.arg("n");
  if (!checkInt(mode, 0, 255)) {
    server.send(200, "text/plain", F("Invalide 'mode' arg: ") + mode);
    DEBUG(F("Invalide 'mode' arg: ") + mode)
    return;
  }
  atmega.new_request("ce");
  atmega.arg_request(server.arg("n"));
  atmega.arg_request(server.arg("mode"));

  if (server.arg("pos") != "") atmega.arg_request(server.arg("pos"));
  
  if (server.arg("timeS") != "" && server.arg("timeE") != "") {
    atmega.arg_request(server.arg("timeS"));
    atmega.arg_request(server.arg("timeE"));
  } 
  else if (server.arg("temp") != "") {
    atmega.arg_request(server.arg("temp"));
    atmega.arg_request("0");
  }
  else if (server.arg("humi") != "") {
    atmega.arg_request(server.arg("humi"));
    atmega.arg_request("0");
  } else {
    atmega.arg_request("0");
    atmega.arg_request("0");
  }
  
  String s = atmega.request();
  server.send(200, "text/plain", s);

}
