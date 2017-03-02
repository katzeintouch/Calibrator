String Ytemp;       // Speicher für String aus Temperatur

void Stellwert()   // Stellwert bearbeiten
{
  Ytemp = String(Output,0);         // String aus float mit 2 Kommastellen erzeugen
  Ytemp = Ytemp + " Digit";                   // Wert und Einheit zusammenfügen
}
