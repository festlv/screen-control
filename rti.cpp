#include <Arduino.h>


#include "rti.h"
#include "pins.h"


SoftwareSerial rti_serial(RTI_SERIAL_RX, RTI_SERIAL_TX, true); 

int current_display_mode = RTI_PAL;
bool send_brightness = true;
char current_brightness_level = 7;


void rti_setup() {
	rti_serial.begin(2400);
}

void rti_loop() {
	rti_serial.write(display_modes[current_display_mode]);
	delay(rti_delay);
	
	if (send_brightness)
		rti_serial.write(brightness_levels[current_brightness_level]);
	else
		rti_serial.write(0x40);
	delay(rti_delay);
	
	rti_serial.write(0x83);
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