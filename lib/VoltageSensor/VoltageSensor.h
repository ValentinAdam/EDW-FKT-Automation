#ifndef VoltageSensor_H
#define VoltageSensor_H

#include <Arduino.h>
#include "EmonLib.h"

class VoltageSensor 
{
	public:
		VoltageSensor(int PIN_Voltmeter, float voltage_calibration, float phase_shift);
		float measureVoltage(int number_of_measurements, int number_of_values_selected);
		
	private:
  		EnergyMonitor energy_monitor;
};

#endif
