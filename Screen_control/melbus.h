#ifndef MELBUS_H
#define MELBUS_H

//Public interface
void melbus_setup();
void melbus_loop();

//Private interface
void melbus_clock_int();
void melbus_signal_busy();

extern volatile uint8_t melbus_recv_byte;
extern volatile uint8_t melbus_clock;

#endif