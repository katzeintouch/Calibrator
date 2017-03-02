void handleRootPage() {

// Wie lange ist der Chip OnLine? An Hand der millis() ausrechnen
// Is nur ein Anhaltswert, da millis() irgendwann (googeln) überlaufen und von vorne anfangen zu zählen
  int secs = millis() / 1000;
  int minu = secs / 60;
  int hr = minu / 60;
  char upTimeBuffer[20];
  snprintf ( upTimeBuffer, 20,"<h2>Uptime: %02d:%02d:%02d",hr, minu % 60, secs % 60);
// Ende UpTime  

  String s  = F("<!DOCTYPE html>\n<html>\n<head>\n<title>Kalibratore</title>\n"
         //"<!-- favicon gleich in Seite eingebaut -->"
         "<link href='data:image/x-icon;base64,AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAA"
         "AAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAAXl5eAHp6egAAzP8A4P/7AAD/8gAA8v8AAN3/AAAAAAAAAAAAAAA"
         "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAARAAAAAAAAAREQAAAAAAACIiAAAAAAAAEREAAAAAAAAiIgAAAAAAAWZ"
         "zEAAAAAABZnMQAAAAABZmczEAAAABZlVnMxAAAAFlVVZzEAAAAVREVnMQAAABVERWcxAAAAFURFZzEAAAABVVVnE"
         "AAAAAAREREAAAAAAAAAAAAAD+fwAA/D8AAPw/AAD8PwAA/D8AAPgfAAD4HwAA8A8AAOAHAADgBwAA4AcAAOAHAAD"
         "gBwAA8A8AAPgfAAD//wAA' rel='icon' type='image/x-icon' />\n"
         //"<!-- /favicon -->"
         // AutoRefresh WebSeite alle XX Sekunden
         "<meta http-equiv='refresh' content='10'>"
         // AutoRefresh Ende
         "<meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=yes'>\n"
         "</head>\n"
         "<body bgcolor='#d0d0f0'>\n"
         "<h1><b>Kalibrator</b></h1>\n");
         s += upTimeBuffer ;          
//         s += F("</h2>Fronius-IP:"); s += ( froniusIP.toString() );
//         s += F("<br>\nS7-IP:"); s += ( s7IP.toString() );
         s += F("<br>\nIstwert   : "); s += mittelwert ; s += F(" Grad Celsius");
         s += F("<br>\nSollwert : "); s += Setpoint ; s += F(" Grad Celsius");
         s += F("<br>\nStellwert: "); s += Output ; s += F(" Digit");
         s += F("<br>\nSpannung: "); s += Batteriespannung ; s += F(" Volt");
         s += F("<br><br>\nLetzter Status: ") ; s += lastStatus ;

         // OTA Buttons - Anzeige nur wenn FLASH > 1MB
         if(ESP.getFlashChipRealSize()>1024000) {
            s += F("<br><br>\n<h3><b>OTA ");
            s += F("<form method='POST' action='/update' enctype='multipart/form-data'>\n<input type='file' name='update'><input type='submit' value='Update'>\n</form>");
            s += F("</b></h3>\n");
         }
         
         s += F("\n</body>\n</html>");
  
  server.send(200, "text/html", s );
}

void handleNotFound(){
  String s = F("<h1>File Not Found</h1>\n\n");
  s += "URI: ";  s += server.uri();
  server.send(404, "text/plain", s );
}

