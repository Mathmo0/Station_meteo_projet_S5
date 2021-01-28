#include "GPS.h"
int k = 0;
int testH = 0;
extern int Parse;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  beginGPS();
  beginDs1307();
  Horloge H;
  NMEA test;
  char * buffer;
  Choix_Msg_NMEA(2);
  H.H.seconde = 0;
  H.H.minute = 0;
  H.H.heure = 0;
  
  H.D.jour_mois = 1;
  H.D.mois =  1;
  H.D.annee = 10;
  H.D.jour_semaine = jour_semaine( H.D.jour_mois,H.D.mois,H.D.annee);
  setDateDs1307(H);
  //Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"); // GPRMC
  //Serial1.write("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"); //GPGGA
}

void loop() {
  Horloge H;
  NMEA test;
  char * buffer;
  //if(Test_Synchro_GPS(test) == false)
  //{
    buffer = GetGPS_MSG();
    test = GPS_msg_parse(buffer);
  //}
  
  //else if(Test_Synchro_GPS(test) == true){
  
  H = Extract_date_heure_from_GPS(test.GPRMC.date,test.GPRMC.UTCtime);
  //H = getDateDs1307();
  //Affiche_date_heure(H);
  //k++;
  //}
  /*if(k>0)
  {
    //delay(1000);
    Serial.print("k = ");Serial.println(k);
    Affiche_date_heure(H);
  }*/
  //delay(1000);
  //Serial.println("Après return : ");Serial.println(buffer);
  //test =  GPS_msg_parse(buffer);
  /*Serial.print(" H.H.heure[0] = ");Serial.println(test.GPRMC.UTCtime);
  Serial.print(" H.H.heure[0] = ");Serial.println(test.GPRMC.UTCtime[0]);
  Serial.print(" H.H.heure[1] = ");Serial.println(test.GPRMC.UTCtime[1]);
  Serial.print(" H.H.heure[2] = ");Serial.println(test.GPRMC.UTCtime[2]);
  Serial.print(" H.H.heure[3] = ");Serial.println(test.GPRMC.UTCtime[3]);
  Serial.print(" H.H.heure[4] = ");Serial.println(test.GPRMC.UTCtime[4]);
  Serial.print(" H.H.heure[5] = ");Serial.println(test.GPRMC.UTCtime[5]);*/

  /*if(testH >= 1)
  {
    //testH=0;
    H = Extract_date_heure_from_GPS(test.GPRMC.date,test.GPRMC.UTCtime);
  }*/
  
  //Serial.print(" H.H.heure = ");Serial.println(H.H.heure);
  /*Serial.print(" test.GPRMC.id = ");Serial.println(test.GPRMC.id);
  Serial.print(" test.GPRMC.UTCtime = ");Serial.println(test.GPRMC.UTCtime);
  Serial.print(" test.GPRMC.statut = ");Serial.println(test.GPRMC.statut);
  Serial.print(" test.GPRMC.latitude = ");Serial.println(test.GPRMC.latitude);
  Serial.print(" test.GPRMC.indicateurLatitute = ");Serial.println(test.GPRMC.indicateurLatitute);
  Serial.print(" test.GPRMC.longitude = ");Serial.println(test.GPRMC.longitude);
  Serial.print(" test.GPRMC.indicateurLongitude = ");Serial.println(test.GPRMC.indicateurLongitude);
  Serial.print(" test.GPRMC.date = ");Serial.println(test.GPRMC.date);
  Serial.print(" test.GPRMC.mode = ");Serial.println(test.GPRMC.mode);*/

  /*Serial.print(" test.GPGGA.id = ");Serial.println(test.GPGGA.id);
  Serial.print(" test.GPGGA.positionIndicator = ");Serial.println(test.GPGGA.positionIndicator);
  Serial.print(" test.GPGGA.mslAltitude = ");Serial.println(test.GPGGA.mslAltitude);*/

  /*Serial.print(" test.PMTK.id = ");Serial.println(test.PMTK.id);
  Serial.print(" test.PMTK.cmd = ");Serial.println(test.PMTK.cmd);
  Serial.print(" test.PMTK.flag = ");Serial.println(test.PMTK.flag);*/
  
  Serial.println("______________");
  // put your main code here, to run repeatedly:

}
