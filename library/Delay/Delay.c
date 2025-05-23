#include "Delay.h"

 void DelayXus(u8 xUs) {
	while(xUs != 0) {
		NOP();
		xUs--;
	}
}

void DelayXms(u16 xMs){
#if DELAY_TIMER //Timer 1
	TMOD &= 0x0F;
	TMOD |= 0x10;
	while(xMs--){
		TH1 = THX;
		TL1 = TLX;
		TR1 = 1;
		while(TF1 != 1);
		TR1 = 0;
		TF1 = 0;
	}

#else //Timer 0
	TMOD &= 0xF0;
	TMOD |= 0x01;
	while(xMs--){
		TH0 = THX;
		TL0 = TLX;
		TR0 = 1;
		while(TF0 != 1);
		TR0 = 0;
		TF0 = 0;
	}
#endif
}