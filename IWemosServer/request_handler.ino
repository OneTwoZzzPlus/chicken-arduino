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
  String s = atmega.request("ci");
  server.send(200, "text/plain", s);
  DEBUG(s)
}

void handleResetMemory() {
  DEBUGf(F("RESET MEMORY: "))
  String s = atmega.request("cr");
  server.send(200, "text/plain", s);
  DEBUG(s)
}

void handleModuleList() {
  DEBUGf(F("List modules: "))
  String s = atmega.request("cl");
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
      String s = atmega.request("cm"+ns);
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
    String req = "ce";
    req += server.arg("n");
    req += F("=");
    req += server.arg("mode");
    if (server.arg("n") == "1" || server.arg("n") == "2" || server.arg("n") == "3" || server.arg("n") == "4") {
      if (server.arg("pos")== "" || server.arg("val0")== "" || server.arg("val1")== "") {
        // no arg
        server.send(200, "text/plain", F("No args! Must be 'pos', 'val0', 'val1'"));
        DEBUG(F("No args! Must be 'pos', 'val0', 'val1'"))
        return;
      }
      req += F("=");
      req += server.arg("pos");
      req += F("=");
      req += server.arg("val0");
      req += F("=");
      req += server.arg("val1");
    }
    DEBUGf("SEND: ") 
    DEBUG(req)
    String s = atmega.request(req);
    server.send(200, "text/plain", s);
    DEBUG(s)
  }
}

/*void handleAddTimer() {
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
}*/

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
