#ifndef CAPTEUR_DIST_HPP
#define CAPTEUR_DIST_HPP

#include "Capteur.hpp"

#include <SoftwareSerial.h>
#include "TFMini.h"

class CapteurDist : public Capteur{
    public:
    CapteurDist(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led, int pin_rx, int pin_tx, int offset_mm);

        //Called when start pressing play
        virtual void init();

        //Return the current value mesured
        virtual float getValue();

    protected:
        SoftwareSerial _serial;

        TFMini _tfmini;

        int _offset_mm;

        bool _setuped;
};

#endif
