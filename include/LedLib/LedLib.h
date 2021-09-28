#pragma once
#include "FastLED.h"
#include "LedStrip.h"
#include <vector>

namespace LedLib
{
    CLEDController *CreateController(uint8_t dataPin);

    //TODO: Return something meaningful instead of void
    class Led
    {
    public:
        std::vector<LedStrip> strips;

        Led();
        Led(LedStrip strip);
        Led(uint8_t dataPin);
        Led(std::vector<LedStrip> strips);
        Led(LedStrip* strips, unsigned int numOfStrips);
        
        void addStrip(uint8_t dataPin);
        void addStrip(uint8_t dataPin, std::vector<CRGB> leds);
        void addStrip(uint8_t dataPin, CRGB *leds, unsigned int numOfLeds);
        void addStrip(uint8_t dataPin, unsigned int numOfLeds, CRGB color = CRGB::Black);

        void removeStrip();
        void removeStrip(unsigned int index);

        void show();
        void show(CRGB color);
        void show(unsigned int index);
        void show(unsigned int index, CRGB color);
    };
};