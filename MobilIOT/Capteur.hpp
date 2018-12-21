#ifndef CAPTEUR_HPP
#define CAPTEUR_HPP

#include <Arduino.h>
#include <TM1637Display.h>

class Capteur{
    public:

        Capteur(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led);

        //Called when start pressing play
        virtual void init();

        //See Capteur.cpp
        uint8_t* getUnity();
        String getSendableUnity();

        //Return the current value mesured * 10
        virtual float getValue();

        //Return all the values to be sent to be saved, from the init moment
        int getNbValues();

        // UX
        int getPinLed();

        int getPinSwitch();

    protected:
        //1-array that implement the symbol to be displayed on the 7 segments
        uint8_t _unity[1];

        unsigned int * _values;
        int _NB_MAX_VALUES, _nb_values;

        float _fake_value;

        int _pin_led, _pin_switch;

        String _sendable_unity;
};

#endif
