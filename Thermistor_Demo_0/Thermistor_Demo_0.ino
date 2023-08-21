#include "thermistorFun.h"

#define THERMISTOR_PIN	A6 // Analog input pin for thermistor voltage 
#define RP				10000.0 // Thermistor polarization resistance


float T;


void setup() {
	Serial.begin(115200); // open serial port and set data rate to 115200 bps
	Serial.println("Thermistor temperature measurement:");
}

void loop() {
	// Value of temperature reading
	T = thermistorReadSH(THERMISTOR_PIN, RP, A, B, C, LOWSIDE);

	Serial.print(T);
	Serial.println(" °C");
	delay(200);
}
