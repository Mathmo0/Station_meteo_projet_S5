#include "BME680_Sensor.h"
#include <Arduino.h>


//Bsec Test;

void setup() {
  // put your setup code here, to run once:
  Bsec verif;
  Serial.begin(9600);
  Serial.println("TestSD");
  
  beginBME680();
  updateValeur();
  
  Serial.println("TestSF");
}

void loop() {
  // put your main code here, to run repeatedly:
  Bsec verif;
  verif = getBME680();
  affichage_Valeur_BME680(verif); //Serial.println("TestLD");
   //Bsec Test;
   //unsigned long time_trigger = millis();
   //updateValeur(Test);
   //affichage_Valeur_BME680(Test);
   Serial.println("TestLF");
   delay(1000);
}
