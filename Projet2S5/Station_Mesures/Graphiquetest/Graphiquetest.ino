#include <Arduino.h>

//#include "TFT_Affichage.h"
#include "Calendrier.h"
#include"Affichage.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

extern float SommePression;
extern int nbValeur;

void setup() {
  
  Serial.begin(9600);
  beginBME680();

  Serial.begin(9600);
  /*Partie initialisation Horloge :*/
  beginDs1307();
     /*On initialise l'horlge aux 1 Janvier 2010 00:00:00 */
  Horloge H;
  H.H.seconde = 50;
  H.H.minute = 59;
  H.H.heure = 0;
  
  H.D.jour_mois = 1;
  H.D.mois =  1;
  H.D.annee = 10;
  H.D.jour_semaine = jour_semaine( H.D.jour_mois,H.D.mois,H.D.annee);
  setDateDs1307(H);
  
  TFT_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Bsec * verif;
  Horloge H;
  H = getDateDs1307();
  Affiche_date_heure(H);
  //TFT_Affiche_Heure(H,H);
  verif = getBME680();
  float recupDelta = 678;
  SommePression = SommePression+verif->pressure;
  nbValeur++;
  affichage_Valeur_BME680(verif);
  graphiqueMoyennePression();
  MoyennePression(H);
  recupDelta = GetDeltaPresssion();
  Serial.print("Delta = ");Serial.println(recupDelta);
  delay(1000);
}
