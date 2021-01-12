// Fichier GPS.h

#include <Arduino.h>
#include <Wire.h>
// Définition des types de données pour gestion des données GPS

typedef struct PMTK
{
  char * id;
  char * cmd;
  char * flag;
} PMTK;

typedef struct GPGGA 
{
  /*On stocke que ces paramètres car on utilisera pas les autres pour la suite du projet*/
  
  char * id;
  char * positionIndicator;
  char * mslAltitude;
} GPGGA;

typedef struct GPRMC 
{
  /*On stocke que ces paramètres car on utilisera pas les autres pour la suite du projet*/
  
  char * id;
  char * UTCtime;
  char * statut;
  char * latitude;
  char * indicateurLatitute;
  char * longitude;
  char * indicateurLongitude;
  char * date;
  char * mode;
  
} GPRMC;

typedef struct TypeNMEA 
{
  GPRMC GPRMC;
  GPGGA GPGGA;
  PMTK PMTK;
 
}NMEA;

// Définition de constantes symboliques


// Fonctions prototypes

void beginGPS();
void GetGPS_MSG();
void reset();
void  GPS_msg_parse();
bool  Test_Synchro_GPS();
