//arg=/*n*/ if(carg>=arg){arg=0;carg=0; /*code*/}
void loop_serial() {
  /**************** READ SERIAL ****************/
  if (!Serial.available()) return; // not available -> exit
  D("SA")
  if (arg == 0) { // normal
    request = Serial.readStringUntil('\n');
    if (request == "" || request == "\n" || request == "n") return;
    D(request)
  }
  if (carg < arg) { // if want args
    char ch = Serial.peek();
    if ((ch < '0' || ch > '9') && ch != '=') { // if error in args read
      arg = 0; carg = 0;
      request = "";
      SEND_BAD_REQUEST;
      return;
    }
    n[carg++] = Serial.parseInt();
    D(n[carg - 1])
    if (carg < arg) return;
  }
  /**************** CHANGE COMMAND ****************/
  switch (request[0]) {
    case 'i': // Upload information
      J(F("ATMV"), VERSION);
      J(F("count_devices"), COUNT_DEVICES);
      J(F("count_sensors"), COUNT_SENSORS);
      J(F("count_slots"), COUNT_SLOTS);
      SEND_JSON;
      break;
    case 'c': // Command
      if (request[1] == '0') {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        SEND_OK;
      } else {
        SEND_NOT_IMPLEMENTED;
      }
      break;
    case 's': // Slot
      switch (request[1]) {
        case 'l': // Get list of available slots (and counts)
          J(F("count"), COUNT_SLOTS);
          get_slots_list();
          SEND_JSON;
          break;
        case 'i': // Get slot information
          arg = 1;
          if (carg >= arg) {
            arg = 0; carg = 0;
            get_slot(n[0]);
            SEND_JSON;
          }
          break;
        case 'e': // Edit slot
          arg = 9;
          if (carg >= arg) {
            arg = 0; carg = 0;
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
    case 'd': // Device
      switch (request[1]) {
        case 'l': // List of device
          J(0, device_name[2]);
          J(1, device_name[2]);
          J(2, device_name[1]);
          J(3, device_name[1]);
          J(4, device_name[1]);
          J(5, device_name[1]);
          SEND_JSON;
          break;
        case 'i': // Get device information
          SEND_NOT_IMPLEMENTED;
          break;
        case 'e': // Device edit
          SEND_NOT_IMPLEMENTED;
          break;
        default:
          SEND_BAD_REQUEST;
          break;
      }
      break;
    case 'r': // Sensor
      switch (request[1]) {
        case 'l': // List of sensor
          J(0, sensor_name[0]);
          J(1, sensor_name[1]);
          J(2, sensor_name[2]);
          SEND_JSON;
          break;
        case 'i': // Get sensor information
          SEND_NOT_IMPLEMENTED;
          break;
        case 'e': // Sensor edit
          SEND_NOT_IMPLEMENTED;
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
