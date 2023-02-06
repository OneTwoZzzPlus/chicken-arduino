#define R_ON 0
#define R_OFF 1

void rele_tick(uint8_t i) {
  switch (vrele[i].mode) {
    case MODE_OFF: digitalWrite(crele[i].pin, R_OFF); break;
    case MODE_TIMER_SW: 
      if (rtime != vrele[i].val0 && rtime != vrele[i].val1) return;
      if (rtime == vrele[i].val0 && vrele[i].pos == R_ON) digitalWrite(crele[i].pin, R_ON);
      else if (rtime == vrele[i].val0 && vrele[i].pos == R_OFF) digitalWrite(crele[i].pin, R_OFF);
      else if (rtime == vrele[i].val1 && vrele[i].pos == R_ON) digitalWrite(crele[i].pin, R_OFF);
      else if (rtime == vrele[i].val1 && vrele[i].pos == R_OFF) digitalWrite(crele[i].pin, R_ON);
    break;
  }
}
