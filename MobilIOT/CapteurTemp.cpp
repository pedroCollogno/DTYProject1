#include "CapteurTemp.hpp"

CapteurTemp::CapteurTemp(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led, int pin):
    Capteur(values, NB_MAX_VALUES, pin_switch, pin_led),
    _oneWire(pin),
    _sensor(&_oneWire),
    _setuped(false)
{
    _unity[0] = SEG_A | SEG_F | SEG_E | SEG_D;
    _sendable_unity = "°C";
}

void CapteurTemp::init(){
    _values[0] = 0;
    _nb_values = 1;

    //Setup serial connexion
    if(!_setuped){
      _setuped = true;
    }
}

float CapteurTemp::getValue(){
    _sensor.requestTemperatures();
    float temp(_sensor.getTempCByIndex(0));

    _values[0] = temp*10;

    return _values[0];
}
