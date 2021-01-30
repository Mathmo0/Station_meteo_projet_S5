#include "BME680_Sensor.h"
#include <Arduino.h>


//Bsec Test;
int k =0;

void setup() {
  // put your setup code here, to run once:
  Bsec * verif;
  Serial.begin(9600);
  Serial.println("TestSD");
  
  beginBME680();
  //updateValeur();
  
  Serial.println("TestSF");
}

void loop() {
  // put your main code here, to run repeatedly:
  Bsec * verif;
  Serial.println(k);
  if(k%3 == 0)
  {
    Serial.println("Dans la boucle________________");
    verif = getBME680();
  }
  
  affichage_Valeur_BME680(verif); //Serial.println("TestLD");
  k++;
  
   //Bsec Test;
   //unsigned long time_trigger = millis();
   //updateValeur(Test);
   //affichage_Valeur_BME680(Test);
   Serial.println("TestLF");
   delay(1000);
}
