#include <avr/io.h>

int main(void){
	
	unsigned char input_data;
	DDRD = 0x00;
	DDRB = 0xFF;
	
	while(1) {
		input_data = PIND & 0x0F;
		if(input_data > 7) {
			PORTB = 0x00;
		}
		else {
			PORTB = 1 << input_data;
		}
	}

	return 0;
}
