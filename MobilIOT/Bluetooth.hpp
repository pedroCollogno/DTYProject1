#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include <Arduino.h>
#include <SoftwareSerial.h>

#define BT_SERIAL_BAUDRATE  9600

class Bluetooth{
    public:
        Bluetooth(int pin_rx, int pin_tx);
        void init();
        void send_values(unsigned int values[], int len, String unit);
    private:
        SoftwareSerial _serialBt;
};

#endif