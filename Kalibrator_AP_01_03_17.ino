/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "Spannung.h"
#include "Dallas.h"
#include "Pid.h"
#include "globalStuff.h"
#include "stuffWeb.h"
#include "Temperatur.h"
#include "Y.h"
#include "Oled_1.3.h"

void setup()
{
  Initialisierung();         // globalStuff.h
  display.init();            // Initialising Oled Display ,the UI will init the display too.
  Serial.begin(115200);       // start serial port

  // für Thermometer
  sensor_eins.begin();        // Start up the library
  sensor_zwei.begin();        // Start up the library

  //für PID Regler
  Setpoint = 27.0;
  myPID.SetMode(AUTOMATIC);   // Regler einschalten
  myPID.SetOutputLimits(0, 50); // Ausgangswert begrenzen
}

void loop()
{
  Werte();                  // Thermometer auslesen
  Regler();                 // PID Regler
  Spannung();               // Batteriespannung einlesen
  Temperatur();             // Temperatur bearbeiten
  Stellwert();              // Stellwert bearbeiten

  server.handleClient();    // Haben wir eine BrowserAnfrage?

  display.clear();  // clear the display
  Textausgabe();    // Texte in Puffer schreiben
  display.display();// Pufferinhalt zum Display schreiben

  Serial.print("   Istwert:  "); Serial.print(mittelwert);
  Serial.print("   gap:  "); Serial.print(gap);
  Serial.print("   Sollwert: "); Serial.print(Setpoint);
  Serial.print("   Y:   "); Serial.print(Output);
  Serial.print("   Spannung:   "); Serial.println(Batteriespannung);
}





