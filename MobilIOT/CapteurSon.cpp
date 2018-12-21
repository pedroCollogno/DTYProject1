#include "CapteurSon.hpp"

CapteurSon::CapteurSon(unsigned int * values, int NB_MAX_VALUES, int pin_switch, int pin_led, int pin):
  Capteur(values, NB_MAX_VALUES, pin_switch, pin_led),
  _pin(pin)
{
  _unity[0] = SEG_B | SEG_C | SEG_D | SEG_E | SEG_G;
}

void CapteurSon::init(){
  _nb_values = 0;
  _sendable_unity = "dB";
}

float CapteurSon::getValue(){
  if(_nb_values < _NB_MAX_VALUES){
    long sum = 0;
    for(int iter = 0; iter < 10; iter++){
      int maxi = 0;
      int mini = 1023;
      for(int i = 0; i < MESURE_MIN_MAX; i++){ //Recherche de l'écart entre minimum et maximum d'amplitude sur un nombre MESURE_MIN_MAX de mesures
       int val = analogRead(_pin);
         if(val > maxi){
          maxi = val;
        }
        if(val < mini){
          mini = val;
        }
     }
     int ecart = maxi - mini;
     sum += ecart;
    }
    float moyenne = (float)sum / 10.;

    _values[_nb_values++] = (int)10 * ( 10 * log(moyenne / (double)ADC_SOUND_REF) + (double)DB_SOUND_REF );
  }

  float res(0), count(0);



  for(int i = max(0, _nb_values - MOYENNE_SUR_SON); i < _nb_values; i++){
    res += _values[i];
    count ++;
  }
  float moy = res/count;
  return moy;
}
