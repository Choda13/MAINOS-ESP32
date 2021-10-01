#include <iostream>
#include <Arduino.h>
#include "MAINOS.h"
#include "LedAPI/LedAPI.h"

LedAPI::LedAPI Led();

void setup()
{
    Serial.begin(115200);
    mainos_init();
}

void loop()
{
    delay(10);
}
