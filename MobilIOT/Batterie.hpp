
#ifndef BATTERIE_HPP
#define BATTERIE_HPP

#include <Arduino.h>

class Batterie {
    public :
        Batterie(int pin);

        unsigned int* getPercentage();

        virtual int convertVoltageToPercentage(float voltage) = 0;

    protected:
        int _pin;

        unsigned int _value[1];
};

class Pile9V_6LR61 : public Batterie {
    public :
        Pile9V_6LR61(int pin);

        virtual int convertVoltageToPercentage(float voltage);
};

#endif
