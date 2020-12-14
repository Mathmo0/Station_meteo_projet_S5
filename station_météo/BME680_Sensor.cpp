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
