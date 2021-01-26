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
//#include "C:\Users\maxim\Documents\station-meteo-projet-s5\Projet2S5\Station_Mesures\test_horloge\RTC_DS1307.h"
extern int testH;
 int count = 0;
 const int tailleMAx = 100;
 char buffer[tailleMAx];
 int resetMes  = 1;
 int Parse = 0;
 NMEA stokageMsg;

void beginGPS()
{
  Serial1.begin(9600);
  reset();
  resetMes  = 1;
  Parse = 0;
  count = 0;
}

char * GetGPS_MSG()
{
  if (resetMes == 0)
  {
    reset();
    resetMes = 1;  
    //Parse = 1;
  }  
  else if(strlen(buffer)!= 0)
  {
    reset();
  }   
      while(Serial1.available())
      {  
         buffer[count] = Serial1.read();
         //Serial.println(buffer[count]);
         if(buffer[count] == '\n' && buffer[count-1] == '\r' )
         {
              //Serial.println("Sortie en cours fdp : ");
              //count++;
              resetMes = 0;
              Parse = 1;
              //Serial.print("Avnt return : ");Serial.print(buffer);
              char * test = strdup(buffer);
              //Serial.print("test =  ");Serial.print(test);
              return test;   
         }
         count++;
         if(count == tailleMAx)
         {
            reset();  
         }
          //delay(200); 
      }
  Serial.println(buffer);
  //return buffer ; 
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

NMEA GPS_msg_parse(char * buffer2)
{
  const char * separators = "," ;  
 
  if( Parse == 1)
  {
    //Serial.println("Entrée1");
    char * copieBuffer = strdup(buffer2);
    Parse = 0; 
    char *  parsermsg;
     
    
    parsermsg = strtok(copieBuffer, separators); // id 
    //Serial.print("parsermsg = "); Serial.println(parsermsg);
    if(strcmp(parsermsg,"$GPRMC") == 0)
    {
      //Serial.println("Entrée2");
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
      testH++;
      /*Serial.print(" stokageMsg.GPRMC.id = ");Serial.println(stokageMsg.GPRMC.id);
      Serial.print(" stokageMsg.GPRMC.UTCtime = ");Serial.println(stokageMsg.GPRMC.UTCtime);
      Serial.print(" stokageMsg.GPRMC.statut = ");Serial.println(stokageMsg.GPRMC.statut);
      Serial.print(" stokageMsg.GPRMC.latitude = ");Serial.println(stokageMsg.GPRMC.latitude);
      Serial.print(" stokageMsg.GPRMC.indicateurLatitute = ");Serial.println(stokageMsg.GPRMC.indicateurLatitute);
      Serial.print(" stokageMsg.GPRMC.longitude = ");Serial.println(stokageMsg.GPRMC.longitude);
      Serial.print(" stokageMsg.GPRMC.indicateurLongitude = ");Serial.println(stokageMsg.GPRMC.indicateurLongitude);
      Serial.print(" stokageMsg.GPRMC.date = ");Serial.println(stokageMsg.GPRMC.date);
      Serial.print(" stokageMsg.GPRMC.mode = ");Serial.println(stokageMsg.GPRMC.mode);*/

      return stokageMsg;
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
      
      /*Serial.print(" stokageMsg.GPGGA.id = ");Serial.println(stokageMsg.GPGGA.id);
      Serial.print(" stokageMsg.GPGGA.positionIndicator = ");Serial.println(stokageMsg.GPGGA.positionIndicator);
      Serial.print(" stokageMsg.GPGGA.mslAltitude = ");Serial.println(stokageMsg.GPGGA.mslAltitude);*/

      return stokageMsg;
      
    }
    else if(strcmp(parsermsg,"$PMTK001") == 0)
    {
      stokageMsg.PMTK.id = parsermsg;
      parsermsg = strtok (NULL, ", *"); //CMD
      stokageMsg.PMTK.cmd = parsermsg;
      parsermsg = strtok (NULL, ", *"); // Flag
      stokageMsg.PMTK.flag = parsermsg;
      parsermsg = strtok (NULL, ", *"); 
      
      /*Serial.print(" stokageMsg.PMTK.id = ");Serial.println(stokageMsg.PMTK.id);
      Serial.print(" stokageMsg.PMTK.cmd = ");Serial.println(stokageMsg.PMTK.cmd);
      Serial.print(" stokageMsg.PMTK.flag = ");Serial.println(stokageMsg.PMTK.flag);*/

      return stokageMsg;
    }
    //else{}
        Serial.println("Résultat msg après parsage");
        
    free(copieBuffer);
    
  }
   return stokageMsg;
  
}
bool Test_Synchro_GPS()
{
  if((int)stokageMsg.PMTK.flag == 3) 
  {
    //Serial.println("Message OK2!!!");
    return true;
  }
  
  else if(strcmp(stokageMsg.GPRMC.statut,"A") == 0)
  {
      //Serial.println("Message OK!!!");
      return true;
  }
 
  else if(strcmp(stokageMsg.GPGGA.id,"$GPGGA") == 0)
  {
    Serial.println("Message OK :(");
    return false;
  }
  //else{Serial.println("nooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnnnnnn presque");}  
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

Horloge Extract_date_heure_from_GPS(char Date[6], char Heure[6])
{
    /*extraction del'heure */
  
    /*Serial.print(" Heure[0] = ");Serial.println(Heure[0]);
    Serial.print(" Heure[1] = ");Serial.println(Heure[1]);
    Serial.print(" Heure[2] = ");Serial.println(Heure[2]);
    Serial.print(" Heure[3] = ");Serial.println(Heure[3]);
    Serial.print(" Heure[4] = ");Serial.println(Heure[4]);
    Serial.print(" Heure[5] = ");Serial.println(Heure[5]);*/
    
    
    char HeureFromGPS[3];  
    char MinFromGPS[3]; 
    char SecFromGPS[3]; 
    char anneeFromGPS[3];  
    char MoisFromGPS[3]; 
    char jourMoisFromGPS[3]; 
    Horloge H;
    
    HeureFromGPS[0] = (char)Heure[0];
    HeureFromGPS[1] = (char)Heure[1];
    HeureFromGPS[2] = '\0';
    
    MinFromGPS[0] = (char)Heure[2];
    MinFromGPS[1] = (char)Heure[3];
    MinFromGPS[2] = '\0';
        
    SecFromGPS[0] = (char)Heure[4];
    SecFromGPS[1] = (char)Heure[5];
    SecFromGPS[2] = '\0';
    
    H.H.heure = (uint8_t)atoi(HeureFromGPS);
    H.H.minute = (uint8_t)atoi(MinFromGPS);
    H.H.seconde = (uint8_t)atoi(SecFromGPS);
    Serial.print("H.H.heure = ");Serial.println(H.H.heure);
    Serial.print("H.H.Minute = ");Serial.println(H.H.minute);
    Serial.print("H.H.seconde = ");Serial.println(H.H.seconde);

    /*extraction dela date*/
    
    
    
    jourMoisFromGPS[0] = (char)Date[0];
    jourMoisFromGPS[1] = (char)Date[1];
    jourMoisFromGPS[2] = '\0';
  
    MoisFromGPS[0] = (char)Date[2];
    MoisFromGPS[1] = (char)Date[3];
    MoisFromGPS[2] = '\0';
    
    anneeFromGPS[0] = (char)Date[4];
    anneeFromGPS[1] = (char)Date[5];
    anneeFromGPS[2] = '\0';
    
    H.D.jour_mois = (uint8_t)atoi(jourMoisFromGPS);
    H.D.mois = (uint8_t)atoi(MoisFromGPS);
    H.D.annee = (uint8_t)atoi(anneeFromGPS);
    Serial.println("H.D.annee =  ");Serial.println(H.D.annee);
    Serial.println("H.D.mois =  ");Serial.println(H.D.mois);
    Serial.print("H.D.jour_mois=  ");Serial.println(H.D.jour_mois);
    H.D.jour_semaine = jour_semaine( H.D.jour_mois,H.D.mois,H.D.annee);
    //Serial.print("H.D.jour-semaine =  ");Serial.println(H.D.jour_semaine);
    return H;
}
