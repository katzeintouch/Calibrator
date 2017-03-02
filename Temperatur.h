String Ttemp;       // Speicher für String aus Temperatur

void Temperatur()   // Temperatur umrechnen
{
  Ttemp = String(mittelwert, 2);         // String aus float mit 2 Kommastellen erzeugen
  Ttemp = Ttemp + "°C";                   // Wert und Einheit zusammenfügen
}
