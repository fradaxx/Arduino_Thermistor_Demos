// Themistor-based single-threshold thermostat with settable threshold 

#include "thermistor2.h"

#define RP              10000
#define THRESHOLD_AIN   A7
#define THERMISTOR_AIN  A6
#define LED_PIN         A2
#define TMIN            20.0
#define TMAX            40.0

float temperature, setpoint;
thermistor myNTC(THERMISTOR_AIN, RP, LOWSIDE); // Define a thermistor object connected on the lowside of a voltage divider with pull-up resistor equal to Rp

void setup() {
	myNTC.initSHModel(A, B, C); // Initialize myNTC with its Steinhart-Hart model parameters

	Serial.begin(9600);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	Serial.println("temperature threshold");
}

void loop() {
	temperature = myNTC.getTemp();
	setpoint = TMIN + (TMAX - TMIN) * analogRead(THRESHOLD_AIN) / 1023;

	if (temperature > setpoint)
		digitalWrite(LED_PIN, LOW);
	else
		digitalWrite(LED_PIN, HIGH);

	Serial.print(temperature);
	Serial.print(" ");
	Serial.println(setpoint);
	delay(200);
}
