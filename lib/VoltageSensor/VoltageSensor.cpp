#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(int PIN_Voltmeter, float voltage_calibration, float phase_shift) 
{
	energy_monitor.voltage(PIN_Voltmeter, voltage_calibration, phase_shift);
}

float VoltageSensor::measureVoltage(int number_of_measurements, int number_of_values_selected) 
{
	float measurements[number_of_measurements];
	int measurement_count = 0;
	for (int index = 0; index < number_of_measurements; index++) 
	{
		energy_monitor.calcVI(10, 10);		// 5 20
		float voltage_value = energy_monitor.Vrms;
		measurements[index] = voltage_value;
		measurement_count++;
  	}
	
	float measurement_sum = 0.0f;
	for (int index = measurement_count - number_of_values_selected; index < measurement_count; index++) 
	{
		measurement_sum += measurements[index];
  	}
	
	float measurement_average = (measurement_sum / float(number_of_values_selected)) - float(25.0);
	return measurement_average;
}
