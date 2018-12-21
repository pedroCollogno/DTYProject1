#ifndef CAPTEUR_LUX_HPP
#define CAPTEUR_LUX_HPP

#include "Capteur.hpp"

#include <Wire.h>
#include <VEML7700.h>

#define MOYENNE_SUR_LUX 3

class CapteurLux : public Capteur{
	public:
    CapteurLux(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led);

		//Called when start pressing play
		virtual void init();

		//Return the current value mesured
		virtual float getValue();

	protected:
		VEML7700 _als;

    bool _setuped;
};

#endif
