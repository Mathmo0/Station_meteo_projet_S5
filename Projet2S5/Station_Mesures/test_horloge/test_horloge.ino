
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
  Test.D.jour_semaine = 7;
  Test.D.jour_mois = 13;
  Test.D.mois =  12;
  Test.D.annee = 20;
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
