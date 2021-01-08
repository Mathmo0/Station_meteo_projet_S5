
#include "RTC_DS1307.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  beginDs1307();
  Horloge Test;
  Test.H.seconde = 0;
  Test.H.minute = 45;
  Test.H.heure = 15;
  
  Test.D.jour_mois = 8;
  Test.D.mois =  01;
  Test.D.annee = 21;
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
