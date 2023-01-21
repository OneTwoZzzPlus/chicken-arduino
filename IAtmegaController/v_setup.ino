JSONobject json;
GyverBME280 bme;
MicroDS3231 rtc;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(3, OUTPUT);
  if (!bme.begin(I2C_BUSS.BME)) {/*NO BME280 condition*/}
  if (!rtc.begin()) {/*NO DS3231 condition*/}
  
}
