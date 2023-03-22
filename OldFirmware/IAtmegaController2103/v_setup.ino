void setup() {
  DEBUG_BEGIN
  // Communication connect
  Serial.begin(9600);
  Serial.setTimeout(1000);
  // Preferences memory
  memory_begin();
  // I2C
  isbme = bme.begin(I2C_BUSS.BME);
  isrtc = rtc.begin();
  // SET
  rtime = RTIME;
  // PIN
  pinMode(PIN.RELE0, OUTPUT);
  pinMode(PIN.RELE1, OUTPUT);
  pinMode(PIN.RELE2, OUTPUT);
  pinMode(PIN.RELE3, OUTPUT);
  for (uint8_t i = 0; i < COUNT_RELE; i++) { rele_set(i); }
  // LED
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}
