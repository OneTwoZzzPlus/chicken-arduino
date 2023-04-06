void loop() {
  server.handleClient();
  atmega.tick();
}
