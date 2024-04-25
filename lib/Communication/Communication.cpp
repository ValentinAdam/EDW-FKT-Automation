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
    dac_output_voltage(DAC_CHANNEL_1, 5);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_potCalib()
{
    dac_output_voltage(DAC_CHANNEL_1, 10);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_potCentered()
{
    dac_output_voltage(DAC_CHANNEL_1, 15);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_potCalibNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 20);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_checkRedLED()
{
    dac_output_voltage(DAC_CHANNEL_1, 25);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_redLEDOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 30);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_redLEDNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 35);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_checkMinVoltage()
{
    dac_output_voltage(DAC_CHANNEL_1, 40);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_minVoltageOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 45);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_minVoltageNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 50);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_checkMaxVoltage()
{
    dac_output_voltage(DAC_CHANNEL_1, 55);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_maxVoltageOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 60);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_maxVoltageNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 65);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_checkYellowLED()
{
    dac_output_voltage(DAC_CHANNEL_1, 70);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_yellowLEDOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 75);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_yellowLEDNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 80);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_checkSincromotor()
{
    dac_output_voltage(DAC_CHANNEL_1, 85);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_sincromotorOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 90);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

void Communication::dac_tx_sincromotorNOK()
{
    dac_output_voltage(DAC_CHANNEL_1, 95);
    delay(500);
    dac_output_voltage(DAC_CHANNEL_1, 0);
}

int Communication::adc_rx()
{
    int adcValue = adc1_get_raw(ADC1_CHANNEL_6);
    int convert = adcValue / 15;
    int packet = round(convert);
    return packet;
}