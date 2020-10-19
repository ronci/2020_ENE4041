#include <avr/io.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
						0x7D, 0x07, 0x7F, 0x6F};

void delay(unsigned long x) {
	while(x--);
}

int main(void){
	unsigned int count = 0, time;
	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;
	while(1) {
		time = 1000;
		while(time--) {
			PORTG |= 0x0F;
			PORTG &= ~FND_C3;
			PORTB = Font[count%10];
			delay(100);
	
			PORTG |= 0x0F;
			PORTG &= ~FND_C2;
			PORTB = Font[(count/10)%10];
			delay(100);
		
			PORTG |= 0x0F;
			PORTG &= ~FND_C1;
			PORTB = Font[(count/100)%10];
			delay(100);
		
			PORTG |= 0x0F;
			PORTG &= ~FND_C0;
			PORTB = Font[count/1000];
			delay(100);
		}
		count++;
		if(count == 1000) break;
	}
	return 0;
}

