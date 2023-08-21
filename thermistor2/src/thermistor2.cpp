#include "thermistor2.h"

thermistor::thermistor(int pin, float Rp, thermistorConnectionType_t ct) {
	_Rp = Rp;
	_pin = pin; // Analog pin to which the voltage divider is connected
	_connectionType = ct;
}

void thermistor::initSHModel(float c1, float c2, float c3) {
	_thermistorModel = STEINHART_HART;
	_A = c1;
	_B = c2;
	_C = c3;
}

void thermistor::initBetaModel(float beta, float R0, float T0) {
	_thermistorModel = BETA;
	_beta = beta; // Coefficients in the Steinhart-Hart equation
	_R0 = R0;
	_T0 = T0;
}

void thermistor::setPolarizationResistance(float Rp) {
	_Rp = Rp;
}

// Set the Steinhart-Hart model parameters
void thermistor::setSHModelParameters(float c1, float c2, float c3) {
	_A = c1;
	_B = c2;
	_C = c3;
}

// Set the beta model parameters
void thermistor::setBetaModelParameters(float beta, float R0, float T0) {   //Set dei coefficienti del modello SH
	_beta = beta;
	_R0 = R0;
	_T0 = T0;
}

// Set the thermistor connection type (LOWSIDE or HIGHSIDE)
void thermistor::setConnectionType(thermistorConnectionType_t setConnectionType) {
	_connectionType = setConnectionType;
}

// Get the temperature sensed by the thermistor, taking into account its configuration
float thermistor::getTemp() {
	int vin = analogRead(_pin);
	float Rt, logRt, logRtR0, T;

	if (_connectionType == LOWSIDE)
		Rt = _Rp / ((1023.0 / float(vin)) - 1.0);
	else
		Rt = _Rp * ((1023.0 / float(vin)) - 1.0);

	switch (_thermistorModel) {
	case STEINHART_HART:
		logRt = log(Rt);
		T = (1.0 / (_A + _B * logRt + _C * logRt * logRt * logRt)) - 273.15;
		break;

	case BETA:
		T = _beta * _T0 / (_T0 * log(Rt / _R0) + _beta) - 273.15;
		break;
	}

	return T;
}
