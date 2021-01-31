#include "RTC_DS1307.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  /*Definition Tableau pour la correction date_Heure_UTC en fonction du pays*/
  
  

 //__________________________________
 
  beginDs1307();
  
  Horloge Test;
  Test.H.seconde = 0;
  Test.H.minute = 0;
  Test.H.heure = 0;
  
  Test.D.jour_mois = 1;
  Test.D.mois =  3;
  Test.D.annee = 20;

  Horloge EteHiv;
  EteHiv.H.heure = 0;
  EteHiv.H.minute = 0;
  EteHiv.H.seconde = 0;

  EteHiv.D.jour_mois = 0;
  EteHiv.D.mois =  0;
  EteHiv.D.annee = 0;

  pays FuseauHoraireDuPays = FuseauHoraire(3); //De base  Le Fuseau hraire est défini sur Paris 
  Serial.print("coor.heure.pays  = ");Serial.println(FuseauHoraireDuPays.corr.heure); 
  
  Test = Correction_Heure_Date(Test,FuseauHoraireDuPays, EteHiv);
  
  Test.D.jour_semaine = jour_semaine(Test.D.jour_mois, Test.D.mois, Test.D.annee);
  
  setDateDs1307(Test);
}

void loop() 
{
  // put 3 main code here, to run repeatedly:
   //Serial.print("Bonjour");
   delay(1000);
   Horloge Test = getDateDs1307();

   Affiche_date_heure(Test);
}
