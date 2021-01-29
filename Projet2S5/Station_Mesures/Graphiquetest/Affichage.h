// Fichier Affichage.h
// Routines d'affichage :
//  Sur le terminal série

#include <Arduino.h>
#include "RTC_DS1307.h"
#include "GPS.h"
#include "BME680_Sensor.h"
#include "Calendrier.h"
#include "TFT_Affichage.h"

// Définition de constantes symboliques

// Fonctions prototypes pour terminal série

void graphiqueMoyennePression();
