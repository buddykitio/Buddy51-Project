#include "Delay.h"

void DelayXus(u8 xUs) {
	while(xUs != 0) {
		NOP();
		xUs--;
	}
}
