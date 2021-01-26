// Fichier TFT_Affichage.cpp
// Routines de gestion d'affichage sur écran TFT Adafruit 2050


#include "TFT_Affichage.h"

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void TFT_setup()
{
  Serial.begin(9600);  
  tft.reset();
  

  uint16_t identifier = tft.readID();

  tft.begin(identifier);

  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.println(F("Done!"));
  tft.fillScreen(WHITE);
}

void TFT_Affichage_Date(Horloge H, Horloge P)
{
  if(H.D.jour_mois != P.D.jour_mois || H.D.mois != P.D.mois || H.D.annee != P.D.annee)
  {
    char * jour[] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"};
    char * mois[]= {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Août","Septembre","Octobre","Novembre","Décembre"};
    tft.setCursor(0,100);
    tft.fillRect(0,100,319,10,BLACK);
    
    
    tft.setTextSize(1);
    tft.print(jour[H.D.jour_semaine-1]);
    tft.print("    ");
    tft.print(H.D.jour_mois);
    tft.print("    ");
    tft.print(mois[H.D.mois-1]);
    tft.print("    ");
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
    tft.setCursor(0,150);
    //tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.fillRect(0,150,50,10,BLACK);
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
    tft.setCursor(50, 150);
    tft.fillRect(50,150,150,10,BLACK);
    tft.print("heure d'");
    tft.print(EteHiv);
  }
}
