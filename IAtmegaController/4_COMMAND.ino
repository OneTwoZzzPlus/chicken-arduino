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
            rele_set(a);
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
