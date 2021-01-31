// Fichier TFT_Affichage.cpp
// Routines de gestion d'affichage sur écran TFT Adafruit 2050


#include "TFT_Affichage.h"
#define PMIN 960
#define PMAX 1050

float SommePression = 0; 
int nbValeur = 0;
float StockageMoyennePression[28]; //= {970,1000,980,990,1050,987,3456,10987,5555,12654,999,7658,3333,6789,6543,1234,13765,7890,3456,6310,9876,4567,2345,9987,8876,7765,6654,900};
uint8_t heurePres  = 25;
int i = 0; //= 27;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void TFT_setup()
{
  Serial.begin(9600);  
  tft.reset();
  uint16_t identifier = tft.readID();

  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  tft.fillRect(20,140,280,150,RED);
  tft.fillRect(25,145,270,140,BLACK);
  tft.fillRect(20,295,280,55,GREEN);
  tft.fillRect(25,300,270,45,BLACK);
  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.println(F("Done!"));
  //tft.fillScreen(WHITE);
}

int centre(int j, int t, int a)
{
  int k = (a - j*6*t)/2;
  return k;
}

void TFT_Affichage_Date(Horloge H, Horloge P)
{
  if(H.D.jour_mois != P.D.jour_mois || H.D.mois != P.D.mois || H.D.annee != P.D.annee)
  {
    tft.setTextSize(2);
    char * jour[] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"};
    char * mois[]= {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};

    //char * date[] = strcat(jour[H.D.jour_semaine-1], " ", H.D.jour_mois, " ", mois[H.D.mois-1], " ", H.D.annee + 2000);

    char jm[20]; 
    //dtostrf(H.D.jour_mois, 3, 0, jm);
    sprintf(jm, "%d", H.D.jour_mois);
    char aa[20]; 
    //dtostrf(H.D.annee + 2000, 5, 0, aa);
    sprintf(aa, "%d", H.D.annee + 2000);
    int taille = strlen(jm) + strlen(aa) + strlen(jour[H.D.jour_semaine-1]) + strlen(mois[H.D.mois-1]) + 3;
    int i = centre(taille, 2, 320);
    tft.setCursor(i,20);
    tft.fillRect(0,17,320,20,BLACK);
    
    //tft.setTextSize(2);
    //tft.print(date[]);
    tft.print(jour[H.D.jour_semaine-1]);
    tft.print(" ");
    tft.print(H.D.jour_mois);
    tft.print(" ");
    tft.print(mois[H.D.mois-1]);
    tft.print(" ");
    tft.print(H.D.annee + 2000);
  }
}

void TFT_Affiche_Heure(Horloge H, Horloge P)
{
  if(H.H.seconde != P.H.seconde)
  {
    tft.setTextSize(4);
    char h[5];
    sprintf(h, "%d", H.H.heure);

    char m[5];
    sprintf(m, "%d", H.H.minute);

    char s[5];
    sprintf(s, "%d", H.H.seconde);
    
    int taille = strlen(h) + strlen(m) + strlen(s) + 2;
    int i = centre(taille, 4, 320);;
    tft.setCursor(i,80);
    //tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.fillRect(0,77,320,40,BLACK);
    tft.print(H.H.heure);
    tft.print(":");
    tft.print(H.H.minute);
    tft.print(":");
    tft.print(H.H.seconde);   
  }
}

void TFT_Affiche_EteHiv(int EteHiv, int  EteHivPres)
{
  if( EteHiv != EteHivPres)
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
    int taille = strlen(indic);
    int i = centre(taille, 2, 100);
    tft.setCursor(180 + i, 50);
    tft.fillRect(180,47,100,20,BLACK);
    //tft.print("heure d'");
    tft.print(indic);
  }
}

void TFT_Affiche_ville_ref_fuseau_horaire(pays Pays, pays PaysPres)
{
  if(strcmp(Pays.ville, PaysPres.ville))
  {
    tft.setTextSize(2);
    int taille = strlen(Pays.ville) + strlen(Pays.pays) + 2;
    int i = centre(taille, 2, 180);
    tft.setCursor(i, 50);
    tft.fillRect(0,47,180,20,BLACK);
    tft.print(Pays.ville);tft.print(", ");tft.print(Pays.pays);
  }
}

void TFT_Affiche_Etat_Synchro(NMEA Verif)
{
  tft.setTextSize(2);
  if(Test_Synchro_GPS(Verif))
  {
    tft.fillCircle(289,57,10,GREEN);
  }
  else
  {
    tft.fillCircle(289,57,10,RED);
  }
}

void remplacer_valeur(char * V, char * VP, int x, int y)
{
  int len = max(strlen(V), strlen(VP));
  int i = 0;
  Serial.print("V = "); Serial.println(V);
  Serial.print("VP = "); Serial.println(VP);
  while (V[i] == VP[i] && i <= len)
  {
    ++i;
  }
  tft.setCursor(x + i*6*2, y);
  tft.fillRect(x + i*6*2, y, (len-i)*6*2,7*2,BLACK);
  for (i; i <= strlen(V); ++i)
  {
    tft.print(V[i]);
  }
}

void TFT_Affiche_Valeur_BME680(Bsec * val, Bsec valPres)
{  
 tft.setTextSize(2);
 if (val->status == BSEC_OK) // If new data is available
    { 
      char tmp[10];
      char tmp2[10];
      if (val->rawTemperature != valPres.rawTemperature)
      {
        char  * presT;
        char * presPT;
        dtostrf(val->rawTemperature, 10, 1, tmp);
        presT = strdup(tmp);
        dtostrf(valPres.rawTemperature, 10, 1, tmp2);
        presPT = strdup(tmp2);
        tft.setCursor(27, 155);
        tft.print("Temperature : "); 
        remplacer_valeur(presT, presPT, 130, 155); 
        tft.setCursor(280, 155);
        tft.print("C");
        free(presT);
        free(presPT);
      }

      if (val->pressure != valPres.pressure)
      {
        char  * presH;
        char * presPH;
        dtostrf(val->pressure/100, 10, 2, tmp);
        presH = strdup(tmp);
        dtostrf(valPres.pressure/100, 10, 2, tmp2);
        presPH = strdup(tmp2);
        tft.setCursor(27, 185);
        tft.print("Pression : "); 
        remplacer_valeur(presH, presPH, 130, 185); 
        tft.setCursor(260, 185);
        tft.print("hPa");
        free(presH);
        free(presPH);
      }

      if (val->humidity != valPres.humidity)
      {
        char  * presHu;
        char * presPHu;
        dtostrf(val->humidity, 10, 1, tmp);
        presHu = strdup(tmp);
        dtostrf(valPres.humidity, 10, 1, tmp2);
        presPHu = strdup(tmp2);
        tft.setCursor(27, 215);
        tft.print("Humidite : "); 
        remplacer_valeur(presHu, presPHu, 130, 215); 
        tft.setCursor(280, 215);
        tft.print("%");
        free(presHu);
        free(presPHu);
      }

      if (val->co2Equivalent != valPres.co2Equivalent)
      {
        char  * presE;
        char * presPE;
        dtostrf(val->co2Equivalent, 10, 1, tmp);
        presE = strdup(tmp);
        dtostrf(valPres.co2Equivalent, 10, 1, tmp2);
        presPE = strdup(tmp2);
        tft.setCursor(27, 240);
        tft.print("Taux de CO2 : "); 
        remplacer_valeur(presE, presPE, 130, 240); 
        tft.setCursor(260, 240);
        tft.print("ppm");
        free(presE);
        free(presPE);
      }
      
      //---pas assez de place pour affciher le taux de COV mais c'est fonctoinnel---// 
      /*if (val->breathVocEquivalent != valPres.breathVocEquivalent)
      {
        char  * presB;
        char * presPB;
        dtostrf(val->breathVocEquivalent, 10, 1, tmp);
        presB = strdup(tmp);
        dtostrf(valPres.breathVocEquivalent, 10, 1, tmp2);
        presPB = strdup(tmp2);
        tft.setCursor(27, 260);
        tft.print("Taux de COV : "); 
        remplacer_valeur(presB, presPB, 130, 260); 
        tft.setCursor(260, 260);
        tft.print("ppm");
        free(presB);
        free(presPB);
      }*/
      
      if (val->iaq != valPres.iaq)
      {
        char  * presA;
        char * presPA;
        dtostrf(val->iaq, 10, 1, tmp);
        presA = strdup(tmp);
        dtostrf(valPres.iaq, 10, 1, tmp2);
        presPA = strdup(tmp2);
        tft.setCursor(27, 305);
        tft.print("IAQ : "); 
        remplacer_valeur(presA, presPA, 130, 305); 
        tft.setCursor(260, 305);
        free(presA);
        free(presPA);
      }

      if (val->iaqAccuracy != valPres.iaqAccuracy)
      {
        char  * presAc;
        char * presPAc;
        dtostrf(val->iaqAccuracy, 10, 0, tmp);
        presAc = strdup(tmp);
        dtostrf(valPres.iaqAccuracy, 10, 0, tmp2);
        presPAc = strdup(tmp2);
        tft.setCursor(27, 325);
        tft.print("IAQAcc : "); 
        remplacer_valeur(presAc, presPAc, 130, 325); 
        tft.setCursor(260, 325);
        free(presAc);
        free(presPAc);
      }
    } 
    else 
    {
      Serial.println("val->statut : Erreur ");
    }  
}

void graphiqueMoyennePression()
{
   float  absicsse[] = {10,469,309,469}; //x1,y1,x2,y2  Valeur que tu devra mettre mathis : 10,469,309,469
   float  ordonne[] = {309,469,309,369};// x1,y1,x2,y2  Valeur que tu devra mettre mathis : 309,469,309,369
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
    tft.drawLine(absicsse[0], absicsse[1]-i,absicsse[2],absicsse[3]-i, WHITE);
   }
   
  int nbBarre = 0;
  int distanceentreBarre = 5;
  int epaisseur_barre = 5;
  
  //float StockageMoyennePressionTest[28] {900,1000,1980,2190,7777,987,3456,10987,5555,12654,999,7658,3333,6789,6543,1234,13765,7890,3456,6310,9876,4567,2345,9987,8876,7765,6654};
   for ( nbBarre = 0; nbBarre<=i; nbBarre++)
   {
      int hauteurBarre = roundf(StockageMoyennePression[nbBarre]) ;
      //Serial.print("StockageMoyennePression[nbBarre]");Serial.println(StockageMoyennePression[nbBarre]);
      //Serial.print("PMIN = ");Serial.println(PMIN);
      //Serial.print("PMAX = ");Serial.println(PMAX);
      if ( hauteurBarre >= PMAX)
      {
          //Serial.println("ENtrer dans la boucle >=PMAX");
          hauteurBarre = (PMAX-PMIN);//*epaisseur_barre;
      }
      else if (hauteurBarre <= PMIN)
      {
          //Serial.println("ENtrer dans la boucle <=PMIN");
          hauteurBarre = 0 ;//(PMIN-PMIN)*epaisseur_barre
      }
      else
      {
           //Serial.println("ENtrer dans la boucle normal");
           hauteurBarre = (StockageMoyennePression[nbBarre]-PMIN);//*epaisseur_barre ;
      }
      //Serial.print("hauteur barre = ");Serial.println(hauteurBarre);
      tft.fillRect(absicsse[2]-(distanceentreBarre*nbBarre*2),absicsse[1]-hauteurBarre, epaisseur_barre,hauteurBarre,GREEN);
   }
}

void MoyennePression(Horloge H)
{
  if( H.H.heure == heurePres)
  {
      StockageMoyennePression[i] = (SommePression/nbValeur)/100; // pour avoir en hPa
  }
  else
  {    
    i++;
    SommePression = 0; 
    heurePres = H.H.heure;
    nbValeur = 0;
    if(i>=28)
    {
      /*on supprime la première valeur du tableau(la plus ancienne) en décalent tout de 1 et permet de libèrer la dernière case*/
      
      for(int j = 0; j<i-1;j++)
      {
          StockageMoyennePression[j] = StockageMoyennePression[j+1];
      }
      i--;      
    }
  }
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

void TFT_Affiche_Delta(float recupDelta, float recupDeltaPres)
{
  char tmp[10];
  char tmp2[10];
  if(recupDelta != recupDeltaPres)
  {
    char  * presD;
    char * presPD;
    dtostrf(recupDelta, 10, 0, tmp);
    presD = strdup(tmp);
    dtostrf(recupDeltaPres, 10, 0, tmp2);
    presPD = strdup(tmp2);
    tft.setCursor(27, 265);
    tft.print("DP : "); 
    remplacer_valeur(presD, presPD, 100, 265);
    tft.setCursor(260, 265);
    tft.print("hPa");
    free(presD);
    free(presPD);
  }
}
