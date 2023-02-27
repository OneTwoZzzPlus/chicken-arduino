void loop() {
  server.handleClient();
  atmega.tick();
  if (Serial.available()){
    Serial.println(atmega.request(Serial.readStringUntil('\\')));
  }
}
