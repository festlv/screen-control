/*
Volvo RTI screen control
 
 */

#include "pins.h"
#include "rti.h"
#include "melbus.h"
#include "canbus.h"


void setup()  
{
	#ifdef DEBUG
		Serial.begin(500000);
		Serial.write("Debugging started");
	#endif 
	//rti_setup();
	//melbus_setup();
	canbus_setup();
}

void loop() // run over and over
{	
	//rti_loop();
	//melbus_loop();
	canbus_loop();
}
