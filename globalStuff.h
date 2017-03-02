// Declare Prototypes wg. Reihenfolge der Functionen bei #include
void handleRootPage() ;      // in stuffWeb.h
void handleNotFound();       // in stuffWeb.h

ESP8266WebServer server(80);

// GLOBALE VARIABLEN

const char *ssid = "Kalibrator_Ap";
const char *password = ""; // leeres Passwort oder mindestens 8 Zeichen

unsigned long       lastConnectionTime  = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval     = 60L * 1000L; // delay between updates, in milliseconds // the "L" is needed to use long type numbers
//bool newData = false ;                                 // wurden neue Daten vom Fronius geholt?
String lastStatus ;                                    // zur Anzeige im Browser

void Initialisierung() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRootPage);
  server.begin();
  Serial.println("HTTP server started");


  server.on("/", handleRootPage);     // in stuffWeb.h
  server.onNotFound(handleNotFound);  // in stuffWeb.h

  // OTA --------------------------------------------------------------------
  // binary für OTA-Upload in Arduino IDE über "Sketch-> Export compiled Binary" (Strg+Alt+S) erzeugen. Vorher "Speichern" (Strg+S) nicht vergessen!
  // Datei liegt dann als *.bin im SketchVerzeichnis und kann hochgeladen werden.
  server.on ("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", (Update.hasError()) ? "Flash Update FAIL ! :-( " : "Flash Update successfully :-)) Wait for Restart ESP8266-Module. Open " + WiFi.localIP().toString() + " in a few seconds again.");
    WiFi.disconnect();
    Serial.println("Go for RESTART NOW!!!");
    Serial.flush();
    delay(1000);
    ESP.restart();
    while (1) {
      delay(1);
    };
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.setDebugOutput(true);
#if defined(WifiUDP)
      WiFiUDP::stopAll();
#endif
      Serial.printf("Update with - %s\n", upload.filename.c_str());
      uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
      if (!Update.begin(maxSketchSpace)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success :-)). %u Bytes uploaded.\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
      Serial.setDebugOutput(false);
    }
    yield();
    delay(0);
  });
  // OTA ENDE --------------------------------------------------------------------

  server.begin();

  lastStatus = "Neustart";
  lastConnectionTime = millis() + postingInterval ;   // für den ersten Durchlauf sofort nach dem Booten
}

