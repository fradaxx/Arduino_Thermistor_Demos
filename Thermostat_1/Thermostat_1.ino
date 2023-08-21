#include <thermistor2.h>


#define RP              10000
#define THERMISTOR_AIN  A6
#define THRESHOLD       30.0
#define LED_PIN         A2

thermistor myNTC(THERMISTOR_AIN, RP, LOWSIDE);  // Define a thermistor object connected on the lowside of a voltage divider with pull-up resistor equal to Rp

void setup() {
	myNTC.initSHModel(A, B, C); // Initialize myNTC with its Steinhart-Hart model parameters

	Serial.begin(9600);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	Serial.println("temperature threshold");
}

void loop() {
	float temperature = myNTC.getTemp();
	if (temperature > THRESHOLD)
		digitalWrite(LED_PIN, LOW);
	else
		digitalWrite(LED_PIN, HIGH);

	Serial.print(temperature);
	Serial.print(" ");
	Serial.println(THRESHOLD);
	delay(200);
}
