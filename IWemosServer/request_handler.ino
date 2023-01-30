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
  String s = atmega.request("i0");
  server.send(200, "text/plain", s);
  DEBUG(s)
}

void handleResetMemory() {
  DEBUGf(F("RESET MEMORY: "))
  String s = atmega.request("cR");
  server.send(200, "text/plain", s);
  DEBUG(s)
}

void handleInfoModules() {
  DEBUGf(F("Info modules: "))
  String s = atmega.request("iM");
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

void handleInfoTimer() {
  DEBUGf(F("Info timers: "))
  if (server.arg("n")== "") {
    // no "n" arg
    server.send(200, "text/plain", F("Missing 'n' arg"));
    DEBUG(F("Missing 'n' arg"))
  } else {
    String ns = server.arg("n");
    if (checkInt(ns, 0, 255)) {
      String s = atmega.request("it"+ns);
      server.send(200, "text/plain", s);
      DEBUG(s)
    } else {
      server.send(200, "text/plain", F("Invalide 'n' arg")+ns); 
      DEBUG(F("Invalide 'n' arg")+ns) 
      return;
    }
  }
}

void handleEditTimer() {
  DEBUGf(F("Edit timer: "))
  if (server.arg("n")== "" || server.arg("channel")== "" || server.arg("pos")== "" || server.arg("val")== "") {
    // no arg
    server.send(200, "text/plain", F("No args! Must be 'n', 'channel', 'pos', 'val'"));
    DEBUG(F("No args! Must be 'n', 'channel', 'pos', 'val'"))
  } else {
    String req = "ste";
    req += server.arg("n");
    req += F("=");
    req += server.arg("channel");
    req += F("=");
    req += server.arg("pos");
    req += F("=");
    req += server.arg("val");
    
    String s = atmega.request(req);
    server.send(200, "text/plain", s);
    DEBUG(s)
  }
}

void handleAddTimer() {
  DEBUGf(F("Add timer: "))
  if (server.arg("channel")== "" || server.arg("pos")== "" || server.arg("val")== "") {
    // no arg
    server.send(200, "text/plain", F("No args! Must be 'channel', 'pos', 'val'"));
    DEBUG(F("No args! Must be 'channel', 'pos', 'val'"))
  } else {
    String req = "sta";
    req += server.arg("channel");
    req += F("=");
    req += server.arg("pos");
    req += F("=");
    req += server.arg("val");
    
    String s = atmega.request(req);
    server.send(200, "text/plain", s);
    DEBUG(s)
  }
}
void handleDeleteAllTimers() {
  DEBUGf(F("Delete ALL timers: "))
  String s = atmega.request("stD");
  server.send(200, "text/plain", s);
  DEBUG(s)  
}

/*void handleGenericArgs(){
  String message = "Number of args received:";
  message += server.args();      // получить количество параметров
  message += "\n";               // переход на новую строку

  for (int i = 0; i < server.args(); i++) 
  {
    message += "Arg nº" + (String)i + " –> "; // добавить текущее значение счетчика
    message += server.argName(i) + ": ";      // получить имя параметра
    message += server.arg(i) + "\n";          // получить значение параметра
  } 

  server.send(200, "text/plain", message);    // ответить на HTTP запрос
}

void handleSpecificArg(){ 
  String message = "";

  if (server.arg("Temperature")== "") 
  { // параметр не найден
    message = "Temperature Argument not found";
  }
  else
  { // параметр найден
    message = "Temperature Argument = ";
    message += server.arg("Temperature");     // получить значение параметра запроса
  }

  server.send(200, "text/plain", message);    // возвращаем HTTP-ответ
}

void handleSetSettings(){
  int countArgs = server.args();
  if (countArgs == 0) {
    server.send(200, "text/plain", ERRORS.ERROR_FEW_ARGUMENTS);
    return;
  }
  String message = "s";
  for (int i = 0; i < countArgs; i++) 
  {
    message += server.argName(i) + ":";
    message += server.arg(i) + "?";
  }
  atmega.send_command(message);
  server.send(200, "text/plain", message);
  DEBUG(F("Send settings ") + message + F(" to atmega"))
}
*/
