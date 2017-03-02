/********************************************************
 * PID Adaptive Tuning Example
 * One of the benefits of the PID library is that you can
 * change the tuning parameters at any time.  this can be
 * helpful if we want the controller to be agressive at some
 * times, and conservative at others.   in the example below
 * we set the controller to use Conservative Tuning Parameters
 * when we're near setpoint and more agressive Tuning
 * Parameters when we're farther away.
 ********************************************************/

#include <PID_v1.h>
#define PIN_OUTPUT 15

double gap;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=36, aggKi=2.0, aggKd=0;
double consKp=18, consKi=1.0, consKd=0.0;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void Regler()
{
    Input = mittelwert;         // aus Dallas.h
  gap = abs(Setpoint-Input);  // Abstand Sollwert - Istwert 
  if (gap < 5.0)
  {  
    myPID.SetTunings(consKp, consKi, consKd);    //bei kleiner Differenz konservative Reglerparameter nutzen
  }
  else
  {
    myPID.SetTunings(aggKp, aggKi, aggKd);      //bei großer Differenz agressive Reglerparameter nutzen
  }

  myPID.Compute();
//  Serial.print(Output);
   if ((Batteriespannung > 11.5) and (mittelwert > 5.0) and (mittelwert < 32.0))    // wenn der Akku geladen ist und der Mittelwert der Temperatur < als 32.0 Grad,
  {  Output = Output;    // Output vom Regler
  }
  else                            // ansonsten
  { Output = 0;        // Output = 0
  }
    
  Output = Output * 4;
  analogWrite(PIN_OUTPUT, Output);
}


