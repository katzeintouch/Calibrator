int sensorPin = 0;  // Analogeingang Pin = 0
float Batteriespannung;
String Utemp;       // Speicher für String aus Spannung


/*
void Spannung()
{
sensorValue = analogRead(sensorPin);
Batteriespannung = sensorValue * 13.867/ 1000.0 ; // Spannung in V
// return sensorValue;
}
*/
void Spannung()     // Batteriespannung messen
{
  Batteriespannung = analogRead(sensorPin) * 13.867/ 1000.0 ; // Wert einlesen
  Utemp = String(Batteriespannung, 2);     // String aus float mit 2 Kommastellen erzeugen
  Utemp = Utemp + "V";                     // Wert und Einheit zusammenfügen
}
