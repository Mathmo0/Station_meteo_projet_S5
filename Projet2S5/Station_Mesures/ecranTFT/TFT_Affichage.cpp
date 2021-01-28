// Fichier TFT_Affichage.cpp
// Routines de gestion d'affichage sur écran TFT Adafruit 2050


#include "TFT_Affichage.h"

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void TFT_setup()
{
  Serial.begin(9600);  
  tft.reset();
  tft.fillScreen(WHITE);
  

  uint16_t identifier = tft.readID();

  tft.begin(identifier);

  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.println(F("Done!"));
  //tft.fillScreen(WHITE);
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

void TFT_Affiche_Valeur_BME680(Bsec val)
{
  tft.setCursor(0, 300);
  tft.fillRect(0,300,319,100,BLACK);
  tft.setTextSize(1);
  tft.println("DébutAffichage");
  if (val.run()) // If new data is available
    { 
      tft.println("val.run : ok !!!!");
      tft.print("La pression vaut : ");Serial.println(val.pressure);
      tft.print("Le taux d'humidité vaut : ");Serial.println(val.humidity);
      tft.print("Le l'IAQ vaut : ");Serial.println(val.iaq);
      tft.print("L' iaqAccuracy vaut : ");Serial.println(val.iaqAccuracy);
      tft.print("La température vaut : ");Serial.println(val.rawTemperature);
      tft.print("Le taux de CO2 vaut : ");Serial.println(val.co2Equivalent);
      tft.print("Le taux de COV vaut : ");Serial.println(val.breathVocEquivalent);
    } 
    else 
    {
      tft.println("VAl.run : is not good fdp");
      tft.println("CheckDébut");
      checkIaqSensorStatus(val);
      tft.println("CheckRéussi");
    }
}
