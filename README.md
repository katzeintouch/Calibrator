# Calibrator
The calibrator generates heat to calibrate thermometers for building automation.
A aluminium cylinder with a diameter of 60mm and a height of 100mm includes two 
onewire digital Dallas thermometers, a elektrical heating and a drill hole for the thermometer probe.
The two thermometers were added and then divided by 2. This ist the actual temperature input signal for
the esp8266 PI controller. The set value is given fix in esp code. 
The control value fired a heating coil arround the cylinder. So the temperatur for the probe is constant
The eps8266 generates a WIFI access point. 
A lokal oled displays and a web site shows the actual, the desired temperatur, and the control value.
