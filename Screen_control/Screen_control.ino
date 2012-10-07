/*
Volvo RTI screen control
 
 */

#include "pins.h"
#include "rti.h"
#include "melbus.h"

void setup()  
{
	#ifdef DEBUG
		Serial.begin(115200);
		Serial.write("Debugging started");
	#endif 
	rti_setup();
	melbus_setup();

}

void loop() // run over and over
{	
	rti_loop();
	melbus_loop();

}
