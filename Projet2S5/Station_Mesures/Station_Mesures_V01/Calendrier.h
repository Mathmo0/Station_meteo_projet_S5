// Fichier Calendrier.h

#ifndef __Calendrier__
#define __Calendrier__

#include <Arduino.h>
#include "RTC_DS1307.h"

// Définition de constantes symboliques

typedef struct corrUTC
{
  int minute;
  int heure;
}corr;

typedef struct pays_UTC
{
  char * pays;
  char * ville;
  corr corr;
}pays;

// Fonctions prototypes

uint8_t jour_semaine(uint8_t jour, uint8_t mois, uint8_t annee);
Horloge Correction_Heure_Date(Horloge H, pays pays_UTC, int E);
int Bissextile(Horloge H);
int IndicateurEteHiv(Horloge H);
pays fuseau_horaire_de_ref(int i);

#endif
