#pragma once
#include "Arduino.h"
#include "math.h"

// Uncomment the line corrisponding to the sensor that you would like to use
#define IWORX_TMN100
//#define BLACK_NTC
//#define KEYSIGHT_E2308A
//#define USERS_BETA_MODEL
//#define USERS_STEINHART_HART_MODEL


#ifdef IWORX_TMN100
// Steinhart-Hart model parameters for the iWorx TMN-100 (experimentally determined using the Fluke 9133 calibrator):
#define A	0.001321226794797
#define B	1.938560203959093e-04
#define C	2.798821325050147e-07
#elif defined(BLACK_NTC)
#define BETA	4037.251
#define R0		10194.096
#define T0		298.15
#elif defined(KEYSIGHT_E2308A)
#define BETA	4007.859
#define R0		5000
#define T0		298.15
#elif defined(USERS_BETA_MODEL)
// Values BETA, R0 and T0 must be defined externally
#elif defined(USERS_STEINHART_HART_MODEL)
// Values of A, B and C parameters must be defined externally
#endif

// Modalità di connessione del termistore
typedef enum thermistorConnectionType_t {
    LOWSIDE = 0, // il termistore è connesso verso GND
    HIGHSIDE // il termistore è connesso verso VCC
};

// Modello utilizzato per la rappresentazione della caratteristica T-R del termistore
typedef enum thermistorModel_t {
    BETA = 0,
    STEINHART_HART
};


class thermistor {
public:
    thermistor(int pin, float Rp, thermistorConnectionType_t p);

    void initSHModel(float c1, float c2, float c3);
    void initBetaModel(float beta, float R0, float T0);
    float getTemp();
    void setPolarizationResistance(float Rp);
    void setSHModelParameters(float c1, float c2, float c3);
    void setBetaModelParameters(float beta, float R0, float T0);
    void setConnectionType(thermistorConnectionType_t p);
    
private:
    int _pin;
    float _Rp;
    float _A, _B, _C;
    float _beta, _R0, _T0;
    thermistorConnectionType_t _connectionType;
    thermistorModel_t _thermistorModel;
};
