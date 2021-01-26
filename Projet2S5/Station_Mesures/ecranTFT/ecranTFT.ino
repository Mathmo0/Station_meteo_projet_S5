#include "TFT_Affichage.h"

Horloge DatePres;
extern char * EteHiv;
extern char * EteHivPres;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /*Definition Tableau pour la correction date_Heure_UTC en fonction du pays*/
  pays France;
  France.pays = "France";
  France.ville = "Paris";
  France.corr.minute = 0;
  France.corr.heure = 1;
   
  pays Angleterre;
  Angleterre.pays = "Royaume-Uni";
  Angleterre.ville = "Londres";
  Angleterre.corr.heure = 0;
  Angleterre.corr.minute = 0;
  
  pays Russie;
  Russie.pays = "Russie";
  Russie.ville = "Moscou";
  Russie.corr.heure = 3;
  Russie.corr.minute = 0;
  
  pays USA;
  USA.pays = "USA";
  USA.ville = "New York";
  USA.corr.heure = -5;
  USA.corr.minute = 0;
  
  pays Canada;
  Canada.pays = "Candada";
  Canada.ville = "Montreal";
  Canada.corr.heure = -5;
  Canada.corr.minute = 0;
  
  pays Japon;
  Japon.pays = "Japon";
  Japon.ville = "Tokyo";
  Japon.corr.heure = 9;
  Japon.corr.minute = 0;
  
  pays Chine;
  Chine.pays = "Chine";
  Chine.ville = "Pekin";
  Chine.corr.heure = 8;
  Chine.corr.minute = 0;
  
  pays FuseauHoraire[7] = {France,Angleterre,Russie,USA,Canada,Japon,Chine};
 //__________________________________
  
  beginDs1307();

  Horloge Test;
  Test.H.seconde = 50;
  Test.H.minute = 59;
  Test.H.heure = 23;
  
  Test.D.jour_mois = 8;
  Test.D.mois =  12;
  Test.D.annee = 21;
  
  Horloge EteHiv;
  EteHiv.H.heure = 0;
  EteHiv.H.minute = 0;
  EteHiv.H.seconde = 0;

  EteHiv.D.jour_mois = 0;
  EteHiv.D.mois =  0;
  EteHiv.D.annee = 0;
  
  
  Test = Correction_Heure_Date(Test, Chine, EteHiv);
  
  setDateDs1307(Test);
  
  TFT_setup();
}

void loop() {
  // put your main code here, to run repeatedly:

   //delay(1000);
   Horloge Test = getDateDs1307();
   
   //Test.D.jour_semaine = jour_semaine(Test.D.jour_mois, Test.D.mois, Test.D.annee);
   EteHiv = IndicateurEteHiv(Test);

   TFT_Affichage_Date(Test, DatePres);
   TFT_Affiche_Heure(Test, DatePres);
   TFT_Affiche_EteHiv(EteHiv, EteHivPres);

   DatePres = Test;
   EteHivPres = EteHiv;
   
   //delay(1000);
}
