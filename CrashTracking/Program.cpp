#include <Arduino.h>
#include "ApplicationMonitor.h"

Watchdog::CApplicationMonitor ApplicationMonitor;

// An LED to flash while we can. 
const int gc_nLEDPin = 13;

// countdown until the program locks up. 
int g_nEndOfTheWorld = 15; 

// number of iterations completed. 
int g_nIterations = 0;     

void setup()
{
  Serial.begin(9600);
  pinMode(gc_nLEDPin, OUTPUT);
  Serial.println("Ready");

  ApplicationMonitor.Dump(Serial);
  ApplicationMonitor.EnableWatchdog(Watchdog::CApplicationMonitor::Timeout_4s);
  //ApplicationMonitor.DisableWatchdog();

  Serial.println("Hello World!");
}

void loop()
{
  ApplicationMonitor.IAmAlive();
  ApplicationMonitor.SetData(g_nIterations++);

  Serial.println("The end is nigh!!!");

  digitalWrite(gc_nLEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);               // wait for a second
  digitalWrite(gc_nLEDPin, LOW);    // turn the LED off by making the voltage LOW
  delay(200);               // wait for a second

  if (g_nEndOfTheWorld == 0)
  {
    Serial.println("The end is here. Goodbye cruel world.");
    while(1)
      ; // do nothing until the watchdog timer kicks in and resets the program. 
  }

  --g_nEndOfTheWorld;
}