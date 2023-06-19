void setup() {
  DEBUG_BEGIN
  Df("########START SETUP########")
  atmega.begin(9600);
  Df("#STARTED atmega")
  setup_memory();
  wifi_connect();
  REQUEST();
  server.begin();
  Df("#STARTED server")
  delay(100);
  Df("\n########START LOOP########")
}

void loop() {
  server.handleClient();
  atmega.tick();
}
