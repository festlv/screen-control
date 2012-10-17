#include <Arduino.h>


#include "rti.h"
#include "pins.h"


int current_display_mode = RTI_PAL;
bool send_brightness = true;
char current_brightness_level = 15;

const int rti_bit_delay = 410;

void rti_setup() {
	pinMode(RTI_SERIAL_TX, OUTPUT);
}

inline void rti_tx_bit_delay() {
	unsigned long wait = micros()+rti_bit_delay;
	while (wait>micros()) {};
}

void rti_loop() {
	rti_bitbang_tx(display_modes[current_display_mode]);
	delay(rti_delay);
	
	if (send_brightness)
		rti_bitbang_tx(brightness_levels[current_brightness_level]);
	else
		rti_bitbang_tx(0x40);
	
	delay(rti_delay);
	
	rti_bitbang_tx(0x83);
	delay(rti_delay);	
}

void rti_set_brightness(char level) {
	if (level>0 && level<16) {
		current_brightness_level = level;
		send_brightness = true;
	}
}

void rti_disable_screen() {
	current_display_mode = RTI_OFF;
}

void rti_enable_screen() {
	current_display_mode = RTI_PAL;
}

//inverted logic serial bitbang transmit
void rti_bitbang_tx(char byte_to_tx) {

	digitalWrite(RTI_SERIAL_TX, HIGH);
	rti_tx_bit_delay();

	for (byte mask = 0x01; mask; mask <<= 1)
    {
      if (byte_to_tx & mask) // choose bit
        digitalWrite(RTI_SERIAL_TX, LOW); // send 1
      else
        digitalWrite(RTI_SERIAL_TX, HIGH); // send 0
    
      rti_tx_bit_delay();
    }
    digitalWrite(RTI_SERIAL_TX, LOW); // restore pin to natural state
    rti_tx_bit_delay();

}

