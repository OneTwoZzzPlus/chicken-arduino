void setup_serial() {
  Serial.begin(9600);
}

String request;
int32_t n[10];
uint8_t carg, arg;
#define ARG{ if(carg>=arg){arg=0;carg=0;
void loop_serial() {
  if (!Serial.available()) return;
  D("SA")
  if (arg == 0) {
    request = Serial.readStringUntil('\n');
    if (request == "" || request == "\n" || request == "n") return;
    D(request)
  }
  if (carg < arg) {
    n[carg++] = Serial.parseInt();
    D(n[carg - 1])
    if (carg < arg) return;
  }
  switch (request[0]) {
    case 'i': // Upload information
      J(F("ATMV"), VERSION);
      J(F("count_devices"), COUNT_DEVICES);
      J(F("count_sensors"), COUNT_SENSORS);
      J(F("count_slots"), COUNT_SLOTS);
      SEND_JSON;
    break;
    case 'c': // Command
      SEND_NOT_IMPLEMENTED;
      break;
    case 's': // Slot settings
      switch (request[1]) {
        case 'l': // Get list of available slots (and counts)
          J(F("count"), COUNT_SLOTS);
          get_slots_list();
          SEND_JSON;
        break;
        case 'i': // Get slot information
          arg = 1;
          ARG{
            get_slot(n[0]);
            SEND_JSON;
          }
        break;
        case 'e': // Edit slot
          arg = 9;
          ARG{
            if (n[0] < 0 || n[0] >= COUNT_SLOTS) {
              SEND_NOT_ALLOWED;
            } else {
              edit_slot(n);
              SEND_JSON;
            }
          }
        break;
        default:
          SEND_BAD_REQUEST;
        break;
      }
      break;
    case 'l': // List
      switch (request[1]) {
        case 'd': // of device
          J("0", device_name[2]);
          J("1", device_name[2]);
          J("2", device_name[1]);
          J("3", device_name[1]);
          J("4", device_name[1]);
          J("5", device_name[1]);
          SEND_JSON;
        break;
        case 's': // of sensor
          J("0", sensor_name[0]);
          J("1", sensor_name[1]);
          J("2", sensor_name[2]);
          SEND_JSON;
        break;
        default:
          SEND_BAD_REQUEST;
        break;
      }
      break;
    default:
      SEND_BAD_REQUEST;
    break;
    }
  CLEAR_JSON;
}
