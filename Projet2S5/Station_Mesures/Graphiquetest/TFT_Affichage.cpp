// Fichier TFT_Affichage.cpp
// Routines de gestion d'affichage sur écran TFT Adafruit 2050


#include "TFT_Affichage.h"
#define PMIN 960
#define PMAX 1050

float SommePression = 0; 
int nbValeur = 0;
float StockageMoyennePression[28] = {900,1000,980,990,1050,987,3456,10987,5555,12654,999,7658,3333,6789,6543,1234,13765,7890,3456,6310,9876,4567,2345,9987,8876,7765,6654,900};
uint8_t heurePres  = 25;
int i = 27;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void TFT_setup()
{
  Serial.begin(9600);  
  tft.reset();
  uint16_t identifier = tft.readID();

  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(BLUE);
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

void TFT_Affiche_EteHiv(int EteHiv, int  EteHivPres)
{
  if( EteHiv == EteHivPres)
  {
    char * indic;
    if(EteHiv == 1)
    {
      indic ="ete";
    }
    else
    {
      indic = "hiver"  ;
    }
    tft.setTextSize(2);
    tft.setCursor(90, 150);
    tft.fillRect(90,150,150,20,BLACK);
    tft.print("heure d'");
    tft.print(indic);
  }
}

void TFT_Affiche_ville_ref_fuseau_horaire(pays Pays, pays PaysPres)
{
  if(strcmp(Pays.ville, PaysPres.ville))
  {
    tft.setTextSize(2);
    tft.setCursor(0, 200);
    tft.fillRect(0,200,150,20,BLACK);
    tft.print(Pays.ville);tft.print(",");tft.print(Pays.pays);
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

void TFT_Affiche_Valeur_BME680(Bsec * val)
{
  tft.setCursor(0, 0);
  tft.fillRect(0,300,319,100,BLACK);
  tft.setTextSize(1);
  //tft.println("DébutAffichage");
 if (val->status == BSEC_OK) // If new data is available
    { 
      tft.print("La pression vaut : ");tft.println(val->pressure);
      tft.print("Le taux d'humidité vaut : ");tft.println(val->humidity);
      tft.print("Le l'IAQ vaut : ");tft.println(val->iaq);
      tft.print("L' iaqAccuracy vaut : ");tft.println(val->iaqAccuracy);
      tft.print("La température vaut : ");tft.println(val->rawTemperature);
      tft.print("Le taux de CO2 vaut : ");tft.println(val->co2Equivalent);
      tft.print("Le taux de COV vaut : ");tft.println(val->breathVocEquivalent);
    } 
    else 
    {
      Serial.println("val->statut : Erreur ");
    }  
}


void graphiqueMoyennePression()
{
   float  absicsse[] = {10,300,225,300}; //x1,y1,x2,y2  Valeur que tu devra mettre mathis : 10,469,309,469
   float  ordonne[] = {225,300,225,215};// x1,y1,x2,y2  Valeur que tu devra mettre mathis : 309,469,309,369
   
   /*5px d'epsce entre chaque barre et 5px pour chaque barre, => E((absicsse[0]-,absicsse[2])/10) pour avoir le nombre
   de coordonnées qu'on peut mettre sur l'abscisse, on mettra ces valeur(donc les différents deltaP) dans un tableau */
   
   //float deltaP = SommePression/nbValeur;

   
   tft.setCursor(0,0);
   tft.drawLine(absicsse[0], absicsse[1],absicsse[2],absicsse[3], RED);
   //tft.drawLine(ordonne[0], ordonne[1],ordonne[2],ordonne[3], RED);
   /* Definition de la zone du graph */ 
   tft.drawRect(absicsse[0], absicsse[1]-100,absicsse[2],110,WHITE);
   
   /*Definition des lignes du graphique : */
   
   for(int i =10;i <= PMAX-PMIN;i= i+10)
   {
    tft.drawLine(absicsse[0], absicsse[1]-i,absicsse[2],absicsse[3]-i, BLACK);
   }
   
  int nbBarre = 0;
  int distanceentreBarre = 5;
  int epaisseur_barre = 5;
  
  
  //float StockageMoyennePressionTest[28] {900,1000,1980,2190,7777,987,3456,10987,5555,12654,999,7658,3333,6789,6543,1234,13765,7890,3456,6310,9876,4567,2345,9987,8876,7765,6654};
   for ( nbBarre = 0; nbBarre<=i; nbBarre++)
   {
      int hauteurBarre = roundf(StockageMoyennePression[nbBarre]) ;
      Serial.print("StockageMoyennePression[nbBarre]");Serial.println(StockageMoyennePression[nbBarre]);
      Serial.print("PMIN = ");Serial.println(PMIN);
      Serial.print("PMAX = ");Serial.println(PMAX);
      if ( hauteurBarre >= PMAX)
      {
          Serial.println("ENtrer dans la boucle >=PMAX");
          hauteurBarre = (PMAX-PMIN);//*epaisseur_barre;
      }

      else if (hauteurBarre <= PMIN)
      {
          Serial.println("ENtrer dans la boucle <=PMIN");
          hauteurBarre = 0 ;//(PMIN-PMIN)*epaisseur_barre
      }

      else
      {
           Serial.println("ENtrer dans la boucle normal");
           hauteurBarre = (StockageMoyennePression[nbBarre]-PMIN);//*epaisseur_barre ;
      }

      Serial.print("hauteur barre = ");Serial.println(hauteurBarre);
      tft.fillRect(absicsse[2]-(distanceentreBarre*nbBarre*2),absicsse[1]-hauteurBarre, epaisseur_barre,hauteurBarre,GREEN);
   }
  //tft.fillRect(90,150,150,20,RED);
  //tft.width();
}

void MoyennePression(Horloge H)
{
  if( H.H.heure == heurePres)
  {
      StockageMoyennePression[i] = (SommePression/nbValeur)/100; // pour avoir en hPa
      Serial.println(i);Serial.print(" : VAleur SommePression[i] = ");Serial.println(StockageMoyennePression[i]);
      Serial.print(" : VAleur SommePression[0] = ");Serial.println(StockageMoyennePression[0]);
  }
  else
  {
    
    i++;
    SommePression = 0; 
    heurePres = H.H.heure;
    nbValeur = 0;
    if(i>28)
    {
      /*reset du tableau en conserveau la dernière valeur qui deviendra la première valeur du tableau*/
      float tmp = StockageMoyennePression[27];
      int j = 0;
      while(j<28)
      {
          Serial.print("tmp = ");Serial.println(tmp);
          Serial.println("reset en cours");
          StockageMoyennePression[j] = 0;
          j++;
      }
      StockageMoyennePression[0] = tmp;
      i=1;
    }
  }
  Serial.print("VAleur SommePression = ");Serial.println(SommePression);
  Serial.print("VAleur nbValeur = ");Serial.println(nbValeur);  
}

float GetDeltaPresssion()
{
  float DeltaP = 0;
  if(StockageMoyennePression[0] == 0 || StockageMoyennePression[1] == 0 )
  {
       return DeltaP;
  } 
  else
  {
    DeltaP = StockageMoyennePression[i] - StockageMoyennePression[i-1];
    return DeltaP; 
  }
}
