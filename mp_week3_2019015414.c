#include <avr/io.h>

void my_delay(unsigned long x) {
	while(x--);
}

int main(void){
	DDRB = 0xFF;
	PORTB = 0x1;
	while(1) {
		my_delay(100000);
		if(PORTB != 0x80) PORTB = PORTB << 1;
		else PORTB = 0x1;
	}
	return 0;
}
