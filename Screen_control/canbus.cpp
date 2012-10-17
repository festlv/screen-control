#include <Arduino.h>
#include "CAN.h"
#include "pins.h"

unsigned long next_delay = 0;

void canbus_setup() {
	pinMode(9, OUTPUT);
	digitalWrite(9, HIGH);
	CAN.begin();
	CAN.isInitialized();
	CAN.setMode(CONFIGURATION);
	CAN.isInitialized();
	CAN.baudConfig(1000);
	CAN.isInitialized();
	CAN.setMode(LOOPBACK);
	delay(100);
	CAN.isInitialized();
	next_delay = millis() + 1000;
}



void printBuf(byte rx_status, byte length, uint32_t frame_id, byte filter, byte buffer, byte *frame_data, byte ext) {
       
      Serial.print("[Rx] Status:");
      Serial.print(rx_status,HEX);
      
      Serial.print(" Len:");
      Serial.print(length,HEX);
      
      Serial.print(" Frame:");
      Serial.print(frame_id,HEX);

      Serial.print(" EXT?:");
      Serial.print(ext==1,HEX);
       
      Serial.print(" Filter:");
      Serial.print(filter,HEX);

      Serial.print(" Buffer:");
      Serial.print(buffer,HEX);
      
      Serial.print(" Data:[");
      for (int i=0;i<8;i++) {
        if (i>0) Serial.print(" ");
        Serial.print(frame_data[i],HEX);
      }
      Serial.println("]"); 
}

void canbus_loop() {
	byte length,rx_status,filter,ext;
	long unsigned int frame_id;
	byte frame_data[8];

	//clear receive buffers, just in case.
	frame_data[0] = 0x00;
	frame_data[1] = 0x00;
	frame_data[2] = 0x00;
	frame_data[3] = 0x00;
	frame_data[4] = 0x00;
	frame_data[5] = 0x00;
	frame_data[6] = 0x00;
	frame_data[7] = 0x00;

	frame_id = 0x0000;

	length = 0;

	rx_status = CAN.readStatus();

	if ((rx_status & 0x40) == 0x40) {
		CAN.readDATA_ff_0(&length,frame_data,&frame_id, &ext, &filter);
		printBuf(rx_status, length, frame_id, filter, 0, frame_data, ext);
		CAN.clearRX0Status();
		rx_status = CAN.readStatus();
		Serial.println(rx_status,HEX);
	}

	if ((rx_status & 0x80) == 0x80) {
		CAN.readDATA_ff_1(&length,frame_data,&frame_id, &ext, &filter);
		printBuf(rx_status, length, frame_id, filter, 1, frame_data, ext);       
		CAN.clearRX1Status();
		rx_status = CAN.readStatus();
		Serial.println(rx_status,HEX);
	}




	if (next_delay<millis()) {
		frame_data[0] = 0x55;
		frame_data[1] = 0xA4;
		frame_data[2] = 0x04;
		frame_data[3] = 0xF4;
		frame_data[4] = 0x14;
		frame_data[5] = 0xC4;
		frame_data[6] = 0xFC;
		frame_data[7] = 0x1D;

		frame_id = 0x1230000;
		length = 8;
		CAN.load_ff_0(length,&frame_id,frame_data, true);
      	delay(6000);    

      
		next_delay = millis()+1000;
		Serial.println("Sending message");
		CAN.isInitialized();
	}
	delay(1000);
}

