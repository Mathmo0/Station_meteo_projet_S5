
#include "RTC_DS1307.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
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
