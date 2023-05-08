#include <Arduino.h>
#include "ColorDetector.h"

ColorDetector::ColorDetector(int s0, int s1, int s2, int s3, int out) 
{
	_s0 = s0;
	_s1 = s1;
	_s2 = s2;
	_s3 = s3;
	_out = out;
	_led_red_frequency = 0;
	_led_green_frequency = 0;
	_led_blue_frequency = 0;
	_led_red_value = 0;
	_led_green_value = 0;
	_led_blue_value = 0;
}

void ColorDetector::initialize() 
{
	pinMode(_s0, OUTPUT);
	pinMode(_s1, OUTPUT);
	pinMode(_s2, OUTPUT);
	pinMode(_s3, OUTPUT);
	pinMode(_out, INPUT);
}

int ColorDetector::detectRed() 
{
	// Setting frequency-scaling to 100%
	digitalWrite(_s0, HIGH);
	digitalWrite(_s1, HIGH);
	// Setting Red filtered photodiodes to be read
	digitalWrite(_s2, LOW);
	digitalWrite(_s3, LOW);
	// Reading the output frequency
	_led_red_frequency = pulseIn(_out, LOW);
	// Remap
	_led_red_value = map(_led_red_frequency, 25, 75, 255, 0);
	return _led_red_value;
	// return _led_red_frequency;
}

int ColorDetector::detectGreen() 
{
	// Setting frequency-scaling to 100%
	digitalWrite(_s0, HIGH);
	digitalWrite(_s1, HIGH);
	// Setting Green filtered photodiodes to be read
	digitalWrite(_s2, HIGH);
	digitalWrite(_s3, HIGH);
	// Reading the output frequency
	_led_green_frequency = pulseIn(_out, LOW);
	// Remap
	_led_green_value = map(_led_green_frequency, 45, 90, 255, 0);
	return _led_green_value;
	// return _led_green_frequency;
}

int ColorDetector::detectBlue() 
{
	// Setting frequency-scaling to 100%
	digitalWrite(_s0, HIGH);
	digitalWrite(_s1, HIGH);
	// Setting Blue filtered photodiodes to be read
	digitalWrite(_s2, LOW);
	digitalWrite(_s3, HIGH);
	// Reading the output frequency
	_led_blue_frequency = pulseIn(_out, LOW);
	// Remap
	_led_blue_value = map(_led_blue_frequency, 30, 85, 255, 0);
	return _led_blue_value;
	// return _led_blue_frequency;
}
