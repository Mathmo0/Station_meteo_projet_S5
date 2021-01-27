#include "TFT_Affichage.h"

Horloge DatePres;

extern char * EteHiv2;
extern char * EteHivPres;
extern pays PaysPres;

 Horloge EteHiv;
  /*EteHiv.H.heure = 0;
  EteHiv.H.minute = 0;
  EteHiv.H.seconde = 0;

  EteHiv.D.jour_mois = 0;
  EteHiv.D.mois =  0;
  EteHiv.D.annee = 0;*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial1.begin(9600);
  beginGPS();
  
  //__________________________________
  
  beginDs1307();

  Horloge Test;
  Test.H.seconde = 50;
  Test.H.minute = 59;
  Test.H.heure = 23;
  
  Test.D.jour_mois = 8;
  Test.D.mois =  12;
  Test.D.annee = 21;
  
 
  
  
  //Test = Correction_Heure_Date(Test, Chine, EteHiv);
  
  setDateDs1307(Test);
  
  TFT_setup();
}

void loop() {
  // put your main code here, to run repeatedly:

   //delay(1000);
   Horloge Test = getDateDs1307();
   
   pays Pays = fuseau_horaire_de_ref(6);
   
   Test = Correction_Heure_Date(Test, Pays, EteHiv);
   //Test.D.jour_semaine = jour_semaine(Test.D.jour_mois, Test.D.mois, Test.D.annee);
   EteHiv2 = IndicateurEteHiv(Test);

   NMEA test;
   char * buffer;
  
   buffer = GetGPS_MSG();
   test = GPS_msg_parse(buffer);

   TFT_Affichage_Date(Test, DatePres);
   TFT_Affiche_Heure(Test, DatePres);
   TFT_Affiche_EteHiv(EteHiv2, EteHivPres);
   TFT_Affiche_Etat_Synchro(test);
   TFT_Affiche_ville_ref_fuseau_horaire(Pays, PaysPres);

   DatePres = Test;
   EteHivPres = EteHiv2;
   PaysPres = Pays;
   
   //delay(1000);
}
