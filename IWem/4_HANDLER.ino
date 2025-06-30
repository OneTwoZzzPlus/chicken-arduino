void handleEmpty() {
  Df("HANDLE Empty")
  SEND_NOT_IMPLEMENTED;
}

void handleVersion() {
  Df("HANDLE V")
  ANSWER(VERSION);
}

void handleRequest() {
  Df("HANDLE Request")
  String c = server.arg("c"), arg = server.arg("arg");
  if (c == "") {
    SEND_BAD_REQUEST;
    return;
  }
  atmega.send(c);
  if (arg != "") {
    atmega.send(arg);
  }
  ANSWER(atmega.wait());
}



void handleGetAccessTg() {
  Df("HANDLE GetAccessTg")
  CLEAR_JSON;
  J(F("max_count"), MAX_TG);
  J(F("count"), count_chatId_tg);
  range(count_chatId_tg) {
    J(itter, chatId_tg[itter]);
  }
  SEND_JSON;
}

void handleSetAccessTg() {
  Df("HANDLE SetAccessTg")

  if ((!checkInt(server.arg("n"), 0, MAX_TG))
      || server.arg("s") == "") {
    SEND_BAD_REQUEST;
    return;
  }

  if (server.arg("s").length() >= ADDR_TG_STEP) {
    SEND_BAD_REQUEST;
    return;
  }

  if (write_chatId_tg(String(server.arg("n")).toInt(), server.arg("s"))) SEND_OK;
  else SEND_BAD_REQUEST;
}

void handleGetToken() {
  Df("HANDLE GetToken")
  String ans = token.substring(0, 5);
  ans += "*******";
  ans += token.substring(token.length() - 5);
  ans += " refer to the link https://t.me/BotFather";
  ANSWER(ans);
}

void handleSetToken() {
  Df("HANDLE SetToken")

  uint8_t len = server.arg("s").length();
  if (len > 50 || len < 40) { //[44..46]
    SEND_BAD_REQUEST;
    return;
  }

  if (write_token_tg(server.arg("s"))) SEND_OK;
  else SEND_BAD_REQUEST;
}

void handleHello() {
  Df("HANDLE Hello")
  server.send(200, R"(text\html)",
              F(R"LOLOLOLO(
 <html>
 <head>
 <meta http-equiv='refresh' content='5'/>
 <title>Controller</title>
 <style>
 </style>
 </head>
 <body>
 <h1>Hello! Welcome to controller!</h1>
 <h2>Available page:</h2>
 <p>None</p>
 <h2>Available API:</h2>
 <ul>
 <li><a href="http://192.168.4.1/version">version</a></li>
 <li><a href="http://192.168.4.1/request?c=i">request?c&arg</a></li>
 <li><a href="http://192.168.4.1/getWifi">getWifi</a></li>
 <li><a href="http://192.168.4.1/setWifi">/setWifi?n&ssid&pass</a></li>
 <li><a href="http://192.168.4.1/getAccessTg">getAccessTg</a></li>
 <li><a href="http://192.168.4.1/setAccessTg?c=i">/setAccessTg?n&s</a></li>
 <li><a href="http://192.168.4.1/getToken">getToken</a></li>
 <li><a href="http://192.168.4.1/setToken">/setToken?s</a></li>
 </ul>
 </body>
 </html>
 )LOLOLOLO" ) );
}

/**************************************************/
/*void handleLed() {
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

  }*/
