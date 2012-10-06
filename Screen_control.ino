/*
Volvo RTI screen control
 
 */

#include "rti.h"
#include <SoftwareSerial.h>

void setup()  
{
rti_setup();

}

void loop() // run over and over
{
rti_loop();
}
