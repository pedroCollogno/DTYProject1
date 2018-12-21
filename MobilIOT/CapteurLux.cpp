#include "CapteurLux.hpp"

CapteurLux::CapteurLux(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led):
	Capteur(values, NB_MAX_VALUES, pin_switch, pin_led),
  _setuped(false)
{
	_unity[0] = SEG_F | SEG_E | SEG_D;
	_sendable_unity = "lux";
}

void CapteurLux::init(){
	_nb_values = 0;
	
  if(!_setuped){
    _setuped = true;
    _als.begin();
  }
}

float CapteurLux::getValue(){
  float lux;
	if(_nb_values < _NB_MAX_VALUES){
		_als.getALSLux(lux);
		_values[_nb_values++] = lux*10;
	}

	float res(0), count(0);

	for(int i = max(0, _nb_values - MOYENNE_SUR_LUX); i < _nb_values; i++){
		res += _values[i];
		count ++;
	}

	return res / count;
}
