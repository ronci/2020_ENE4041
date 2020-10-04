#include <avr/io.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
						0x7D, 0x07, 0x7F, 0x6F}

void delay(unsigned long x) {
	while(x--);
}

int main(void){
	int i, j;
	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;

	for(i=0; i<1000; i++) {
		for(j=0; j<25; j++) {
			PORTG |= 0x0F;
			PORTG &= ~FND_C3;
			DDRB = Font[i/1000];
			delay(100);
			
			PORTG |= 0x0F;
			PORTG &= ~FND_C2;
			DDRB = Font[(i/100)%10];
			delay(100);
			
			PORTG |= 0x0F;
			PORTG &= ~FND_C1;
			DDRB = Font[(i/10)%10];
			delay(100);
			
			PORTG |= 0x0F;
			PORTG &= ~FND_C0;
			DDRB = Font[i%10];
			delay(100);
		}
	}
	return 0;
}
