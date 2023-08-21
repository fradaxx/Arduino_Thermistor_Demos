// Thermistor-based thermostat with hysteresis and with LCD

// Uncomment only one of the following lines to select the correct LCD backpack
#define PCF8475_LCD_BACKPACK
//#define ADAFRUIT_LCD_BACKPACK

#ifdef PCF8475_LCD_BACKPACK
#include <LiquidCrystal_I2C.h> // LCD connected to the I2C bus by the Adafruit LCD Backpack 
#elif defined (ADAFRUIT_LCD_BACKPACK)
#include "Adafruit_LiquidCrystal.h" // LCD connected to the I2C bus by the PCF8574-based adapter
#endif

#include "thermistor2.h"

#define RP			    10000
#define THRESHOLD_AIN   A7
#define THERMISTOR_AIN  A6
#define LED_PIN         A2
#define TMIN            20.0
#define TMAX            40.0
#define HYSTERESIS      2.0


// Symbols to correctly drive the load control relay
#define HEATER_ON   LOW
#define HEATER_OFF  HIGH


#ifdef PCF8475_LCD_BACKPACK
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#elif defined (ADAFRUIT_LCD_BACKPACK)
Adafruit_LiquidCrystal lcd(0); // default address #0 (A0-A2 not jumpered)
#endif

thermistor myNTC(THERMISTOR_AIN, RP, LOWSIDE); // Define a thermistor object connected on the lowside of a voltage divider with pull-up resistor equal to Rp
float temperature, setpoint, th, tl;

void setup() {
	myNTC.initSHModel(A, B, C); // Initialize myNTC with its Steinhart-Hart model parameters

#ifdef PCF8475_LCD_BACKPACK

	lcd.init();   // Initialize the lcd 
	lcd.backlight(); // Enable the LCD backlight

#elif defined(ADAFRUIT_LCD_BACKPACK)

	lcd.begin(20, 4); // set up the LCD's number of rows and columns
	lcd.setBacklight(HIGH); // Enable the LCD backlight

#endif

	Serial.begin(115200);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
	Serial.println("temperature threshold");
}

void loop() {
	temperature = myNTC.getTemp();
	setpoint = TMIN + (TMAX - TMIN) * analogRead(THRESHOLD_AIN) / 1023;
	th = setpoint + HYSTERESIS / 2;
	tl = setpoint - HYSTERESIS / 2;

	lcd.setCursor(0, 0);
	lcd.print("T=");
	lcd.print(temperature);
	lcd.print(" C");

	lcd.setCursor(0, 1);
	lcd.print("THR=");


	lcd.print(tl);
	lcd.print(", ");
	lcd.print(th);
	lcd.print(" C");

	// Thermostat implementation
	if (temperature > th)
		digitalWrite(LED_PIN, HEATER_OFF);
	else if (temperature < tl)
		digitalWrite(LED_PIN, HEATER_ON);
	else {
		// Current temperature is in the hysteresis window => don't do anything!
	}

	Serial.print(temperature);
	Serial.print(", ");
	Serial.print(th);
	Serial.print(", ");
	Serial.print(tl);
	Serial.print(", ");
	Serial.println(digitalRead(LED_PIN) ? "0" : "1");

	delay(200);
}
