#include "../include/LedLib/LedStrip.h"
#include "../include/MAINOS.h"
#include <WebServer.h>
#include <Arduino.h>
#include <iostream>
#include <WiFi.h>

/*Put your SSID & Password*/
const char *ssid = "Test"; // Enter SSID here
const char *password = "Test";   //Enter Password here

LedStrip strip(5, 60);

void setup()
{
    Serial.begin(115200);
    strip.show();
    mainos_init();
}

void loop()
{
    delay(10);
}
