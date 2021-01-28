// Fichier RTC_DS1307.h
// Contient les définitions de types de données associées aux fonctions
//  de manipulation du circuit d'horloge RTC DS1307

//#include "C:\Users\maxim\Documents\station-meteo-projet-s5\Projet2S5\Station_Mesures\TestGPS\GPS.h"

#ifndef __Holorge__
#define __Holorge__

#include <Arduino.h>


// Définition de type de données pour gestion de la date

typedef struct Heure
{
    uint8_t seconde;
    uint8_t minute;
    uint8_t heure;
} Heure ;

typedef struct Date
{
    uint8_t jour_semaine;
    uint8_t jour_mois;
    uint8_t mois;
    uint8_t annee;
} Date ;

typedef struct HorlogeRTC
{
    Heure H;
    Date D;
}Horloge;

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



// Définition de constantes symboliques

#define DS1307_I2C_ADDRESS 0x68


// Fonctions prototypes

void setDateDs1307(Horloge H);
Horloge getDateDs1307();
void Affiche_date_heure(Horloge H);
uint8_t decToBcd(uint8_t val);
uint8_t bcdToDec(uint8_t val);
void beginDs1307();
uint8_t jour_semaine(uint8_t jour, uint8_t mois, uint8_t annee);
Horloge Correction_Heure_Date(Horloge H, pays pays_UTC, int E);
int Bissextile(Horloge H);
char * IndicateurEteHiv(Horloge H);
pays fuseau_horaire_de_ref(int i);


#endif
