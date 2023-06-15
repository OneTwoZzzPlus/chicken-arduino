#include <EEPROM.h>
#include "painter.h"

#define VERSION "0.1"
#define INIT_BYTE 'q'
#define DEBUG

/* При частом RESET сменить INIT_BYTE (6 строка)
 * ЕСЛИ НЕ ПОМОГЛО ПРОВЕРИТЬ
 *  -заполненность массивов: 
 *      funcs (2 строка work_define)
 *      sensor и device (define)
 *  
 * Закоментировать 13 строку work_define =
 * = отключить работу слотов
 */

/* MODE
 * 0 - event
 * 1 - border
 */
