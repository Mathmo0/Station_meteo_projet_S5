#include "GPS.h"
#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  beginGPS();
  //char test[200];
  Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"); // GPRMC
  //Serial1.write("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"); //GPGGA
  //Serial1.println(Serial1.read());
  GetGPS_MSG();
  GPS_msg_parse();
  Test_Synchro_GPS();
  Serial.println("____________________fin init____________________"); 
}

void loop() 
{
  //char test[100];
  // put your main code here, to run repeatedly:
  //Serial1.read();
  //Serial.println("___________________________________");
  char test[200];
  GetGPS_MSG();
  GPS_msg_parse();
  //Test_Synchro_GPS();
  //resetBuffer(test);
  Serial.println(" ");
  Serial.println("___________________________________");
  //delay(1000);
}
