void setup() {
  DEBUG_BEGIN
  DEBUG("START SETUP")
  atmega.begin(9600);
  DEBUG("Atmega serial started")
  setup_server();
  delay(100);
  DEBUG("START LOOP\n")
}
