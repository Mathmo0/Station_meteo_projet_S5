// Fichier GPS.cpp
// Fonction de gestion du module GPS
// Acquisition d'un message NMEA
// Parser un message NMEA
// Savoir si le module GPS est synchronisé
// Définir le type de message NMEA renvoyé par le module GPS
// Extraire les données de date et d'heure depuis les données GPS

#include <Arduino.h>
#include "GPS.h"
#include <string.h>
 int count = 0;
 char buffer[200];
 int resetMes  = 1;
 int Parse = 1;
 int c = 1;

void beginGPS()
{
  Serial1.begin(9600);
  reset();
}

void GetGPS_MSG()
{
  if (resetMes == 0)
  {
    reset();
    resetMes = 1;  
    Parse = 1;
  }
  //reset();
 /* buffer[count] = Serial1.read();
  Serial.print("premier crac : ");Serial.println(buffer[count]);
  delay(100);
  if( buffer[count] == '$')
  {
      count++;
      Serial.println("entrer dans la boucle");*/
      
      while(Serial1.available())
      {
          //Serial.print("Valeur de count : ");Serial.println(count);
          //Serial.println("entrer dans la boucle2");
          //Serial.println(test[j]);
          //Serial.print(buffer[j]);
         
         buffer[count] = Serial1.read();
         Serial.println(buffer[count]);
         if(buffer[count] == '\n' && buffer[count-1] == '\r' )
         {
              Serial.println("Sortie en cours fdp : ");
              //count++;
              resetMes = 0;
              Parse = 0;
              Serial.print(buffer);
              return ;   
         }
         count++;
         if(count == 200)
         {
            reset();  
         }
          //delay(200); 
      }
      
      //buffer[count] = '\0';
 /* }
  else{Serial.println("Isnot good fdp");}*/
 
  Serial.println(buffer);
  /*if( resetMes ==1 && count <= 200)
  {
  reset(); 
  }  */
  //test[200]= '\0';
  //Serial.println("________________fin parse___________________");
  
  //Serial.println("________________Affichage après reset___________________");
  /*int i = 0;
  while(i<200)
  {
    buffer[i] = '\0';
    i++;  
  }*/
  //Serial.println(buffer[0]);*/
  //Serial.print(buffer);
}

void reset()
{
  int i = 0;
  count = 0;
  while(i<200)
  {
    buffer[i] = '\0';
    i++;  
  }
}

void Choix_Msg_NMEA()
{ 
  Serial.print("select 1 ou 2 ou rien je men balek ntm sale merde");
  if(Serial.available())
  {
    c = Serial.read();
    if(c == 2)
    {
       Serial1.write("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    }
    else
    {
       Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    }
  }
}
