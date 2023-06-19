/*************** SERIAL SETUP ***************/
String request;
int32_t n[9];
byte carg = 0, arg = 0;

void setup_serial() {
  Serial.begin(9600);
}
/*************** SERIAL FUNC ****************/
void get_slots_list() {
  for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
    J(slot[i].channel_device, slot[i].mode);
  }
}

void get_slot(int n) {
  J("index", n);
  J("enable", slot[n].enable);
  J("mode", slot[n].mode);
  J("channel_sensor", slot[n].channel_sensor);
  J("channel_device", slot[n].channel_device);
  J("sensor_on", slot[n].sensor_on);
  J("sensor_off", slot[n].sensor_off);
  J("device_on", slot[n].device_on);
  J("device_off", slot[n].device_off);
}

void edit_slot(int32_t n[9]) {
  slot[n[0]].enable = !!n[1];
  slot[n[0]].mode = n[2];
  slot[n[0]].channel_sensor = n[3];
  slot[n[0]].channel_device = n[4];
  slot[n[0]].sensor_on = n[5];
  slot[n[0]].sensor_off = n[6];
  slot[n[0]].device_on = n[7];
  slot[n[0]].device_off = n[8];
  EEPROM.put(get_slot_addr(n[0]), slot[n[0]]);
  get_slot(n[0]);
}
