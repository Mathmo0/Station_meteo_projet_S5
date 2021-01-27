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
char * buffer2;
//bool synchro = false;
NMEA msgFromGpsParser;

Bsec capteurBME680;

/*varibale poru le Timer1 : */

#define BASE_TEMPS_TIMER1_05s 57723U
#define BASE_TEMPS_TIMER1_1s 49911U
#define Led2_pin LED_BUILTIN
#define T_EVNT1 10 // Période de gestion de l'événémént 1
#define T_EVNT2 3 // Période de gestion de l'événémént 2
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
  Choix_Msg_NMEA(2);
  //char * buffer2;
  //Horloge H;
  //NMEA msgFromGpsParser;

  /*Initialisation du capteurBME680 : */
  Wire.begin();
  
  capteurBME680.begin(BME680_I2C_ADDR_PRIMARY, Wire);
  checkIaqSensorStatus(capteurBME680);
  bsec_virtual_sensor_t sensorList[10] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  }; 

  capteurBME680.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP); 
  checkIaqSensorStatus(capteurBME680);
  
  /*Partie initialisation Timer1 : */
  
  noInterrupts();
  TCCR1A = 0B00000000; // Mode normal
  TCCR1B = 0B00000000; // Timer1 arreté
  TCCR1C = 0B00000000;
  TIFR1 |= 0B00000001; // Mise à 1 du bit TOV1
  TIMSK1 |= 0B0000001; // Mise à 1 du bit TOEI1 pour autoriser les IT timer 1
  TCNT1 = BASE_TEMPS_TIMER1_05s;
  interrupts();
  TCCR1B |= 0B00000101; //demarre à 1024
  Serial.println("Initialisation du timer1 : done");
} 
/*--------------------------------------------------------------------------------------------*/
void loop() 
{
  
  Horloge H;
  Bsec rafraichissement;
  H = getDateDs1307();
  Affiche_date_heure(H);
  bool synchro = false;
  
  /*while(synchro == false && strcmp(msgFromGpsParser.GPRMC.id,"$GPRMC")==1)
  {
    Serial.println("On est dans la boucle : ");
    buffer2 = GetGPS_MSG();
    msgFromGpsParser = GPS_msg_parse(buffer2);
    synchro = Test_Synchro_GPS(msgFromGpsParser);
    if(synchro == true && strcmp(msgFromGpsParser.GPRMC.id,"$GPRMC") == 1)
    {
      Serial.println("WOWOWOWOWO : ");
      //H = getDateDs1307();
      H = Extract_date_heure_from_GPS(msgFromGpsParser.GPRMC.date,msgFromGpsParser.GPRMC.UTCtime);
      Affiche_date_heure(H);
    }
  }*/
  
  if (T_Time_Out_Evenement1 <= 0)
  {
    
    buffer2 = GetGPS_MSG();
    msgFromGpsParser = GPS_msg_parse(buffer2);
    synchro = Test_Synchro_GPS(msgFromGpsParser);
    if(synchro == true)
    {
      H = Extract_date_heure_from_GPS(msgFromGpsParser.GPRMC.date,msgFromGpsParser.GPRMC.UTCtime);
      setDateDs1307(H);
    } 
    T_Time_Out_Evenement1 = T_EVNT1;*/
  //}
  Serial.println("______________________en attente________________________");
  
  if (T_Time_Out_Evenement2 <= 0)
  {
    Serial.print("Dans Evenement 2");
    affichage_Valeur_BME680(capteurBME680);
    T_Time_Out_Evenement2 = T_EVNT2;
    
  }
  delay(1000);

}
