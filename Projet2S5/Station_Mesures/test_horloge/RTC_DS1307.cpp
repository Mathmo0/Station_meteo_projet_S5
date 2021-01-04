// Fichier RTC_DS1307.cpp
// Fonctions de gestion du circuit d'horloge RTC DS1307
// Affichage de la date et de l'heure sur terminal série : 
// Arret du circuit RTC : 
// Initialisation des paramètres de l'horloge : 
// Acquisition de la date et de l'heure : 
// 2 fonctions additionnelles :
//  - byte decToBcd(byte val)
//  - byte bcdToDec(byte val)


#include <Arduino.h>
#include <Wire.h>
#include "RTC_DS1307.h"

void setDateDs1307(Horloge H)
{
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write(decToBcd(H.H.seconde));// 0 to bit 7 starts the clock
    Wire.write(decToBcd(H.H.minute));
    Wire.write(decToBcd(H.H.heure));  // If you want 12 hour am/pm you need to set bit 6
    Wire.write(decToBcd(H.D.jour_semaine));
    Wire.write(decToBcd(H.D.jour_mois));
    Wire.write(decToBcd(H.D.mois));
    Wire.write(decToBcd(H.D.annee));
    Wire.endTransmission();
}

Horloge getDateDs1307()
{
    Horloge getDate;
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission(DS1307_I2C_ADDRESS);
    Wire.requestFrom(DS1307_I2C_ADDRESS,7);
    getDate.H.seconde       = bcdToDec(Wire.read() & 0x7f);
    getDate.H.minute        = bcdToDec(Wire.read());
    getDate.H.heure         = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
    getDate.D.jour_semaine  = bcdToDec(Wire.read());
    getDate.D.jour_mois     = bcdToDec(Wire.read());
    getDate.D.mois          = bcdToDec(Wire.read());
    getDate.D.annee         = bcdToDec(Wire.read());

    return getDate;
}

void Affiche_date_heure(Horloge H)
{
    char* jour[] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"};
    char* mois[]= {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Août","Septembre","Octobre","Novembre","Décembre"};

    Serial.print(jour[H.D.jour_semaine-1]);
    Serial.print("    ");
    Serial.print(H.D.jour_mois);
    Serial.print("    ");
    Serial.print(mois[H.D.mois-1]);
    Serial.print("    ");
    Serial.print(H.D.annee + 2000);
    Serial.print("    ");

    Serial.print(H.H.heure);
    Serial.print(":");
    Serial.print(H.H.minute);
    Serial.print(":");
    Serial.print(H.H.seconde);
    Serial.println("    ");
}

uint8_t decToBcd(uint8_t val)
{
    return ((val / 10 * 16) + (val % 10));
}

uint8_t bcdToDec(uint8_t val)
{
    return ((val / 16 * 10) + (val % 16));
}

void beginDs1307()
{
  Wire.begin();
}
