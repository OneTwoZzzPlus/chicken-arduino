void setup() {
  DEBUG_BEGIN
  // Communication connect
  Serial.begin(9600);
  Serial.setTimeout(100);
  // Preferences memory
  memory_begin();
  // I2C
  isbme = bme.begin(I2C_BUSS.BME);
  isrtc = rtc.begin();
  // PIN
  pinMode(PIN.RELE0, OUTPUT);
  pinMode(PIN.RELE1, OUTPUT);
  pinMode(PIN.RELE2, OUTPUT);
  pinMode(PIN.RELE3, OUTPUT);
  digitalWrite(PIN.RELE0, 1);
  digitalWrite(PIN.RELE1, 1);
  digitalWrite(PIN.RELE2, 1);
  digitalWrite(PIN.RELE3, 1);
  // LED
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}
