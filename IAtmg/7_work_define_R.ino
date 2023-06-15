/*************** WORK FUNC ***************/
void empty(uint8_t i) {  }//D(F("WORK"))}
void (*funcs[COUNT_DEVICE_TYPE][COUNT_SENSOR_TYPE])(uint8_t) = {
  {empty,empty,empty},
  {empty,empty,empty},
  {empty,empty,empty}
};

/**************** LOOPER ****************/
void loop_slot() {
  for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
    if (!slot[i].enable) continue;
    uint8_t x = device[slot[i].channel_device].type;
    uint8_t y = sensor[slot[i].channel_sensor].type;
    funcs[x][y](i); //RESET 
  }
}
