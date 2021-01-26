// Fichier TFT_Affichage.h
// Spécifique à l'écran TFT Adafruit 2050

//#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "RTC_DS1307.h"


#define LCD_CS A0 // Chip Select goes to Analog 3
#define LCD_CD A1 // Command/Data goes to Analog 2
#define LCD_WR A2 // LCD Write goes to Analog 1
#define LCD_RD A3 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin



// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void TFT_Affichage_Date(Horloge H, Horloge P);
void TFT_Affiche_Heure(Horloge H, Horloge P);
void TFT_Affiche_EteHiv(char * EteHiv, char * EteHivPres);

void TFT_setup();
// Définition de type de données


// Définition de constantes symboliques

/*--------------------------------------------------------------------------------*/
// Spécifique au shield écran TFT + dalle tactile Adafruit_2050_TFT
// Arduino Mega2560, mode Data parallèle

// Broches de contrôle écran TFT


/*----------------------------------------*/
// Fonctions prototypes pour affichage graphique
