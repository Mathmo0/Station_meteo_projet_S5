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
#include "BME680_Sensor.h"

// Variables globales

int testH = 0;

/*varibale poru le Timer1 : */
#define BASE_TEMPS_TIMER1_05s 57723U
#define BASE_TEMPS_TIMER1_1s 49911U
#define Led2_pin LED_BUILTIN
#define T_EVNT1 4 // Période de gestion de l'événémént 1
#define T_EVNT2 8 // Période de gestion de l'événémént 2
volatile int T_Time_Out_Evenement1 = 0;
volatile int T_Time_Out_Evenement2 = 0;

/*--------------------------------------------------------------------------------------------*/
// Routine d'IT TImer1 sur Overflow registre de comptage
ISR(TIMER1_OVF_vect)
{
  TIMSK1 &= 0B11111110;

  T_Time_Out_Evenement1 --;
  T_Time_Out_Evenement2 --;
  
  TIFR1 |= 0B00000001;
  TCNT1 = BASE_TEMPS_TIMER1_05s;
  TIMSK1 = 0B00000001;
  SREG |= 0B10000000;
}
/*--------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------*/
void setup(void)
{
  Serial.begin(9600);
  /*Partir initialisation Horloge :*/
  beginDs1307();
  
  /*Partie initialisation GPS : */
  beginGPS();
  Choix_Msg_NMEA(2);
  /*GetGPS_MSG();
  GPS_msg_parse();
  Test_Synchro_GPS(); */
  char * buffer;
  Horloge H;
  NMEA Test;
  /*Partie initialisation Timer1 : */
  /*noInterrupts();

  TCCR1A = 0B00000000; // Mode normal
  TCCR1B = 0B00000000; // Timer1 arreté
  TCCR1C = 0B00000000;
  TIFR1 |= 0B00000001; // Mise à 1 du bit TOV1
  TIMSK1 |= 0B0000001; // Mise à 1 du bit TOEI1 pour autoriser les IT timer 1
  TCNT1 = BASE_TEMPS_TIMER1_05s;
  interrupts();
  TCCR1B |= 0B00000100; //demarre à 1024
  Serial.println("Initialisation du timer1 : done");*/
} 
/*--------------------------------------------------------------------------------------------*/
void loop() 
{
  char * buffer;
  Horloge H;
  NMEA Test;
  if (T_Time_Out_Evenement1 <= 0)
  {
    buffer = GetGPS_MSG();
    Test = GPS_msg_parse(buffer);
    Test_Synchro_GPS();
    
  }
  Serial.println("en attente");
  /*if (T_Time_Out_Evenement2 <= 0)
  {
    Tache2 ();
    T_Time_Out_Evenement2 = T_EVNT2;
  }*/


}
