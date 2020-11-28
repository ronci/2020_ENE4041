#include <avr/io.h>
#include <avr/interrupt.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

#define TRUE 1
#define FALSE 0

int i, check;
const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
						0x7D, 0x07, 0x7F, 0x6F};

void delay(unsigned long x)
{
	while(x--);
}

void find_display(unsigned char digit0, unsigned char digit1,
					unsigned char digit2, unsigned char digit3)
{
	PORTG |= 0x0F;
	PORTG &= ~FND_C0;
	PORTB = Font[digit0];
	delay(100);
	
	PORTG |= 0x0F;
	PORTG &= ~FND_C1;
	PORTB = Font[digit1];
	delay(100);
	
	PORTG |= 0x0F;
	PORTG &= ~FND_C2;
	PORTB = Font[digit2];
	delay(100);
	
	PORTG |= 0x0F;
	PORTG &= ~FND_C3;
	PORTB = Font[digit3];
	delay(100);
}

SIGNAL(SIG_INTERRUPT1) {
	int j;
	unsigned char digit0, digit1, digit2, digit3;
	if(check == TRUE) {
		check = FALSE;
		j = i;
		i = 10000;
		digit0 = j / 1000;
		digit1 = (j % 1000) / 100;
		digit2 = (j % 100) / 10;
		digit3 = j % 10;
		while(1) {
			find_display(digit0, digit1, digit2, digit3);
		}
	}
	else {
		check = TRUE;
	}
}

int main() 
{
	unsigned char digit0, digit1, digit2, digit3;
	int j;

	DDRB = 0xFF;
	DDRG = 0xFF;
	PORTB = 0x00;
	PORTG = 0xFF;

	EIMSK = 0xFF;

	EICRA = 0xFF;
	EICRB = 0xFF;

	sei();

	while(1)
	{
		if(check == TRUE) {
			for(i=0; i<10000; i++) {

				digit0 = i / 1000;
				digit1 = (i % 1000) / 100;
				digit2 = (i % 100) / 10;
				digit3 = i % 10;

				for(j=0; j<10; j++) {
					find_display(digit0, digit1, digit2, digit3);
				}
			}
		}
		
	}
}
