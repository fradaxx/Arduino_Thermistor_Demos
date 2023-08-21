#pragma once

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


float thermistorReadBeta(uint8_t Tpin, float Rp, float BETA, float R0, float T0, thermistorConnectionType_t ctype);
float thermistorReadSH(uint8_t Tpin, float Rp, float c1, float c2, float c3, thermistorConnectionType_t ctype);

