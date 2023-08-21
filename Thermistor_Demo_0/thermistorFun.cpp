#include "Arduino.h"
#include "thermistorFun.h"


float thermistorReadBeta(uint8_t Tpin, float RP, float BETA, float R0, float T0, thermistorConnectionType_t ctype)
{
	int Vo;
	float Rt, T;

	Vo = analogRead(Tpin);

	if (ctype == LOWSIDE)
		Rt = RP * (1023.0 / float(Vo) - 1.0);
	else
		Rt = RP / (1023.0 / float(Vo) - 1.0);

	T = BETA * T0 / (T0 * log(Rt / R0) + BETA) - 273.15; // estimated temperature in celsius degrees

	return T;
}

// Function to be used when the Steinhart-Hart model parameters (A, B and C) are known
float thermistorReadSH(uint8_t Tpin, float RP, float c1, float c2, float c3, thermistorConnectionType_t ctype)
{
	int Vo;
	float Rt, logRt, T;

	Vo = analogRead(Tpin);

	if (ctype == LOWSIDE)
		Rt = RP * (1023.0 / float(Vo) - 1.0);
	else
		Rt = RP / (1023.0 / float(Vo) - 1.0);

	logRt = log(Rt);
	T = (1.0 / (c1 + c2 * logRt + c3 * logRt * logRt * logRt)) - 273.15;

	return T;
}
