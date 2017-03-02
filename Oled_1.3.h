// Notwendige Bibliotheken einbinden
#include "OLEDDisplayUi.h"
#include "SH1106Wire.h"

// Display Einstellungen
const int I2C_DISPLAY_ADDRESS = 0x3c;   // I2C Adresse (mit Scanner ermitteln)
const int SDA_PIN = 4;                  // GPIO4
const int SDC_PIN = 5;                  // GPIO5

// OLED display initialisieren
SH1106Wire  display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
OLEDDisplayUi ui     ( &display );



void Textausgabe()
{
  display.setFont(ArialMT_Plain_16); // Schriftart und Schriftgrösse  10, 16 und 24 möglich
  display.drawString(0, 0, "Spann.:"); // oben links
  display.drawString(78, 0, Utemp);
  display.drawString(0, 18, "Temp.:");
  display.drawString(55, 18, Ttemp);
  display.drawString(0, 36, "Y:");
  display.drawString(52, 36, Ytemp);
}


