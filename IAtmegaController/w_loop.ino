void loop() {
  serial_tick();
  uint16_t rtime = RTIME;
  for (int i = 0; i < prefs.timers_count; i++) {
    if (rtime == timers[i].val) {
      digitalWrite(channel[timers[i].channel], timers[i].pos);
    }
  }
}
