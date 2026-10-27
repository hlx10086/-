#include "main.h"
#include "i2c.h"
//#include "usr_uart.h"
#include <string.h>

#define POWER_ON 0x01				 										// Power_On													上电
#define RESET 0x07 														 	// Reset														复位
#define CONTINUOUSLY_H_RESOLUTION_MODE 0x10 		// Continuously H-Resolution Mode 	连续高分辨率模式

#define BH1750_ADDRESS (0x23 << 1)

void BH1750_INIT(void);
int get_lx(void);