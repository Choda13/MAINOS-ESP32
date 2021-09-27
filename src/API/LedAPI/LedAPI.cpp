#include "../include/API/LedAPI/LedAPI.h"
#include "FastLED.h"

LedAPI::LedAPI(){
    this->leds = std::vector<CRGB>(30);
    FastLED.addLeds<NEOPIXEL, 4>(leds.data(), leds.size());
}

void LedAPI::show(){
    FastLED.show();
}

