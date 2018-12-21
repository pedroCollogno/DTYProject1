#ifndef CAPTEUR_SON_HPP
#define CAPTEUR_SON_HPP

#include "Capteur.hpp"
#include <Arduino.h>

#define MOYENNE_SUR_SON 50
#define MESURE_MIN_MAX 50

// Valeurs de calibrage du potentiomètre
#define ADC_SOUND_REF 25 // valeur d'écart max-min affichée sur l'Arduino
#define DB_SOUND_REF 70 // valeur d'un dBmètre "officiel" (celui de mon iPhone) 

class CapteurSon : public Capteur{
  public:
    CapteurSon(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led, int pin);

    //Called when start pressing play
    virtual void init();

    //Return the current value mesured
    virtual float getValue();

  protected:
    int _pin;
};

#endif
