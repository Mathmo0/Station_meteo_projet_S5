

#include "RTC_DS1307.h"

//char UTC[7] = {1, 0, 3, -5, -6, 9, 8};




void setup() 
{
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
  Canada.ville = "Montréal";
  Canada.corr.heure = -5;
  Canada.corr.minute = 0;
  
  pays Japon;
  Japon.pays = "Japon";
  Japon.ville = "Tokyo";
  Japon.corr.heure = 9;
  Japon.corr.minute = 0;
  
  pays Chine;
  Chine.pays = "Chine";
  Chine.ville = "Pékin";
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

  Horloge UTC;
  UTC.H.heure = 1;
  UTC.H.minute = 30;
  UTC.H.seconde = 0;

  UTC.D.jour_mois = 0;
  UTC.D.mois =  0;
  UTC.D.annee = 0;

  Horloge EteHiv;
  EteHiv.H.heure = 0;
  EteHiv.H.minute = 0;
  EteHiv.H.seconde = 0;

  EteHiv.D.jour_mois = 0;
  EteHiv.D.mois =  0;
  EteHiv.D.annee = 0;
  
  Test = Correction_Heure_Date(Test, UTC, EteHiv);

  //Correction_Heure_Date(Horloge H, int CorUTC, int CorEteHiv)
  Test.D.jour_semaine = jour_semaine(Test.D.jour_mois, Test.D.mois, Test.D.annee);
  setDateDs1307(Test);
  //Affiche_date_heure(Test);

}

void loop() 
{
  // put 3 main code here, to run repeatedly:
   //Serial.print("Bonjour");
   delay(1000);
   Horloge Test = getDateDs1307();

   Affiche_date_heure(Test);
}
