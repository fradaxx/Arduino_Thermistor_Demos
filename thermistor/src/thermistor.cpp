#include "thermistor.h"
#include "math.h"

thermistor::thermistor(int pin) {
	_pin = pin; // Input analogico lettura del partitore di tensione
}

thermistor::thermistor(int pin, float RP, float c1, float c2, float c3) {
	_pin = pin; // Input analogico lettura del partitore di tensione
	_Rpu = RP; // Resistenza di pull-up
	_A = c1;
	_B = c2;
	_C = c3;
}

void thermistor::setPullupResistance(float RP) {
	_Rpu = RP;    //Set del valore della resistenza a _Rfix
}

void thermistor::setSHModelParameters(float c1, float c2, float c3) {   //Set dei coefficienti del modello SH
	_A = c1;
	_B = c2;
	_C = c3;
}

float thermistor::getTemp() {
	int vin = analogRead(_pin); // Lettura voltaggio del termistore
	float Rt;
	float logRt, T;
	Rt = _Rpu * ((1023.0 / float(vin)) - 1.0);
	logRt = log(Rt);
	T = (1.0 / (_A + _B * logRt + _C * logRt * logRt * logRt)) - 273.15;

	return T;
}
