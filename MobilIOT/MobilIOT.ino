
#include <Arduino.h>
#include <TM1637Display.h>
#include <EEPROM.h>

#include "pitches.h"

#include "Capteur.hpp"
#include "CapteurLux.hpp"
#include "CapteurDist.hpp"
#include "CapteurSon.hpp"
#include "CapteurTemp.hpp"

#include "Bluetooth.hpp"
#include "Batterie.hpp"

#include "pins_3d.hpp"

#define NB_MAX_VALUES 300

#define DELAY_AFFICHAGE 50
#define DELAY_REACTION 10

#define BATTERIE_COUNT_UPDATE 100

unsigned int values[NB_MAX_VALUES];

const int NB_CAPTEURS = 3;
Capteur* capteurs[NB_CAPTEURS] = {
  // new CapteurTemp(values, NB_MAX_VALUES, PIN_SWITCH_TO_LUX, PIN_LED_LUX, A4), //TEMP
  new CapteurDist(values, NB_MAX_VALUES, PIN_SWITCH_TO_DIST, PIN_LED_DIST, PIN_RX_TFMINI, PIN_TX_TFMINI, OFFSET_DISTANCE), //DIST
  new CapteurLux(values, NB_MAX_VALUES, PIN_SWITCH_TO_LUX, PIN_LED_LUX), //LUX
  new CapteurSon(values, NB_MAX_VALUES, PIN_SWITCH_TO_SONO, PIN_LED_SONO, PIN_SONO)}; //SONO


Bluetooth bluetooth(PIN_RX_BLUETOOTH, PIN_TX_BLUETOOTH);

Batterie * battery(new Pile9V_6LR61(PIN_BATTERIE));

/* Affichage */
TM1637Display display(PIN_7SEG_CLK, PIN_7SEG_DIO);

const uint8_t no_values[] = {
  SEG_G,
  SEG_G,
  SEG_G,
};
const uint8_t empty[] = {0};

long prev_affichage(0);

/* L'état de l'objet */
struct EtatMobilIOT {
  bool measuring;
  Capteur* capteur;
  float value;
};

EtatMobilIOT etat = {
  false,
  capteurs[0],
  0
};

VEML7700 als;

void setup()
{

  for(int i = 0; i < NB_CAPTEURS; i++){
    pinMode(capteurs[i]->getPinLed(), OUTPUT);
    pinMode(capteurs[i]->getPinSwitch(), INPUT);
  }
  
  Serial.begin(9600);
  Serial.println("coucou");
  
  als.begin();

  bluetooth.init();

  display.setBrightness(0x0f);

  pinMode(PIN_TAKE_MEASUREMENT, INPUT);
  pinMode(PIN_LASER, OUTPUT);

  pinMode(PIN_BATTERIE, INPUT);
  pinMode(PIN_HP, OUTPUT);
}

int count(0);
void loop()
{
  ///=====================
  // Test if we are measuring

  long measure_start(millis());

  if(digitalRead(PIN_TAKE_MEASUREMENT) == HIGH){
    //Alert the captor if needed
    if(etat.measuring == false)
      etat.capteur->init();
    etat.measuring = true;
  }
  else if(etat.measuring){
    //send the datas
    int nb_values = etat.capteur->getNbValues();

    bluetooth.send_values(values, nb_values, etat.capteur->getSendableUnity());

    tone(PIN_HP, NOTE_E6, 1000/16);
    delay(1000/16*1.3);
    noTone(PIN_HP);
    tone(PIN_HP, NOTE_G6, 1000/16);
    delay(1000/16*1.3);
    noTone(PIN_HP);
    tone(PIN_HP, NOTE_C7, 1000/4);
    delay(1000/4*1.3);
    noTone(PIN_HP);

    etat.measuring = false;
  }

  ///=====================
  // Change mode
  for(int i = 0; i<NB_CAPTEURS; i++){
    if(digitalRead(capteurs[i]->getPinSwitch()) == HIGH){
      etat.capteur = capteurs[i];
      etat.value = 0;
    }
  }

  for(int i = 0; i<NB_CAPTEURS; i++)
    digitalWrite(capteurs[i]->getPinLed(), etat.capteur == capteurs[i] ? HIGH : LOW);

  digitalWrite(PIN_LASER, etat.measuring && etat.capteur->getPinLed() == PIN_LED_DIST ? HIGH : LOW);

  ///=====================
  // Update the value if needed
  if(etat.measuring)
    etat.value = etat.capteur->getValue() / 10;

  ///=====================
  // Display

  //Display the unit
  display.setSegments(etat.capteur->getUnity(), 1, 3);

  //Display the value
  if(millis() - prev_affichage > DELAY_AFFICHAGE){
    int toDisplay = min(999, max(0, etat.value));
    for(int i = 0; i<3; i++){
      if(toDisplay)
        display.showNumberDec(toDisplay%10, true, 1, 2-i);
      else if(etat.value)
        display.setSegments(empty, 1, 2-i);
      toDisplay /= 10;
    }
    prev_affichage = millis();
  }

  if(etat.value == 0)
    display.setSegments(no_values, 3, 0);

  if(!count)
    bluetooth.send_values(battery->getPercentage(), 1, "battery");
  count = (count+1) % BATTERIE_COUNT_UPDATE;

  ///=====================
  // Wait some time
  if(etat.measuring)
    delay(max(1, DELAY_REACTION - ((long)millis() - measure_start)));
}
