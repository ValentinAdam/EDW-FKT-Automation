#ifndef Communication_H
#define Communication_H

#include <Arduino.h>

class Communication
{
    public:
        void dac_tx_sync();
        void dac_tx_potCalib();
        void dac_tx_potCentered();
        void dac_tx_potCalibNOK();
        void dac_tx_checkRedLED();
        void dac_tx_redLEDOK();
        void dac_tx_redLEDNOK();
        void dac_tx_checkMinVoltage();
        void dac_tx_minVoltageOK();
        void dac_tx_minVoltageNOK();
        void dac_tx_checkMaxVoltage();
        void dac_tx_maxVoltageOK();
        void dac_tx_maxVoltageNOK();
        void dac_tx_checkYellowLED();
        void dac_tx_yellowLEDOK();
        void dac_tx_yellowLEDNOK();
        void dac_tx_checkSincromotor();
        void dac_tx_sincromotorOK();
        void dac_tx_sincromotorNOK();
    private:
};
#endif;