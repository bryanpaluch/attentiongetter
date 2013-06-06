#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

int main(void)
{
	uint8_t d;
	uint8_t d_prev=0xFF;

	CPU_PRESCALE(0);
	DDRD = 0x00;
	PORTD = 0x00;
	
	usb_init();
	
	while (!usb_configured());
	
	_delay_ms(1000);


	while (1) {
		d = PIND;
		if (((d & 0x01) == 0) && (d_prev & 0x01) != 0) {
			
			keyboard_modifier_keys = KEY_CTRL;
			keyboard_keys[0] = 0;
			keyboard_keys[1] = 0;
			keyboard_keys[2] = 0;
			keyboard_keys[3] = 0;
			keyboard_keys[4] = 0;
			keyboard_keys[5] = 0;
			usb_keyboard_send();
			_delay_ms(50);
			
			keyboard_modifier_keys = KEY_CTRL | KEY_ALT;
			usb_keyboard_send();
			_delay_ms(50);
			keyboard_keys[0] = KEY_P;
			usb_keyboard_send();
			_delay_ms(150);
			keyboard_keys[0] = 0;
			usb_keyboard_send();
			_delay_ms(50);
			keyboard_modifier_keys = 0;
			usb_keyboard_send();
		}
		
		d_prev = d;
		_delay_ms(20);
	}
	
	
	return 0;
}
