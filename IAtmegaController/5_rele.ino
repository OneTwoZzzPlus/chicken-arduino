// Rele invert! Use macro and <value> to set
#define R_ON 0
#define R_OFF 1

void rele_tick(uint8_t i) {
  switch (vrele[i].mode) {
    case MODE_TIMER_SW:
      if (rtime >= vrele[i].val0 && rtime < vrele[i].val1) digitalWrite(crele[i].pin, vrele[i].pos);
      else digitalWrite(crele[i].pin, !vrele[i].pos);
      break;
  }
}

void rele_set(uint8_t i) {
  switch (vrele[i].mode) {
    case MODE_OFF: digitalWrite(crele[i].pin, R_OFF); break;
    case MODE_TIMER_SW:
      if (vrele[i].val0 >= vrele[i].val1) { // err
        vrele[i].mode = MODE_OFF;
        digitalWrite(crele[i].pin, R_OFF);
      } else {
        if (rtime >= vrele[i].val0 && rtime < vrele[i].val1) digitalWrite(crele[i].pin, vrele[i].pos);
        else digitalWrite(crele[i].pin, !vrele[i].pos);
      }
      break;
  }
}
