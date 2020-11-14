#include <avr/io.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
						0x7D, 0x07, 0x7F, 0x6F};

void delay(unsigned long x)
{
	while(x--);
}

void find_display(unsigned char digit0, unsigned char digit1,
					unsigned char digit2, unsigned char digit3)
{
	int i;
	for(i=0; i<1000; i++)
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
}

int main() 
{
	unsigned char digit0, digit1, digit2, digit3;
	int h_value, l_value;

	DDRB = 0xFF;
	DDRG = 0xFF;
	PORTB = 0xFF;
	PORTG = 0xFF;

	TCCR1 = 0x7F;

	while(1)
	{
		h_value = TCNT1H;
		l_value = TCNT1L;

		digit0 = h_value / 1000;
		digit1 = (h_value % 1000) / 100;
		digit2 = (h_value % 100) / 10;
		digit3 = h_value % 10;

		find_display(digit0, digit1, digit2, digit3);

		digit0 = l_value / 1000;
		digit1 = (l_value % 1000) / 100;
		digit2 = (l_value % 100) / 10;
		digit3 = l_value % 10;

		find_display(digit0, digit1, digit2, digit3);
		
	}
}
