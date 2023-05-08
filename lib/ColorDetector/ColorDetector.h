#ifndef ColorDetector_h
#define ColorDetector_h

#include <Arduino.h>

class ColorDetector 
{
	public:
		ColorDetector(int s0, int s1, int s2, int s3, int out);
		void initialize();
		int detectRed();
		int detectGreen();
		int detectBlue();

  	private:
		int _s0;
		int _s1;
		int _s2;
		int _s3;
		int _out;
		int _led_red_frequency;
		int _led_green_frequency;
		int _led_blue_frequency;
		int _led_red_value;
		int _led_green_value;
		int _led_blue_value;
};

#endif
