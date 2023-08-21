#pragma once
#include "math.h"

class thermistor {//Crea classe Thermistor
public:
	thermistor(int pin);
	thermistor(int pin, float RPU, float c1, float c2, float c3);
	float getTemp(); // compute the sensed temperature in celsius degrees
	void setPullupResistance(float Rfix); // set/modify value of the pull-up resistor
	void setSHModelParameters(float c1, float c2, float c3); // set/modify the Steinhart-Hart coefficients

private:
	int _pin;
	float _Rpu;
	float _A, _B, _C;
};
