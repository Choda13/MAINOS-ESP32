#pragma once
#include "FastLED.h"
#include <vector>
#include <string>

//TODO: Return something meaningful instead of void
class LedStrip
{
public:
    uint8_t dataPin;
    std::vector<CRGB> pixels;
    CLEDController* controller;
    
    LedStrip(uint8_t dataPin);
    LedStrip(uint8_t dataPin, int numOfLeds);
    LedStrip(uint8_t dataPin, std::vector<CRGB> data);
    LedStrip(uint8_t dataPin, CRGB* data, int numOfLeds);
    //~LedStrip(){delete controller;}
    //LedStrip() with chipset option

    CRGB& at(unsigned int index);
    std::string toString();
    unsigned int size();

    void updatePixels();

    void addPixel(CRGB color=CRGB::Black);
    void addPixel(CHSV color);

    void removePixel();
    void removePixel(unsigned int index);

    void show();
    void show(CRGB color);
    void show(std::vector<CRGB> data);
    void show(CRGB* data, int numOfLeds);
    
    void show(CHSV color);
    void show(std::vector<CHSV> data);
    void show(CHSV* data, int numOfLeds);
};