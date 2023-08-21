#include <thermistor2.h>

#define	RP				10000
#define THERMISTOR_AIN  A6

thermistor myNTC(THERMISTOR_AIN, RP, LOWSIDE);  // Define a thermistor object connected on the lowside of a voltage divider with pull-up resistor equal to Rp

void setup() {
	myNTC.initSHModel(A, B, C);

	Serial.begin(115200);
	Serial.println("temperature");
}

void loop() {
	Serial.println(myNTC.getTemp());
	delay(200);
}
