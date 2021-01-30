// Fichier TFT_Affichage.cpp
// Routines de gestion d'affichage sur écran TFT Adafruit 2050

#include <stdlib.h>
#include <stdio.h>
#include "TFT_Affichage.h"

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void TFT_setup()
{
  Serial.begin(9600);  
  tft.reset();
  //tft.fillScreen(WHITE);
  

  uint16_t identifier = tft.readID();

  tft.begin(identifier);
tft.fillScreen(BLACK);
  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.println(F("Done!"));
  
}

void TFT_Affichage_Date(Horloge H, Horloge P)
{
  if(H.D.jour_mois != P.D.jour_mois || H.D.mois != P.D.mois || H.D.annee != P.D.annee)
  {
    tft.setTextSize(2);
    char * jour[] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"};
    char * mois[]= {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};
    tft.setCursor(0,100);
    tft.fillRect(0,100,319,20,BLACK);
    
    
    tft.setTextSize(2);
    tft.print(jour[H.D.jour_semaine-1]);
    tft.print(" ");
    tft.print(H.D.jour_mois);
    tft.print(" ");
    tft.print(mois[H.D.mois-1]);
    tft.print(" ");
    tft.print(H.D.annee + 2000);
    //tft.print("    ");

    /*tft.print(H.H.heure);
    tft.print(":");
    tft.print(H.H.minute);
    tft.print(":");
    tft.print(H.H.seconde);
    tft.println("    ");*/
    //delay(1000);
  }
}

void TFT_Affiche_Heure(Horloge H, Horloge P)
{
  if(H.H.seconde != P.H.seconde)
  {
    tft.setTextSize(2);
    //tft.setTextColor(WHITE);
    tft.setCursor(0,150);
    //tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.fillRect(0,150,90,20,BLACK);
    tft.print(H.H.heure);
    tft.print(":");
    tft.print(H.H.minute);
    tft.print(":");
    tft.print(H.H.seconde);
    //tft.println("    ");
    
    //delay(1000);
  }
}

void TFT_Affiche_EteHiv(char * EteHiv, char * EteHivPres)
{
  if(strcmp(EteHiv, EteHivPres))
  {
    tft.setTextSize(2);
    tft.setCursor(90, 150);
    tft.fillRect(90,150,150,20,BLACK);
    tft.print("heure d'");
    tft.print(EteHiv);
  }
}

void TFT_Affiche_ville_ref_fuseau_horaire(pays Pays, pays PaysPres)
{
  if(strcmp(Pays.ville, PaysPres.ville))
  {
    tft.setTextSize(2);
    tft.setCursor(0, 200);
    tft.fillRect(0,200,150,20,BLACK);
    tft.print(Pays.ville);
  }
}

void TFT_Affiche_Etat_Synchro(NMEA Verif)
{
  tft.setTextSize(2);
  if(Test_Synchro_GPS(Verif))
  {
    tft.setCursor(0, 250);
    tft.fillRect(0,250,150,20,BLACK);
    tft.print("GPS est synchronise");
  }
  else
  {
    tft.setCursor(0, 250);
    tft.fillRect(0,250,300,20,BLACK);
    tft.print("GPS n'est pas synchronise");
  }
}

void remplacer_valeur(char * V, char * VP)
{
  int len = max(strlen(V), strlen(VP));
  int i = 0;
  Serial.println(V);
  Serial.println(VP);
  while(i <= len && V[i] == VP[i])
  {
    ++i;
  }
  tft.setCursor(i*6 + 150, 7);
  tft.fillRect(i*6 + 150,7,150,7,BLACK);
  for(i; i<strlen(V); ++i)
  {
    tft.print(V[i]);
  }
}

void TFT_Affiche_Valeur_BME680(Bsec * val, Bsec * valPres)
{
  tft.setCursor(0, 0);
  //tft.fillRect(0,250,229,150,BLACK);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.println("DébutAffichage");
  if ( val->status == BSEC_OK) // If new data is available
    { 
      
      //----------------------------//
      char pres[10]; 
      //sprintf(pres, "%d", val->pressure);
      sprintf(pres, "%d", val->rawTemperature);
      //(char *)(val->pressure);
      /*char * humid = (char *)(val->humidity);
      char * aqi = (char *)(val->iaq);
      char * temp = (char *)(val->rawTemperature);
      char * co2 = (char *)(val->co2Equivalent);
      char * voc = (char *)(val->breathVocEquivalent);*/

      char presP[10]; 
      //sprintf(presP, "%d", valPres->pressure);
      sprintf(presP, "%d", valPres->rawTemperature);
      //Serial.print(pres);
      //presP = (char *)(valPres->pressure);
      /*char * humidP = (char *)(valPres->humidity);
      char * aqiP = (char *)(valPres->iaq);
      char * tempP = (char *)(valPres->rawTemperature);
      char * co2P = (char *)(valPres->co2Equivalent);
      char * vocP = (char *)(valPres->breathVocEquivalent);*/
      //----------------------------//*
      
      //tft.println("val.run : ok !!!!");
      if(val->rawTemperature != valPres->rawTemperature)
      {
        //tft.print("La pression vaut : "); remplacer_valeur(pres, presP); //tft.println(val->pressure);
        tft.print("la temperature vaut : "); remplacer_valeur(pres, presP); //tft.println(val->pressure);
      }
      
      /*tft.print("Le taux d'humidité vaut : "); //tft.println(val->humidity);
      tft.print("Le l'IAQ vaut : "); //tft.println(val->iaq);
      tft.print("L' iaqAccuracy vaut : "); //tft.println(val->iaqAccuracy);
      tft.print("La température vaut : "); //tft.println(val->rawTemperature);
      tft.print("Le taux de CO2 vaut : "); //tft.println(val->co2Equivalent);
      tft.print("Le taux de COV vaut : "); //tft.println(val->breathVocEquivalent);*/
    } 
    else 
    {
      //checkIaqSensorStatus(val);
      tft.println("val->statut : Erreur ");
    }
}
