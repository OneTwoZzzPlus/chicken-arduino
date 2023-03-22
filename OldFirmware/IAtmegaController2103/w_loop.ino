void loop() {
  rtime = RTIME;
  serial_tick();
  for (uint8_t i = 0; i < COUNT_RELE; i++) { rele_tick(i); }
}
