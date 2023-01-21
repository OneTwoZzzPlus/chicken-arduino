void handleGetVersion(){ server.send(200, "text/plain", VERSION); }

void handleGetMessage() {
  if (atmega.messageIsEmpty()) server.send(200, "text/plain", "No messages!");
  else server.send(200, "text/plain", atmega.putMessage());
  DEBUGf("MESSAGE request: ");
  DEBUG(atmega.putMessage());
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
  DEBUG("Send settings " + message + " to atmega")
}

void handleLed() {
  atmega.send_command("c0");
  server.send(200, "text/plain", "c0");
  DEBUG("Send command c0 to atmega")
}

void handleInfo() {
  DEBUGf("Send command i0 to atmega with return: ")
  String s = atmega.request("i0");
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
}*/
