// Fichier BME680_Sensor.cpp
// Fonctions de gestion du capteur BME680
// Acquisition des mesures depuis le capteur BME680
// - Température en °C dans [-40.0; 80.0]
// - Pression en hPa dans [900.00; 13000.00]
// - Humidité en % dans [0.0; 100.0]
// - IAQ : mesure dans [0.0; 500.0] (IAQ ; Index Air Quality)
// - IAQ_Acc : valeur dans {0, 1, 2, 3} (Précision de la mesure de l'Index Air Quality)
// - CO2 en ppm (Concentration en CO2)
// - COV en ppm (Concentration des Composés Organo Volatiles)

#include <Arduino.h>
#include "BME680_Sensor.h"


void checkIaqSensorStatus(Bsec verif)
{
  Serial.println("Début_fonction_Check");
  String output;
  if (verif.status != BSEC_OK)
  {
    Serial.println("entrer1B");
    if (verif.status < BSEC_OK) {
      output = "BSEC error code : " + String(verif.status);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      output = "BSEC warning code : " + String(verif.status);
      Serial.println(output);
    }
  }

  if (verif.bme680Status != BME680_OK) 
  {
    Serial.println("entrer2B");
    if (verif.bme680Status < BME680_OK) 
    {
      output = "BME680 error code : " + String(verif.bme680Status);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } 
    
    else
    {
      Serial.println("entrerElseB");
      output = "BME680 warning code : " + String(verif.bme680Status);
      Serial.println(output);
    }
  }
  Serial.println("FINNNN_fonction_check");
}

void errLeds(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("ErreurLedClignote");
}

void beginBME680(Bsec Start)
{
  Start.begin(BME680_I2C_ADDR_PRIMARY, Wire);
  Serial.println("fin_init");
  //Start.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP); 
  //checkIaqSensorStatus(Start);
}

void affichage_Valeur_BME680(Bsec val)
{
    Serial.println("DébutAffichage");
    //val.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
    if (val.run()) // If new data is available
    { 
      Serial.println("val.run : ok !!!!");
      Serial.print("La pression vaut : ");Serial.println(val.pressure);
      Serial.print("Le taux d'humidité vaut : ");Serial.println(val.humidity);
      Serial.print("Le l'IAQ vaut : ");Serial.println(val.iaq);
      Serial.print("L' iaqAccuracy vaut : ");Serial.println(val.iaqAccuracy);
      Serial.print("La température vaut : ");Serial.println(val.rawTemperature);
      Serial.print("Le taux de CO2 vaut : ");Serial.println(val.co2Equivalent);
      Serial.print("Le taux de COV vaut : ");Serial.println(val.breathVocEquivalent);
    } 
    else 
    {
      Serial.println("VAl.run : is not good fdp");
      Serial.println("CheckDébut");
      checkIaqSensorStatus(val);
      Serial.println("CheckRéussi");
    }  
    Serial.println("FIN_Affichage");
}
