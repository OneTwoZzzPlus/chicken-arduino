void loop() {
  rtime = RTIME;
  serial_tick();
  for (uint8_t i = 0; i < COUNT_RELE; i++) { rele_tick(i); }
}

/*for (int i = 0; i < pref.timers_count; i++) {
    if (rtime == timers[i].val) {
      if (module[timers[i].module] == 1) { // rele
        switch (pref.mode[i]) {
          case 0: // off
          digitalWrite(pin[i], 1);
          break;
          case 1:
          digitalWrite(module[timers[i].module], timers[i].pos);
          break;
          case 2:
          digitalWrite(module[timers[i].module], 0);
        }
        digitalWrite(module[timers[i].module], timers[i].pos);
      }
      //digitalWrite(module[timers[i].module], timers[i].pos);
    }
  }*/
