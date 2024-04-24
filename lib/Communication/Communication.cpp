#include "Communication.h"
#include <driver/dac.h>
#include <driver/adc.h>
#include <Arduino.h>

Communication::Communication()
{
    dac_output_enable(DAC_CHANNEL_1);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
}

void Communication::dac_tx_sync()
{
    dac_output_voltage(DAC_CHANNEL_1, 50);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);
}

void Communication::dac_tx_potCalib()
{
    dac_output_voltage(DAC_CHANNEL_1, 100);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_potCentered()
{
    dac_output_voltage(DAC_CHANNEL_1, 150);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_potCalibNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 200);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_checkRedLED()
{
    dac_output_voltage(DAC_CHANNEL_1, 250);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_redLEDOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 300);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_redLEDNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 350);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_checkMinVoltage()
{
    dac_output_voltage(DAC_CHANNEL_1, 400);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_minVoltageOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 450);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_minVoltageNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 500);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_checkMaxVoltage()
{
    dac_output_voltage(DAC_CHANNEL_1, 550);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_maxVoltageOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 600);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_maxVoltageNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 650);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_checkYellowLED()
{
    dac_output_voltage(DAC_CHANNEL_1, 700);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_yellowLEDOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 750);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_yellowLEDNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 800);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_checkSincromotor()
{
    dac_output_voltage(DAC_CHANNEL_1, 850);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_sincromotorOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 900);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

void Communication::dac_tx_sincromotorNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 950);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
    delay(500);    
}

int Communication::adc_rx()
{
    int adcValue = adc1_get_raw(ADC1_CHANNEL_6);
    return adcValue;
}