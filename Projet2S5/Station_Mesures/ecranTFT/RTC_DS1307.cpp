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


char * EteHiv;
char * EteHivPres;

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
    char * jour[] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"};
    char * mois[]= {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};

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

char * IndicateurEteHiv(Horloge H)
{
  if(H.D.mois >= 3 && H.D.jour_mois >= 28 && H.H.heure >= 2)
    {
      EteHiv = "ete";
    }
    else
    {
      EteHiv = "hiver";
    }

    return EteHiv;
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

uint8_t jour_semaine(uint8_t jour, uint8_t mois, uint8_t annee)
{
  uint8_t c = (14-mois)/12;
  uint8_t a = annee-c;
  uint8_t m = mois + 12*c-2;
  uint8_t j = ( jour + a + a/4 - a/100 + a/400 + (31*m)/12 ) % 7;

  return j;
}

int Bissextile(Horloge H)
{
  int A = H.D.annee + 2000;
  if(A%4 == 0 && A%100 != 100)
  {
    return 1;
  }
  else if(A%400 == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

Horloge Correction_Heure_Date(Horloge H, pays pays_UTC, Horloge E)
{
  if(H.D.mois == 3 && H.D.jour_mois == 28 && H.H.heure == 2)
  {
    E.H.heure = 1;
  }
  else if(H.D.mois == 10 && H.D.jour_mois == 31 && H.H.heure == 3)
  {
    E.H.heure = -1;
  }
  
  if((H.H.heure + pays_UTC.corr.heure + ((H.H.minute + pays_UTC.corr.minute)/60) + E.H.heure) >= 24)
  {
    if(H.D.mois == 1 || H.D.mois == 3 || H.D.mois == 5 || H.D.mois == 7 || H.D.mois == 8 || H.D.mois == 10 || H.D.mois == 12)
    {
      if(H.D.jour_mois == 31)
      {
        H.D.jour_mois = 1;
        if(H.D.mois == 12)
        {
          H.D.mois = 01;
          ++H.D.annee;
        }
        else
        {
          ++H.D.mois;
        }
      }
      else
      {
        ++H.D.jour_mois;
      }
    }
    else if(H.D.mois == 02)
    {
      if(Bissextile(H))
      {
        if(H.D.jour_mois == 29)
        {
          H.D.jour_mois = 1;
          if(H.D.mois == 12)
          {
            H.D.mois = 01;
            ++H.D.annee;
          }
          else
          {
            ++H.D.mois;
          }
        }
      }
      else
      {
        if(H.D.jour_mois == 28)
        {
          H.D.jour_mois = 1;
          if(H.D.mois == 12)
          {
            H.D.mois = 01;
            ++H.D.annee;
          }
          else
          {
            ++H.D.mois;
          }
        }
      }
    }
    else
    {
      if(H.D.jour_mois == 30)
      {
        H.D.jour_mois = 1;
        if(H.D.mois == 12)
        {
          H.D.mois = 01;
          ++H.D.annee;
        }
        else
        {
          ++H.D.mois;
        }
      }
      else
      {
        ++H.D.jour_mois;
      }
    }
  }
  
  H.H.heure = (H.H.heure + pays_UTC.corr.heure + ((H.H.minute + pays_UTC.corr.minute)/60) + E.H.heure)%24;
  H.H.minute = (H.H.minute + pays_UTC.corr.minute + E.H.minute)%60;
  
  return H;
}
