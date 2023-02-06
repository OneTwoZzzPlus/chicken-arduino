void serial_tick() {
  if (!Serial.available()) return;
  String s = Serial.readStringUntil('\\');
  int len = s.length();
  json.clear();
  int i = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
  digitalWrite(3, !digitalRead(3));

  switch (s[0]) {
    ////////////////////
    case 'c':
      switch (s[1]) {
        //////////
        case '0': //c0 - null command
          send(String(digitalRead(3)));
        break;
        //////////
        case 'r': //cr - reset
          memory_reset();
          send(F("Reset!"));
        break;
        //////////
        case 'i': //ci - BME+RTC information
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
        break;
        //////////
        case 'l': //cl - modules list
          json.put("COUNT_MODULE", COUNT_MODULE);
          json.put("0", MODULE_MAIN);
          json.put("1", MODULE_RELE);
          json.put("2", MODULE_RELE);
          json.put("3", MODULE_RELE);
          json.put("4", MODULE_RELE);
          send(json.get());
        break;
        //////////
        case 'm': //cm - module info
          // read index
          i = 2; while(i < len) {a = (a*10)+(s[i]-'0'); i++; }
          // valid index
          if (a<0 || a>=COUNT_MODULE) { send("No module index "+String(a)); return; }
          // change module type
          if (a==0) { //main
            json.put("type", MODULE_MAIN);
            json.put("mode", vmain.mode);
          } else if (a>0&&a<COUNT_MODULE) { a--; //rele
            json.put("type", MODULE_RELE);
            json.put("mode", vrele[a].mode);
            json.put("pos", String(vrele[a].pos));
            json.put("val0", String(vrele[a].val0));
            json.put("val1", String(vrele[a].val1));
          }
          send(json.get());
        break;
        //////////
        case 'e': //ce[index]=[mode] - module edit
          D("EDIT")
          // read index
          i = 2; while(s[i] != '=') {a = (a*10)+(s[i]-'0'); i++;}
          if (a<0 || a>=COUNT_MODULE) { send("No module index "+String(a)); return; }
          D(a)
          // change module type
          if (a==0) { //main
            // mode
            i++; while(s[i] < len) {b = (b*10)+(s[i]-'0'); i++; }
            if (b<0 || b>=1) { send("No mode "+String(b)); return; }
            vmain.mode = b;
            json.put("type", MODULE_MAIN);
            json.put("mode", vmain.mode);
          } else if (a>0&&a<COUNT_MODULE) { a--; //rele +=[pos]=[val0]=[val1]
            // mode
            i++; while(s[i] != '=') {b = (b*10)+(s[i]-'0'); i++; }
            if (b<0 || b>=7) { send("No mode "+String(b)); return; }
            // pos
            i++; while(s[i] != '=') {c = (c*10)+(s[i]-'0'); i++; }
            if (c<0 || c>=2) { send("Pos can be 0/1, not "+String(c)); return; }
            // val0
            i++; while(s[i] != '=') {d = (d*10)+(s[i]-'0'); i++; }
            if (d<0 || d>=1440) { send("Invalide time "+String(d)); return; }
            // val1
            i++; while(i < len) {e = (e*10)+(s[i]-'0'); i++; }
            if (e<0 || e>=1440) { send("Invalide time "+String(e)); return; }
            vrele[a].mode = b;
            vrele[a].pos = c;
            vrele[a].val0 = d;
            vrele[a].val1 = e;
            json.put("type", MODULE_RELE);
            json.put("mode", vrele[a].mode);
            json.put("pos", String(vrele[a].pos));
            json.put("val0", String(vrele[a].val0));
            json.put("val1", String(vrele[a].val1));
          }
          send(json.get());
          memory_commit();
        break;
        //////////
      } // sw s[1]
    break;
    ////////////////////
    case '0':
    break;
    ////////////////////
  } // sw s[0]

} // func

/*
switch (s[0]) {
  case 'c': switch (s[1]) {
    case '0': //c0
      digitalWrite(3, HIGH);
      send("Led set to " + String(digitalRead(3)));
    break;
    case 'R': //cR - reset
      memory_reset();
    break;
  } break;
  /**********************************
  case 'i': switch (s[1]) {
    case '0': // i0
      json.clear();
      if (isbme) {
        json.put("Temperature", String(bme.readTemperature()));
        json.put("Humidity", String(bme.readHumidity()));
        json.put("Pressure", String(bme.readPressure()));
      }
      if (isrtc) {
        json.put("Time", String(rtc.getTimeString()));
        json.put("Data", String(rtc.getDateString()));
        json.put("TempDS", String(rtc.getTemperatureFloat()));
      }
      send(json.get());
    break;
    // PREFS
    case 'M': //iM
      json.put("MaxCountTimers", MAX_COUNT_TIMERS);
      json.put("CountTimers", pref.timers_count);
      json.put("CountModules", MODULE_COUNT);
      for (int i = 0; i < MODULE_COUNT; i++) {
        if (module[i] == 0) json.put(String(i), "SETTINGS");
        else if (module[i] == 1) json.put(String(i), "RELE");
      }
      send(json.get());
    break;
    // time
    case 'T':
      json.clear();
      json.put("Time", String(rtc.getTimeString()));
      json.put("Data", String(rtc.getDateString()));
      send(json.get());
    break;
    // timer
    case 't':
      if (len==3) i = s[2]-'0';
      else if (len==4) i = 10*(s[2]-'0')+(s[3]-'0');
      else { send("Invalide index timer"); return; }
      if (i<0 || i>=pref.timers_count) { send("No index timer "+String(i)); return; }
      json.clear();
      json.put("Timer", i);
      json.put("Channel", timers[i].module);
      json.put("Pos", timers[i].pos);
      json.put("Val", timers[i].val);
      send(json.get());
    break;
  } break;
  /*********************************
  case 's': switch (s[1]) {
    // TIMER
    case 't': switch (s[2]) {
      case 'e': // ste[ntimer]=[channel]=[pos]=[val(min)]
        // ntimer
        i = 3; while(s[i] != '=') { a = (a*10)+(s[i]-'0'); i++; } 
        if (a<0 || a>=pref.timers_count) { send("No index timer "+String(a)); return; }
        // channel
        i++; while(s[i] != '=') {b = (b*10)+(s[i]-'0'); i++; }
        if (b<0 || b>=MODULE_COUNT) { send("No index channel "+String(b)); return; }
        // pos
        i++; while(s[i] != '=') {c = (c*10)+(s[i]-'0'); i++; }
        if (c<0 || c>=255) { send("No pos "+String(c)); return; }
        // val
        i++; while(i < len) {d = (d*10)+(s[i]-'0'); i++; }
        if (d<0 || d>=1440) { send("Invalide time "+String(d)); return; }

        timers[a].module = b;
        timers[a].pos = c;
        timers[a].val = d;
        send("OK");
        memory_timers_commit();
      break;
      case 'a': // sta[channel]=[pos]=[val(min)]
        if (pref.timers_count >= MAX_COUNT_TIMERS-1) { send("Too many timers! MAX "+String(MAX_COUNT_TIMERS)); return; }
        // channel
        i = 3; while(s[i] != '=') {b = (b*10)+(s[i]-'0'); i++; }
        if (b<0 || b>=MODULE_COUNT) { send("No index channel "+String(b)); return; }
        // pos
        i++; while(s[i] != '=') {c = (c*10)+(s[i]-'0'); i++; }
        if (c<0 || c>=255) { send("No pos "+String(c)); return; }
        // val
        i++; while(i < len) {d = (d*10)+(s[i]-'0'); i++; }
        if (d<0 || d>=1440) { send("Invalide time "+String(d)); return; }
        timers[pref.timers_count].module = b;
        timers[pref.timers_count].pos = c;
        timers[pref.timers_count].val = d;
        pref.timers_count += 1;
        send("OK");
        memory_timers_commit();
        memory_prefs_commit();
      break;
      case 'D': // stD - delete all timers
        pref.timers_count = 0;
        send("OK");
        memory_prefs_commit();
      break;
    } break;
    // TIME
    case 'T': 
      // SEC, MIN, HOUR, DAY, MONTH, YEAR
      i = 2; while(s[i] != '=') {a = (a*10)+(s[i]-'0'); i++; }
      i++; while(s[i] != '=') {b = (b*10)+(s[i]-'0'); i++; }
      i++; while(s[i] != '=') {c = (c*10)+(s[i]-'0'); i++; }
      i++; while(s[i] != '=') {d = (d*10)+(s[i]-'0'); i++; }
      i++; while(s[i] != '=') {e = (e*10)+(s[i]-'0'); i++; }
      i++; while(i < len) {f = (f*10)+(s[i]-'0'); i++; }
      rtc.setTime(a, b, c, d, e, f);
      send("OK");
    break;
    // END S
  } break;
  }
 */
