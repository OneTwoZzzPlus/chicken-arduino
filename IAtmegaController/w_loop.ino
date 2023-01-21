void loop() {
  if (Serial.available()) {
    String s = Serial.readStringUntil('\\');
    if (s == "c0") {
      digitalWrite(3, !digitalRead(3));
      send("Led set to" + digitalRead(3));
    } else if (s == "i0"){
      digitalWrite(3, !digitalRead(3));
      json.clear();
      json.put("Temperature", String(bme.readTemperature()));
      json.put("Humidity", String(bme.readHumidity()));
      json.put("Pressure", String(bme.readPressure()));
      json.put("Time", String(rtc.getTimeString()));
      json.put("Data", String(rtc.getDateString()));
      json.put("TempDS", String(rtc.getTemperatureFloat()));
      send(json.get());
    }
  }
}
