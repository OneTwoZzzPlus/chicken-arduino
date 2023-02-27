uint64_t off_timer[MODULE_COUNT]; byte off_pin[MODULE_COUNT]; bool off_pos[MODULE_COUNT];

void loop() {
  serial_tick();
  uint16_t rtime = RTIME;
  for (int i = 0; i < pref.timers_count; i++) {
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
          off_pin[i] = pin[i];
          off_timer[i] = millis()+(timers[i].val0*1000);
          off_pos[i] = 1;
        }
        digitalWrite(module[timers[i].module], timers[i].pos);
      }
      //digitalWrite(module[timers[i].module], timers[i].pos);
    }
  }
  for (int i = 0; i < MODULE_COUNT; i++) {
    if (millis() >= off_timer[i]) {
      digitalWrite(off_pin[i], off_pos[i]);
    }
  }
  
}
