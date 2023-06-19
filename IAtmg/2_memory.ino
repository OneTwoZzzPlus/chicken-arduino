/**************** ADDRES ****************/
#define ADDR_INIT 0
#define ADDR_KEY 1
#define ADDR_KEY_END ADDR_KEY+KEY_LENGTH
#define ADDR_SLOT 32
#define ADDR_SLOT_END COUNT_SLOTS*BYTE_SIZE_SLOT+ADDR_SLOT+1

#if ADDR_KEY_END>ADDR_SLOT
#error "Too much key!"
#endif
#if ADDR_SLOT_END>1024
#error "Too much slots!"
#endif

#define get_slot_addr(i) BYTE_SIZE_SLOT*i+ADDR_SLOT

/**************** LOAD ****************/
char key[KEY_LENGTH];
Slot slot[COUNT_SLOTS];

void setup_memory() {
  
  if (EEPROM[ADDR_INIT] != INIT_BYTE) {
    D("MEMORY RESET")
    EEPROM[ADDR_INIT] = INIT_BYTE;
    EEPROM.put(ADDR_KEY, "key1234567");
    for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
      EEPROM.put(get_slot_addr(i), default_slot);
    }
  }
  
  D("MEMORY SETUP")
  EEPROM.get(ADDR_KEY, key);
  d("KEY = ") D(key)
  for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
    EEPROM.get(get_slot_addr(i), slot[i]);
    D(slot[i].enable)
  }
  
}
