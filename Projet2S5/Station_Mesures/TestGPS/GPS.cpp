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
#include <stdio.h>
 int count = 0;
 const int tailleMAx = 100;
 char buffer[tailleMAx];
 int resetMes  = 1;
 int Parse = 1;
 int c = 1;
 NMEA stokageMsg;

void beginGPS()
{
  Serial1.begin(9600);
  reset();
  resetMes  = 1;
  Parse = 1;
  count = 0;
}

void GetGPS_MSG()
{
  if (resetMes == 0)
  {
    reset();
    resetMes = 1;  
    //Parse = 1;
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
         if(count == tailleMAx)
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
  while(i<tailleMAx)
  {
    buffer[i] = '\0';
    i++;  
  }
}

void  GPS_msg_parse( /*char buffer*/ )
{
  
  const char * separators = "," ;  
  if( Parse == 0)
  {
    char * copieBuffer = strdup(buffer);
    Parse = 1; 
    char *  parsermsg;
    
    parsermsg = strtok(copieBuffer, separators); // id 

    if(strcmp(parsermsg,"$GPRMC") == 0)
    {
      stokageMsg.GPRMC.id = parsermsg;
      parsermsg = strtok (NULL, ","); //UTC
      stokageMsg.GPRMC.UTCtime = parsermsg;
      parsermsg = strtok (NULL, ",");// statut
      stokageMsg.GPRMC.statut = parsermsg;
      parsermsg = strtok (NULL, ","); //latitude 
      stokageMsg.GPRMC.latitude = parsermsg;
      parsermsg = strtok (NULL, ","); //indicateur latitude 
      stokageMsg.GPRMC.indicateurLatitute = parsermsg;
      parsermsg = strtok (NULL, ",");//longitude 
      stokageMsg.GPRMC.longitude = parsermsg;
      parsermsg = strtok (NULL, ","); //indicateur longitude
      stokageMsg.GPRMC.indicateurLongitude = parsermsg;
      parsermsg = strtok (NULL, ","); //speed gound
      parsermsg = strtok (NULL, ","); // course ground 
      parsermsg = strtok (NULL, ","); // date
      stokageMsg.GPRMC.date = parsermsg;
      parsermsg = strtok (NULL, ", *");//mode (magnetic variation et Est/West indicator sont sauté car on a aucune valeur)
      stokageMsg.GPRMC.mode = parsermsg;
       
      Serial.print(" stokageMsg.GPRMC.id = ");Serial.println(stokageMsg.GPRMC.id);
      Serial.print(" stokageMsg.GPRMC.UTCtime = ");Serial.println(stokageMsg.GPRMC.UTCtime);
      Serial.print(" stokageMsg.GPRMC.statut = ");Serial.println(stokageMsg.GPRMC.statut);
      Serial.print(" stokageMsg.GPRMC.latitude = ");Serial.println(stokageMsg.GPRMC.latitude);
      Serial.print(" stokageMsg.GPRMC.indicateurLatitute = ");Serial.println(stokageMsg.GPRMC.indicateurLatitute);
      Serial.print(" stokageMsg.GPRMC.longitude = ");Serial.println(stokageMsg.GPRMC.longitude);
      Serial.print(" stokageMsg.GPRMC.indicateurLongitude = ");Serial.println(stokageMsg.GPRMC.indicateurLongitude);
      Serial.print(" stokageMsg.GPRMC.date = ");Serial.println(stokageMsg.GPRMC.date);
      Serial.print(" stokageMsg.GPRMC.mode = ");Serial.println(stokageMsg.GPRMC.mode);
      
    }
    else if(strcmp(parsermsg,"$GPGGA") == 0)
    {
      stokageMsg.GPGGA.id = parsermsg;
      parsermsg = strtok (NULL, ","); //UTC
      parsermsg = strtok (NULL, ","); // Latitude 
      parsermsg = strtok (NULL, ","); // Indic Latitude
      parsermsg = strtok (NULL, ","); //Longitude
      parsermsg = strtok (NULL, ","); // Indic longitude 
      parsermsg = strtok (NULL, ","); // position dicator 
      stokageMsg.GPGGA.positionIndicator = parsermsg;
      parsermsg = strtok (NULL, ","); // satellites used 
      parsermsg = strtok (NULL, ","); //HDOP
      parsermsg = strtok (NULL, ","); // MSL Altitude
      stokageMsg.GPGGA.mslAltitude = parsermsg;
      
      Serial.print(" stokageMsg.GPGGA.id = ");Serial.println(stokageMsg.GPGGA.id);
      Serial.print(" stokageMsg.GPGGA.positionIndicator = ");Serial.println(stokageMsg.GPGGA.positionIndicator);
      Serial.print(" stokageMsg.GPGGA.mslAltitude = ");Serial.println(stokageMsg.GPGGA.mslAltitude);
      
    }
    else if(strcmp(parsermsg,"$PMTK001") == 0)
    {
      stokageMsg.PMTK.id = parsermsg;
      parsermsg = strtok (NULL, ", *"); //CMD
      stokageMsg.PMTK.cmd = parsermsg;
      parsermsg = strtok (NULL, ", *"); // Flag
      stokageMsg.PMTK.flag = parsermsg;
      parsermsg = strtok (NULL, ", *"); 
      Serial.print(" stokageMsg.PMTK.id = ");Serial.println(stokageMsg.PMTK.id);
      Serial.print(" stokageMsg.PMTK.cmd = ");Serial.println(stokageMsg.PMTK.cmd);
      Serial.print(" stokageMsg.PMTK.flag = ");Serial.println(stokageMsg.PMTK.flag);
    }
    else{}
        Serial.println("Résultat msg après parsage");
        /*//Serial.println(parsermsg);
         int k = 0;
         while (parsermsg != NULL)
        {
          Serial.println(parsermsg);
          parsermsg = strtok (NULL, ",");
          *stockage = *parsermsg;
          //k++;
        }*/
    //Serial.println("Résultat msg après parsage2"); Serial.println(stock.id);
    //while(stock.id[k] != '\0'){Serial.println(stock.id[k]);k++;}
    free(copieBuffer);
  }
  
}

bool Test_Synchro_GPS()
{
  //if((int)stokageMsg.PMTK.flag == 3) 
  //{
    //Serial.println(stokageMsg.GPRMC.id);
    //if(strcmp(stokageMsg.GPRMC.id,"$GPMRC") == 0)
    //{
        //Serial.println("première boucle ok");
        if(strcmp(stokageMsg.GPRMC.statut,"A") == 0)
        {
          Serial.println("Message OK!!!");
          return true;
        }
        else{Serial.println("nooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnnnnnn presque");}
    //} 
     
    /*else if(strcmp(stokageMsg.GPGGA.id,"$GPGGA") == 0)
    {
      Serial.println("Message OK :(");
      return false;
    }*/

    /*else
    {
      Serial.println("Message non OK :(");
      return false;   
    }*/
 /* }
  
  else
    {
      Serial.println("Message non OK FDP :(");
      return false;   
    }*/
}

void Choix_Msg_NMEA(int c)
{ 
  if(c == 1)
    {
       Serial1.write("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    }
    else
    {
       Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    }

}
