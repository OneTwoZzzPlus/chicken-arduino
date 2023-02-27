#define COUNT_MODULE 5
#define COUNT_RELE 4

#define MODE_NORMAL 0
#define MODE_OFF 0
#define MODE_TIMER_SW 1
#define MODE_TIMER_DO 2

#define MODULE_MAIN 0
struct {
  uint8_t index = 0;
} cmain;
struct {
  uint8_t mode = MODE_NORMAL;
} vmain;

#define MODULE_RELE 1
struct Crele{
  uint8_t index;
  uint8_t pin;
};
Crele crele[COUNT_RELE] = { Crele{1, 7}, Crele{2, 8}, Crele{3, A2}, Crele{4, A3} };
struct Vrele{
  uint8_t mode;
  bool pos;
  uint16_t val0;
  uint16_t val1;
};
Vrele vrele[COUNT_RELE] = {
  Vrele{MODE_TIMER_SW, 0, TIME(0,3), TIME(0,4)},
  Vrele{MODE_TIMER_SW, 0, TIME(0,4), TIME(0,5)},
  Vrele{MODE_TIMER_SW, 0, TIME(0,3), TIME(0,30)},
  Vrele{MODE_TIMER_SW, 0, TIME(0,3), TIME(1,30)}
};


#define ADDR_INIT 0
#define ADDR_MAIN 1
#define ADDR_RELE (((size_t)(&(vmain)+1)-(size_t)(&(vmain)))+1)
#define ADDR_OTHER (((size_t)(&(vrele)+1)-(size_t)(&(vrele)))+ADDR_RELE)

void memory_commit() {
  EEPROM.put(ADDR_MAIN, vmain);
  EEPROM.put(ADDR_RELE, vrele);
}
void memory_reset() { EEPROM.write(ADDR_INIT, 254); }

void memory_begin() {
  if (EEPROM.read(ADDR_INIT) != INIT_KEY) {
    EEPROM.write(ADDR_INIT, INIT_KEY);
    EEPROM.put(ADDR_MAIN, vmain);
    EEPROM.put(ADDR_RELE, vrele);
  }
  EEPROM.get(ADDR_MAIN, vmain);
  EEPROM.get(ADDR_RELE, vrele);
  
  #ifdef DEBUG_ENABLE
    d("ADDR_INIT=") D(ADDR_INIT)
    d("ADDR_MAIN=") D(ADDR_MAIN)
    d("main=") d(vmain.mode) D("")
    d("ADDR_RELE=") D(ADDR_RELE)
    for (int i=0; i<COUNT_RELE; i++) {
      d("rele[") d(i) d("]= ") d(vrele[i].mode) d(' ') d(vrele[i].pos) d(' ') d(vrele[i].val0) d(' ') d(vrele[i].val1) D("")
    }
  #endif
}
