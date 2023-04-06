void loop() {
  server.handleClient();
  atmega.tick();
  if (Serial.available()){
    atmega.create_request(Serial.readString());
    Serial.println(atmega.send_request());
  }
}
