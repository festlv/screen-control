#include <Arduino.h>

#include "melbus.h"
#include "pins.h"

volatile uint8_t melbus_recv_byte = 0;
volatile uint8_t melbus_clock = 7;


const int melbus_buffer_length = 7;
volatile uint8_t melbus_data_buffer[melbus_buffer_length] = {0, 0, 0, 0 ,0, 0, 0};


#ifdef DEBUG
	volatile bool send_byte = false;
	volatile uint8_t melbus_byte_copy = 0;
#endif

/**
Sets up interrupts for Melbus communication and performs initial Melbus handshake/sequence
*/

void melbus_setup() {
	pinMode(3, INPUT);
	pinMode(MELBUS_DATA, INPUT_PULLUP);
	attachInterrupt(MELBUS_CLOCK_INT, melbus_clock_int, RISING);
	melbus_signal_busy();
}

void melbus_loop() {
	#ifdef DEBUG
		if (send_byte) {
			Serial.write(melbus_byte_copy);
			send_byte=false;
		}
	#endif

}

/*
Notifies HU by pulling BUSY line low for 1s
*/
void melbus_signal_busy() {
	pinMode(MELBUS_BUSY, OUTPUT);
	digitalWrite(MELBUS_BUSY, LOW);
	delay(1000);
	pinMode(MELBUS_BUSY, INPUT_PULLUP);
}


void melbus_clock_int() {

	if (PIND & (1<<PIND7))
		melbus_recv_byte |= (1<<melbus_clock);
	else
		melbus_recv_byte &=~(1<<melbus_clock);
	
	if (melbus_clock==0) {
		#ifdef DEBUG
			melbus_byte_copy = melbus_recv_byte;
			send_byte = true;
		#endif
		melbus_clock=7;
	} else {
		melbus_clock--;
	}
}