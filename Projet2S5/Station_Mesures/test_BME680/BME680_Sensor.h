// Fichier BME680_Sensor.h


#include <Arduino.h>
#include <Wire.h>
#include "bsec.h"
// Définition de constantes symboliques
                               // pression moyenne (toutes les heures, soit 3600s)
 

// Fonctions prototypes

void checkIaqSensorStatus(Bsec verif);
void errLeds();
void beginBME680(); 
void affichage_Valeur_BME680(Bsec * val);
void updateValeur();
Bsec * getBME680();
