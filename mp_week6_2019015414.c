#include <avr/io.h>
#define KEY_CTRL PORTE
#define RO 0x10

const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
						0x7D, 0x07, 0x7F, 0x6F}

void delay(unsigned long x) {
	while(x--);
}

unsigned char key_scan(void) {
	unsigned char scan = 0;
	unsigned char key_control = 0;
	unsigned char input_data = 0;
	unsigned char key = 0;

	key_control = R0;

	for(scan = 0; scan < 4; scan++) {
		KEY_CTRL &= 0x0F;
		KEY_CTRL |= key_control;
		delay(1);
		input_data = PINF & 0x07;

		if(input_data != 0) {
			key = (input_data >> 1) + 1 + scan * 3;
		}

		key_control <<= 1;
	}
	return key;
}

int main(void){
	
	unsigned char rotary_swith_input_data, key_pad_input_data;
	unsigned char ans;
	unsigned char led_input_data;
	unsigned char digit1, digit0;
	DDRA = 0xFF; // LED
	DDRB = 0xFF: // FND1
	DDRC = 0xFF; // FND2
	DDRD = 0x00; // ROTARY_SWITH
	DDRF = 0x00; // KEY_PAD
	
	while(1) {
		rotary_swith_input_data = PIND & 0x0F;
		key_pad_input_data = key_scan();
		ans = rotary_swith_input_data - key_pad_input_data;
		led_input_data = ans & 0x0F;
		PORTA = led_input_data;
		digit1 = ans / 10;
		digit0 = ans % 10;
		PORTB = FONT(digit1);
		PORTC = FONT(digit0);
		delay(1000);
	}

	return 0;
}
