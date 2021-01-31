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
Bsec BME680;

void checkIaqSensorStatus(Bsec verif)
{
  String output;
  if (verif.status != BSEC_OK)
  {
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
    if (verif.bme680Status < BME680_OK) 
    {
      output = "BME680 error code : " + String(verif.bme680Status);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } 
    
    else
    {
      output = "BME680 warning code : " + String(verif.bme680Status);
      Serial.println(output);
    }
  }
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

void beginBME680()
{
  Wire.begin();
  
  BME680.begin(BME680_I2C_ADDR_PRIMARY, Wire);
  checkIaqSensorStatus(BME680);
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
   checkIaqSensorStatus(BME680);
   
  BME680.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);   
  checkIaqSensorStatus(BME680);
}

void affichage_Valeur_BME680(Bsec * val)
{
    if (val->status == BSEC_OK) // If new data is available
    { 
      Serial.print("La pression vaut : ");Serial.print(val->pressure/100);Serial.println(" hPa");
      Serial.print("Le taux d'humidité vaut : ");Serial.print(val->humidity);Serial.println("%");
      Serial.print("Le l'IAQ vaut : ");Serial.println(val->iaq);
      Serial.print("L' iaqAccuracy vaut : ");Serial.println(val->iaqAccuracy);
      Serial.print("La température vaut : ");Serial.print(val->rawTemperature);Serial.println("°C");
      Serial.print("Le taux de CO2 vaut : ");Serial.print(val->co2Equivalent);Serial.println("ppm");
      Serial.print("Le taux de COV vaut : ");Serial.print(val->breathVocEquivalent);Serial.println("ppm");
    } 
    else 
    {
      Serial.println("val->statut : Erreur ");
    }  
}

Bsec * getBME680()
{
    if (BME680.run()) // If new data is not available
    {
       return &BME680;
    }
} 
