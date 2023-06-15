void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  setup_serial();
  setup_memory();
  D("SETUP\n")
}

void loop() {
  loop_serial();
  loop_slot();
}
