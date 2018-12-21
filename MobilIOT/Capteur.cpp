#include "Capteur.hpp"

Capteur::Capteur(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led) :
  _pin_led(pin_led),
  _pin_switch(pin_switch),
  _values(values),
  _NB_MAX_VALUES(NB_MAX_VALUES)
{
	_unity[0] = SEG_G | SEG_E | SEG_D;
}

void Capteur::init(){
	_values[0] = 345;
    _nb_values = 1;
	_fake_value = 100;
}

uint8_t* Capteur::getUnity(){
  return _unity;
}

String Capteur::getSendableUnity(){
  return _sendable_unity;
}

float Capteur::getValue(){
	return ++_fake_value;
}

int Capteur::getNbValues(){
	return _nb_values;
}

int Capteur::getPinLed(){
  return _pin_led;
}

int Capteur::getPinSwitch(){
  return _pin_switch;
}
