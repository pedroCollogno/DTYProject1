#include "CapteurDist.hpp"

CapteurDist::CapteurDist(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led, int pin_rx, int pin_tx, int offset_mm):
    Capteur(values, NB_MAX_VALUES, pin_switch, pin_led),
    _serial(pin_rx, pin_tx),
    _setuped(false),
    _offset_mm(offset_mm)
{
    _unity[0] = SEG_G | SEG_E | SEG_D;
    _sendable_unity = "cm";
}

void CapteurDist::init(){
    _values[0] = 0;
    _nb_values = 1;

    //Setup serial connexion
    if(!_setuped){
      _setuped = true;
      _serial.begin(TFMINI_BAUDRATE);
      _tfmini.begin(&_serial);
    }
}

float CapteurDist::getValue(){
    float dist(_tfmini.getDistance());

    _values[0] = dist*10 + _offset_mm;

    return _values[0];
}
