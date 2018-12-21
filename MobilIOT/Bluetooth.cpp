
#include "Bluetooth.hpp"

Bluetooth::Bluetooth(int pin_rx, int pin_tx):
    _serialBt(pin_tx, pin_rx)
{}

void Bluetooth::init(){
    _serialBt.begin(BT_SERIAL_BAUDRATE);
}

// Function to send an array of ints over _serialBt in a JSON-like char list.
//        values[]    -->     The array of the values   (Caution: 0 <= int <= 2*32767)
//        len         -->     The length of the array
//        unit        -->     The unit of the values    (Caution: length(unit) <= 3 )
void Bluetooth::send_values( unsigned int values[], int len, String unit ) {
    char unitChar[10];
    char valueChar[10];
    String str;

    _serialBt.write( "{ \"unit\": \"" );          // Send: { "unit": "
    unit.toCharArray( unitChar, 10 );             // Convert unit from String to char
    _serialBt.write( unitChar );                  // Send: unit
    _serialBt.write( "\", \"values\": [" );       // Send: ", "values": [
    for (int i = 0; i < len-1; i++) {              //
        str = String( values[i] );                 //

        str.toCharArray( valueChar, 10 );        // Convert value from int to char
        _serialBt.write( valueChar );             // Send: value
        _serialBt.write(", ");                    // Send: ,
    }
    str = String( values[ len-1 ] );                 //
    str.toCharArray( valueChar, 10 );            //
    _serialBt.write( valueChar );                 // Send: last value
    _serialBt.write( " ] }" );                    // Send  ] }
    _serialBt.write( "\n" );                      // End of the transmission
}
