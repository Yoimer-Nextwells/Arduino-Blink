
/*
  Potentiometer from Hardware pushed to Blynk using Analog Input A0.
  Also Pushing Virtual Pins with simulated values of Temperature and Humidity

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
 * It also pushes to variables as Temperature and Humidity updating(incremeted) by float variables.
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
float temp = 1.10; // Virtual Temperature
float humd = 0.0;  // Virtual Humidity

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
  // This function sends Arduino's up time every second to Virtual Pin (5), Virtual Pin (1) and Virtual Pin(10).
  // In the app, Widget's reading frequency should be set to PUSH. This means
  // that you define how often to send data to Blynk App.
  
  // Writing in virtual pin V10 the real value from pot saved in sensorValue
  Blynk.virtualWrite(V10, sensorValue); 
  
  temp += 0.25; // Increment the temperature by 0.25 Celsius degree
  humd += 0.5;  // Increment Humidity by 0.5 %
  Blynk.virtualWrite(V5, temp);    // Reading temperature on Blynk App
  Blynk.virtualWrite(V1, humd);    // Reading humidity on Blynk App
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

