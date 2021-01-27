#include "BME680_Sensor.h"
#include <Arduino.h>


Bsec Test;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("TestSD");
  
  //beginBME680(Test);
  Wire.begin();
  Test.begin(BME680_I2C_ADDR_PRIMARY, Wire);
  checkIaqSensorStatus(Test);
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

  Test.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP); 
  checkIaqSensorStatus(Test);
  
  Serial.println("TestSF");
}

void loop() {
  // put your main code here, to run repeatedly:
  
   Serial.println("TestLD");
   //Bsec Test;
   //unsigned long time_trigger = millis();
   affichage_Valeur_BME680(Test);
   Serial.println("TestLF");
   delay(1000);
}
