// Fichier BME680_Sensor.h

#ifndef __BME680__
#define __BME680__


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
Bsec * getBME680();

#endif
