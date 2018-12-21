
#include "Batterie.hpp"

Batterie::Batterie(int pin):
    _pin(pin)
{}

Pile9V_6LR61::Pile9V_6LR61(int pin):
    Batterie(pin)
{}

unsigned int* Batterie::getPercentage(){
    // Le pont diviseur de tension nous permet de lire une tension 2 fois moins grande que celle de la batterie
    float voltage = 2. * (5. * (float)analogRead(_pin) / 1023.);
    _value[0] = 0;
    int N = 4;
    for(int i=0; i<N; i++)
        _value[0] += min(100, max(0, convertVoltageToPercentage(voltage))) / N;
    return _value;
}

// https://img1.emos.eu/files/product/attachment/1320511000_61-B7951.pdf
int Pile9V_6LR61::convertVoltageToPercentage(float voltage){
    return 12.501f*(float)(voltage*voltage*voltage) - 343.94f*(float)(voltage*voltage) + 3156.3f*(float)voltage - 9563.3f;
}
