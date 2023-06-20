void setup() {
  uint64_t setup_timer = millis();
  DEBUG_BEGIN
  Df("########START SETUP########")
  atmega.begin(9600);
  Df("#STARTED atmega")
  setup_memory();
  wifi_connect();
  REQUEST();
  server.begin();
  Df("#STARTED server")
  setup_tg();
  Df("#STARTED tg")
  delay(100);
  df("#Setup end: ") d(millis()-setup_timer) D("ms")
  Df("\n########START LOOP########")
}

void loop() {
  server.handleClient();
  bot.tick();
  atmega.tick();
}
