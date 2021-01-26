#include "GPS.h"
#include <Arduino.h>
#include "RTC_DS1307.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial1.begin(9600);
  beginGPS();
  Choix_Msg_NMEA(2);
  
  //Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"); // GPRMC
  //Serial1.write("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"); //GPGGA
  //Serial1.println(Serial1.read());
  char test[200];
  NMEA Parser ;
  GetGPS_MSG();
  /*Parser = */GPS_msg_parse();
  Test_Synchro_GPS();
  
  Serial.println("____________________fin init____________________"); 
}

void loop() 
{
  //char test[100];
  // put your main code here, to run repeatedly:
  //Serial1.read();
  //Serial.println("___________________________________");
  Horloge Test;
  char test[200];
  NMEA Parser ;
  GetGPS_MSG();
  //Serial.print("test = "); Serial.println(test);
  /*Parser = */GPS_msg_parse();
  //Serial.print(" Parser.GPRMC.id = ");Serial.println(Parser.GPRMC.id);
  //Parser = recupParse();
  Test = Extract_date_heure_from_GPS(/*Parser.GPRMC.date,Parser.GPRMC.UTCtime*/);
  //Test.D.jour_semaine = jour_semaine( Test.D.jour_mois,Test.D.mois,Test.D.annee+2000);
  //Test_Synchro_GPS();
  //resetBuffer(test);
   setDateDs1307(Test);
  Affiche_date_heure(Test);
  //Affiche_date_heure(Test);
  Serial.println("    ");
  Serial.println("___________________________________");
  //delay(1000);
}
