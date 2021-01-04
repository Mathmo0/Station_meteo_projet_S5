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

void beginGPS()
{
  Serial1.begin(9600);
}

void GetGPS_MSG()
{
  //strtok
  char test[100];
  
  //Serial.println("________________affichage avant parse___________________");
  
  //Serial.println("________________début parse___________________");
  Serial1.readBytesUntil("<CR><LF>",test,100);
  Serial.print(test);
  int j  = 0;
  while( j <100)
  {
    Serial.println(test[j]);
    delay(200);  
    j++;
  }
  //test[200]= '\0';
  //Serial.println("________________fin parse___________________");
  
  //Serial.println("________________Affichage après reset___________________");
  int i = 0;
  while(i<100)
  {
    test[i] = '\0';
    i++;  
  }
  //Serial.println(buffer[0]);*/
  Serial.print(test);
}
