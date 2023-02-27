void setup() {
  DEBUG_BEGIN
  DEBUG("START SETUP")
  setup_serial();
  setup_server();
  delay(100);
  DEBUG("START LOOP\n")
}
