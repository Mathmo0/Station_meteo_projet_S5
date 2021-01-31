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
tft.fillScreen(WHITE);
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

void remplacer_valeur(char * V, char * VP, int x, int y)
{
  int len = max(strlen(V), strlen(VP));
  int i = 0;
  Serial.println(V);
  Serial.println(VP);
  while(V[i] == VP[i] && i <= len)
  {
    ++i;
  }
  if(i != len)
  {
    tft.setCursor(x + i*6, y);
    tft.fillRect(x + i*6, y, 50,7*2,BLACK);
    for(i; i<=strlen(V); ++i)
    {
      tft.print(V[i]);
    }
  }
  
  //tft.setCursor(x + i*6 + 130, y);
}

void TFT_Affiche_Valeur_BME680(Bsec * val, Bsec * valPres)
{
  //tft.setCursor(0, 0);
  Serial.print("La pression vaut : ");Serial.println(val->pressure);
      Serial.print("Le taux d'humidité vaut : ");Serial.println(val->humidity);
      Serial.print("Le l'IAQ vaut : ");Serial.println(val->iaq);
      Serial.print("L' iaqAccuracy vaut : ");Serial.println(val->iaqAccuracy);
      Serial.print("La température vaut : ");Serial.println(val->rawTemperature);
      Serial.print("Le taux de CO2 vaut : ");Serial.println(val->co2Equivalent);
      Serial.print("Le taux de COV vaut : ");Serial.println(val->breathVocEquivalent);
  
  tft.setTextSize(2);
  //tft.println("DébutAffichage");
 if (val->status == BSEC_OK) // If new data is available
    { 
      Serial.println("entrer if");
      //if(val->rawTemperature != valPres->rawTemperature)
      //{
        Serial.println("entrer if 2");
      char * presT;
      char * presPT;
      char tmp[10];
      char tmp2[10];
      dtostrf(val->rawTemperature, 10, 1, tmp);
      dtostrf(valPres->rawTemperature, 10, 1, tmp2);
      presT = strdup(tmp);
      presPT = strdup(tmp2);
      Serial.println("presT = ");Serial.println(presT);
      Serial.println("presPT = ");Serial.println(presPT);
      Serial.println("valPres->rawTemperature = ");Serial.println(valPres->rawTemperature);
      Serial.println("val->rawTemperature = ");Serial.println(val->rawTemperature);
        tft.setCursor(30, 155);
        //tft.print("Temperature :"); 
        //remplacer_valeur(presT, presPT, 80, 155); 
        //tft.print("  C");//tft.println(val->pressure);
      /*free(presT);
      free(presPT);
      //}
      

      char presH[10];
      dtostrf(val->pressure, 10, 1, presH);
      char presPH[10];
      dtostrf(valPres->pressure, 10, 1, presPH);
      //if(val->pressure != valPres->pressure)
      //{
        tft.setCursor(30, 185);
        //tft.print("Pression :"); 
        remplacer_valeur(presH, presPH, 20, 185); 
        //tft.print(" hPa");//tft.println(val->pressure);
      //}
      //free(presH);
      free(presPH);

      char presHu[10];
      dtostrf(val->humidity, 10, 1, presHu);
      char presPHu[10];
      dtostrf(valPres->humidity, 10, 1, presPHu);
      //if(val->humidity != valPres->humidity)
      //{
        tft.setCursor(30, 215);
        //tft.print("Humidite :"); 
        remplacer_valeur(presHu, presPHu, 20, 215); 
        //tft.print(" %");//tft.println(val->pressure);
      //}
      //free(presHu);
      //free(presPHu);

      char presE[10];
      dtostrf(val->co2Equivalent, 10, 1, presE);
      char presPE[10];
      dtostrf(valPres->co2Equivalent, 10, 1, presPE);
      //if(val->co2Equivalent != valPres->co2Equivalent)
      //{
        tft.setCursor(30, 240);
        //tft.print("Taux de CO2 :"); 
        remplacer_valeur(presE, presPE, 30, 240); 
        //tft.print(" ppm");//tft.println(val->pressure);
      //}
      //free(presE);
      //free(presPE);*/

      /*char presB[10];
      dtostrf(val->breathVocEquivalent, 10, 1, presB);
      char presPB[10];
      dtostrf(valPres->breathVocEquivalent, 10, 1, presPB);
      if(val->breathVocEquivalent != valPres->breathVocEquivalent)
      {
        tft.setCursor(30, 260);
        //tft.print("Taux de COV :"); 
        remplacer_valeur(presB, presPB, 70, 260); 
        //tft.print(" ppm");//tft.println(val->pressure);
      }

      char presA[10];
      dtostrf(val->iaq, 10, 1, presA);
      char presPA[10];
      dtostrf(valPres->iaq, 10, 1, presPA);
      if(val->iaq != valPres->iaq)
      {
        tft.setCursor(30, 305);
        //tft.print("iAQ :"); 
        remplacer_valeur(presA, presPA, 30, 305);//tft.println(val->pressure);
      }

      char presAc[10];
      dtostrf(val->iaqAccuracy, 10, 1, presAc);
      char presPAc[10];
      dtostrf(valPres->iaqAccuracy, 10, 1, presPAc);
      if(val->iaqAccuracy != valPres->iaqAccuracy)
      {
        tft.setCursor(30, 320);
        //tft.print("iAQAcc :"); 
        remplacer_valeur(presAc, presPAc, 30, 320);//tft.println(val->pressure);
      }*/
      /*tft.print("La pression vaut : ");tft.println(val->pressure);
      tft.print("Le taux d'humidité vaut : ");tft.println(val->humidity);
      tft.print("Le l'IAQ vaut : ");tft.println(val->iaq);
      tft.print("L' iaqAccuracy vaut : ");tft.println(val->iaqAccuracy);
      tft.print("La température vaut : ");tft.println(val->rawTemperature);
      tft.print("Le taux de CO2 vaut : ");tft.println(val->co2Equivalent);
      tft.print("Le taux de COV vaut : ");tft.println(val->breathVocEquivalent);*/
      
    } 
    else 
    {
      Serial.println("val->statut : Erreur ");
    }  
}
