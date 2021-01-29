// Fichier Affichage.cpp

// Routines d'affichage sur le terminal série
//   Affichage de la date et de l'heure sur terminal série
//   Affichage Indicateur Ete-Hiver sur le terminal série
//   Affichage Ville de référence fuseau horaire sur le terminal série
//   Affichage Indicateur de synchro sur le terminal série
//   Affichage des mesures du capteur BME680 sur le terminal série
//   Affichage de l'historique des mesures de valeur moyenne de pression atmosphérique sur le terminal série

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h>
/*Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void graphiqueMoyennePression()
{
  tft.drawLine(10, 479, 306, 479, RED);
}*/
