/*for (int r = 0; r < request_count; r++) {
    server.on(request_commands[r], request_functions[r]);
  }
  //server.onNotFound(handleNotFound); */
/*void handleNotFound() { server.send(200, "text/plain", F("\
  Command not found!  \n\
  Available commands: \n\
  '/version'        \n\
  '/message'        \n\
  '/messageDelete'  \n\
  '/led'            \n\
  '/resetMemory'    \n\
  '/info'           \n\
  '/moduleList'     \n\
  '/moduleInfo?n='  \n\
  '/moduleEdit?n=&mode='  \n\
  '/moduleEdit?n=&mode=&pos=&val0=&val1='  \n\
  ")); }*/

/*// FUNCTIONS
  void (*request_functions[])() = {
  handleGetVersion,
  handleGetMessage,
  handleDeleteMessage,
  handleLed,
  handleResetMemory,
  handleInfo,
  handleModuleList,
  handleModuleInfo,
  handleModuleEdit
  };

  // REQUEST COUNT
  const int request_count = 11;

  // COMMANDS
  const String request_commands[] = {
  "/version",
  "/message",
  "/messageDelete",
  "/led",
  "/resetMemory",
  "/info",
  "/moduleList",
  "/moduleInfo",
  "/moduleEdit"
  };*/

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

  if (server.arg("n") == "1" || server.arg("n") == "2" || server.arg("n") == "3" || server.arg("n") == "4") {
    if (server.arg("pos") == "" || server.arg("val0") == "" || server.arg("val1") == "") {
      // no arg
      server.send(200, "text/plain", F("No args! Must be 'pos', 'val0', 'val1'"));
      DEBUG(F("No args! Must be 'pos', 'val0', 'val1'"))
      return;
    }
     
    atmega.arg_request(server.arg("val0"));
    atmega.arg_request(server.arg("val1"));
  }
*/
//// MODE 2d-array: 1-TYPE 2-MODE
//String ModuleMode[2][5] = {
//  { // MAIN
//    /*0*/{"{}"},
//    /*0*/{"{}"},
//    /*0*/{"{}"},
//    /*0*/{"{}"},
//    /*0*/{"{}"}
//  },
//  { // RELAY
//    /*0*/{"{}"},
//    /*1*/{"{\"pos\":\"\",\"time0\":\"\",\"time1\":\"\"}"},
//    /*2*/{"{\"time0\":\"\",\"time1\":\"\"}"},
//    /*3*/{"{\"pos\":\"\",\"temp\":\"\"}"},
//    /*4*/{"{\"pos\":\"\",\"humi\":\"\"}"}
//  }
//};
