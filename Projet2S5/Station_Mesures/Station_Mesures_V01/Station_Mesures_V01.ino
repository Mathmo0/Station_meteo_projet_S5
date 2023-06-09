// Fichier Station_Mesures.ino

// Mise en oeuvre horloge temps réel : circuit DS1307 Dallas Semi Conducteur
// Mise en oeuvre module GPS
// Mise en oeuvre Capteur BME680
// Mise en oeuvre écran TFT Adafruit 2050
// Mise en oeuvre dalle tactile shield écran Adafruit 2050

// Sortie sur terminal série

// Communication :
//   - DS1307 : bus I2C
//   - Module GPS : port série1
//   - Capteur BME680 : bus I2C

// Version Environnement Arduino : 1.8.8
// Cible matérielle : Atmega 2560_R3

// Version : 1.0

// Inclure les fichiers d'en tête de base
#include <Arduino.h>

// Fichier d'en tête spécifiques
#include "RTC_DS1307.h"
#include "GPS.h"
#include "Calendrier.h"

// Variables globales

char * buffer2;
NMEA msgFromGpsParser;
int k = 0;

pays FuseauHoraire = fuseau_horaire_de_ref(0); // Fuseau Horaire de base : Paris

/*varibale poru le Timer1 : */

#define BASE_TEMPS_TIMER1_05s 57723U
#define BASE_TEMPS_TIMER1_1s 49911U
#define Led2_pin LED_BUILTIN
#define T_EVNT1 14400 //4h // Période de gestion de la synchronisation du GPS
#define T_EVNT2 1 // Affichage(date,heure...) toute les secondes
volatile int T_Time_Out_Evenement1 = 0;
volatile int T_Time_Out_Evenement2 =0;

/*--------------------------------------------------------------------------------------------*/
// Routine d'IT TImer1 sur Overflow registre de comptage
ISR(TIMER1_OVF_vect)
{
  
  TIMSK1 &= 0B11111110;

  T_Time_Out_Evenement1 --;
  T_Time_Out_Evenement2 --;
  
  TIFR1 |= 0B00000001;
  TCNT1 = BASE_TEMPS_TIMER1_1s;
  TIMSK1 = 0B00000001;
  SREG |= 0B10000000;
}
/*--------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------*/
void setup(void)
{
  Serial.begin(9600);
  /*Partie initialisation Horloge :*/
  beginDs1307();
     /*On initialise l'horlge aux 1 Janvier 2010 00:00:00 */
  Horloge H;
  H.H.seconde = 0;
  H.H.minute = 0;
  H.H.heure = 0;
  
  H.D.jour_mois = 1;
  H.D.mois =  1;
  H.D.annee = 10;
  H.D.jour_semaine = jour_semaine( H.D.jour_mois,H.D.mois,H.D.annee);
  setDateDs1307(H);
  
  /*Partie initialisation GPS : */
  
  beginGPS();
  Choix_Msg_NMEA(2); // de type GPRMC de base

  /*Partie initialisation Timer1 : */
  
  noInterrupts();
  TCCR1A = 0B00000000; // Mode normal
  TCCR1B = 0B00000000; // Timer1 arreté
  TCCR1C = 0B00000000;
  TIFR1 |= 0B00000001; // Mise à 1 du bit TOV1
  TIMSK1 |= 0B0000001; // Mise à 1 du bit TOEI1 pour autoriser les IT timer 1
  TCNT1 = BASE_TEMPS_TIMER1_1s;
  interrupts();
  TCCR1B |= 0B00000101; //demarre à 1024
  Serial.println("Initialisation du timer1 : done");
} 
/*--------------------------------------------------------------------------------------------*/
void loop() 
{
  Horloge H;
  Horloge EteHiv;
  int IndicateurEteHIver;
  IndicateurEteHIver = IndicateurEteHiv(H);
  
  buffer2 = GetGPS_MSG();
  msgFromGpsParser = GPS_msg_parse(buffer2);  
  bool synchro = Test_Synchro_GPS(msgFromGpsParser);
  
  if (T_Time_Out_Evenement1 <= 0)
  {   
    if(synchro == true)
    {
      H = Extract_date_heure_from_GPS(msgFromGpsParser.GPRMC.date,msgFromGpsParser.GPRMC.UTCtime);
      IndicateurEteHIver = IndicateurEteHiv(H);  
      H = Correction_Heure_Date(H,FuseauHoraire, IndicateurEteHIver);  
      setDateDs1307(H);
    } 
    
    T_Time_Out_Evenement1 = T_EVNT1;
  }
 
  if (T_Time_Out_Evenement2 <= 0)
  {
       if (synchro == true)
      {
        Serial.println("Synchronisé");
        
        /*Cette condition permet la synchrinisation de la date et de l'heure orsque le GPS se synchronique pour  la première fois */
        if(k  <1)
        {
          H = Extract_date_heure_from_GPS(msgFromGpsParser.GPRMC.date,msgFromGpsParser.GPRMC.UTCtime); 
          IndicateurEteHIver = IndicateurEteHiv(H);  
          H = Correction_Heure_Date(H,FuseauHoraire, IndicateurEteHIver);  
          setDateDs1307(H);
          k++;
        }     
      }
      else
      {
        Serial.println("Non Synchronisé");
      }
      H = getDateDs1307();
      Affiche_date_heure(H);
      
      if(IndicateurEteHIver == 0)
      {
        Serial.println("Nous somme en hiver ");
      }
      else
      {
        Serial.println("Nous somme en été ");
      }
      
      Serial.print("Fuseau Horaire utilisé : ");Serial.print(FuseauHoraire.ville);Serial.print(", ");Serial.println(FuseauHoraire.pays);

      T_Time_Out_Evenement2 = T_EVNT2;
      
      Serial.println("______________________ Fin Affichage ________________________");
      
  }
}
