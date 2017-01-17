
/*
  Potentiometer from Hardware pushed to Blynk, Analog input, analog output, serial output

 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example shows how to push the value from a Potentiometer
 * to Blynk using a Value Display Settings Widget on the App.
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************
 *            USB HOWTO: http://tiny.cc/BlynkUSB

 Reads an analog input pin in a range from 0 to 1023
 
 The circuit:
 * potentiometer connected to 5V and Ground.
   Center pin of the potentiometer goes to the analog pin A0.

 created 17 Dec. 2017 by Yoimer Román from Next-Wells.

 This example code is in the public domain.

 */


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#define BLYNK_PRINT Serial
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>
#include <SimpleTimer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

// Type here your AuthToken. Please keep the quotes.
//It should be something like "369505e836ed435abe9c7e9db2db5471", not 369505e836ed435abe9c7e9db2db5471

char auth[] = "369505e836ed435abe9c7e9db2db5471";

/***************************************************** Variables Declaration ********************************************************/

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot

/***************************************************** Functions *******************************************************************/

/***************************Timer***************/

SimpleTimer timer;
// This function sends Arduino's up time every second to Virtual Pin (5) and Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  // Writing in virtual pin V10 the real value from pot saved in sensorValue
  
  Blynk.virtualWrite(V10, sensorValue); 
  
} 



void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

}

void loop()
{

  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  Blynk.run();
  
  timer.run(); // Initiates SimpleTimer
}

/****************Writing from server************/
/*

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 2
BLYNK_WRITE(V13)
{
  ////int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V13 Slider value is: ");
  Serial.println(pinValue);
}

*/



// These constants won't change.  They're used to give names
// to the pins used:
//// const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//// const int analogOutPin = 9; // Analog output pin that the LED is attached to

//// int sensorValue = 0;        // value read from the pot
//// int outputValue = 0;        // value output to the PWM (analog out)

//// int ledPin = 13;      // select the pin for the LED

/*

void setup() {
  
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

*/

/*

void loop() {
  
  Blynk.run();
   
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

 // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  V13 = ledPin;

// stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  
 // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
  
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("sensor = " );
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}

*/
