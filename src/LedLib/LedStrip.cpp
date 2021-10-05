#include "LedLib/LedStrip.h"
#include "LedLib/LedLib.h"
#include "TypeConversions/TypeConversions.h"
#include <Arduino.h>

LedStrip::LedStrip(uint8_t dataPin)
{
    this->dataPin = dataPin;
    controller = LedLib::CreateController(dataPin);
    FastLED.addLeds(controller, pixels.data(), pixels.size());
}
LedStrip::LedStrip(uint8_t dataPin, int numOfLeds){
    this->dataPin = dataPin;
    controller = LedLib::CreateController(dataPin);
    pixels = std::vector<CRGB>(numOfLeds, CRGB::Black);
    FastLED.addLeds(controller, pixels.data(), pixels.size());
}
LedStrip::LedStrip(uint8_t dataPin, std::vector<CRGB> data)
{
    this->dataPin = dataPin;
    controller = LedLib::CreateController(dataPin);
    pixels = data;
    FastLED.addLeds(controller, pixels.data(), pixels.size());
}
LedStrip::LedStrip(uint8_t dataPin, CRGB *data, int numOfLeds)
{
    this->dataPin = dataPin;
    controller = LedLib::CreateController(dataPin);
    pixels = std::vector<CRGB>(dataPin, numOfLeds);
    FastLED.addLeds(controller, pixels.data(), pixels.size());   
}

CRGB& LedStrip::at(unsigned int index)
{
    return pixels.at(index);
}
unsigned int LedStrip::size()
{
    return pixels.size();
}
std::string LedStrip::toString()
{
    std::string result="";
    result+="\nData pin: " + TypeConversions::int_to_string(this->dataPin);
    result+="\nNum. of pixels: " + TypeConversions::int_to_string(this->pixels.size());
    result+="\n";
    return result;
}

void LedStrip::updatePixels(){
    controller->setLeds(pixels.data(), pixels.size());
}

void LedStrip::addPixel(CRGB color)
{
    pixels.push_back(color);
    updatePixels();
}
void LedStrip::addPixel(CHSV color){
    CRGB rgb;
    CHSV hsv = color;
    hsv2rgb_rainbow(hsv, rgb);
    addPixel(rgb);
}

void LedStrip::removePixel()
{
    pixels.pop_back();
    updatePixels();
}
void LedStrip::removePixel(unsigned int index)
{
    if(index >= pixels.size())
        return;
    pixels.erase(pixels.begin()+index);
    updatePixels();
}

void LedStrip::show()
{
    controller->showLeds(255);
}
void LedStrip::show(CRGB color)
{
    controller->showColor(color);
}
void LedStrip::show(std::vector<CRGB> data)
{
    controller->show(data.data(), data.size(), 255);
}
void LedStrip::show(CRGB* data, int numOfLeds)
{
    controller->show(data, numOfLeds, 255);
}