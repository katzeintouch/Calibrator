#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 2
#define ONE_WIRE_BUS_2 0                    // Data wire is plugged into port 0 und 2 on the Arduino

float temp1 = 0;
float temp2 = 0;
float summe = 0;
float mittelwert = 0;

OneWire oneWire_1(ONE_WIRE_BUS_1);          // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire_2(ONE_WIRE_BUS_2);

DallasTemperature sensor_eins(&oneWire_1);  // Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensor_zwei(&oneWire_2);

void Werte()
{
  sensor_eins.requestTemperatures(); // Send the command to get temperatures
  sensor_zwei.requestTemperatures();
 
  temp1 = sensor_eins.getTempCByIndex(0);
  temp2 = sensor_zwei.getTempCByIndex(0);
  summe = temp1 + temp2;
  mittelwert = summe / 2;
}
