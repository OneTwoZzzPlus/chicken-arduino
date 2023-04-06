void serial_tick() {
  if (!Serial.available()) return;
  String s = Serial.readStringUntil('\\');
  json.clear();
  long i = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
  digitalWrite(3, !digitalRead(3));

  if (s == "c0") { //c0 - null command
    send(String(digitalRead(3)));
  } else if (s == "cr") { //cr - reset
    memory_reset();
    send(F("Reset!"));
  } else if (s == "ci") { //ci - BME+RTC information
    if (isbme) {
      json.put("Temperature", bme.readTemperature());
      json.put("Humidity", bme.readHumidity());
      json.put("Pressure", bme.readPressure());
    }
    if (isrtc) {
      json.put("Time", rtc.getTimeString());
      json.put("Data", rtc.getDateString());
      json.put("TempDS", rtc.getTemperatureFloat());
    }
    send(json.get());
  } else if (s == "cl") { //cl - modules list
    json.put("COUNT_MODULE", COUNT_MODULE);
    json.put("0", MODULE_MAIN);
    json.put("1", MODULE_RELE);
    json.put("2", MODULE_RELE);
    json.put("3", MODULE_RELE);
    json.put("4", MODULE_RELE);
    send(json.get());
  } else if (s == "cm") { //cm - module info
    // read index
    a = Serial.parseInt();
    // valid index
    if (a < 0 || a >= COUNT_MODULE) {
      send("No module index " + String(a));
      return;
    }
    // change module type
    if (a == 0) { //main
      json.put("type", MODULE_MAIN);
      json.put("mode", vmain.mode);
    } else if (a > 0 && a < COUNT_MODULE) {
      a--; //rele
      json.put("type", MODULE_RELE);
      json.put("mode", vrele[a].mode);
      switch (vrele[a].mode) {
        case 0: break;
        case 1:
          json.put("pos", String(vrele[a].pos));
          json.put("timeS", String(vrele[a].val0));
          json.put("timeE", String(vrele[a].val1));
          break;
        case 2:
          json.put("pos", String(vrele[a].pos));
          json.put("temp", String(vrele[a].val0));
          break;
        case 3:
          json.put("pos", String(vrele[a].pos));
          json.put("humi", String(vrele[a].val0));
          break;
      }

    }
    send(json.get());
  } else if (s == "mm") { //mm - module mode
    // read index
    a = Serial.parseInt();
    b = Serial.parseInt();
    // valid index
    if (a < 0 || a >= COUNT_MODULE) {
      send("No module index " + String(a));
      return;
    }
    // change module type
    if (a > 0 && a < COUNT_MODULE) {
      a--; //rele
      switch (b) {
        case 0: break;
        case 1:
          json.put("pos", String(vrele[a].pos));
          json.put("timeS", String(vrele[a].val0));
          json.put("timeE", String(vrele[a].val1));
          break;
        case 2:
          json.put("pos", String(vrele[a].pos));
          json.put("temp", String(vrele[a].val0));
          break;
        case 3:
          json.put("pos", String(vrele[a].pos));
          json.put("humi", String(vrele[a].val0));
          break;
      }

    }
    send(json.get());
  } else if (s == "ce") { //ce[index]=[mode] - module edit
    D("EDIT")
    // read index
    a = Serial.parseInt();
    if (a < 0 || a >= COUNT_MODULE) {
      send("No module index " + String(a));
      return;
    }
    // change module type
    if (a == 0) { //main
      // mode
      b = Serial.parseInt();
      if (b < 0 || b >= 1) {
        send("No mode " + String(b));
        return;
      }
      vmain.mode = b;
      json.put("type", MODULE_MAIN);
      json.put("mode", vmain.mode);
    } else if (a > 0 && a < COUNT_MODULE) {
      a--; //rele +=[pos]=[val0]=[val1]
      // mode
      b = Serial.parseInt();
      if (b < 0 || b >= 3) {
        send("No mode " + String(b));
        return;
      }
      if (b == vrele[a].mode) {
        // pos
        c = Serial.parseInt();
        if (c < 0 || c >= 2) {
          send("Pos can be 0/1, not " + String(c));
          return;
        }
        // val0
        d = Serial.parseInt();
        if (d < 0 || d >= 1440) {
          send("Invalide time " + String(d));
          return;
        }
        // val1
        e = Serial.parseInt();
        if (e < 0 || e >= 1440) {
          send("Invalide time " + String(e));
          return;
        }
        vrele[a].mode = b;
        vrele[a].pos = c;
        vrele[a].val0 = d;
        vrele[a].val1 = e;
        rele_set(a);
        json.put("type", MODULE_RELE);
        json.put("mode", vrele[a].mode);
        switch (vrele[a].mode) {
          case 0: break;
          case 1:
            json.put("pos", String(vrele[a].pos));
            json.put("timeS", String(vrele[a].val0));
            json.put("timeE", String(vrele[a].val1));
            break;
          case 2:
            json.put("pos", String(vrele[a].pos));
            json.put("temp", String(vrele[a].val0));
            break;
          case 3:
            json.put("pos", String(vrele[a].pos));
            json.put("humi", String(vrele[a].val0));
            break;
        }
      } else {
        Serial.parseInt(); Serial.parseInt(); Serial.parseInt();
        switch (b) {
          case 0: break;
          case 1:
            json.put("pos", String(vrele[a].pos));
            json.put("timeS", String(vrele[a].val0));
            json.put("timeE", String(vrele[a].val1));
            break;
          case 2:
            json.put("pos", String(vrele[a].pos));
            json.put("temp", String(vrele[a].val0));
            break;
          case 3:
            json.put("pos", String(vrele[a].pos));
            json.put("humi", String(vrele[a].val0));
            break;
        }
      }
    }
    send(json.get());
    memory_commit();
  }

}
