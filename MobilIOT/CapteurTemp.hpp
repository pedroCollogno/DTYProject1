#ifndef CAPTEUR_TEMP_HPP
#define CAPTEUR_TEMP_HPP

#include "Capteur.hpp"

#include <OneWire.h>
#include <DallasTemperature.h>

class CapteurTemp : public Capteur{
    public:
    CapteurTemp(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led, int pin);

        //Called when start pressing play
        virtual void init();

        //Return the current value mesured
        virtual float getValue();

    protected:
        OneWire _oneWire;

        DallasTemperature _sensor;

        bool _setuped;
};

#endif
