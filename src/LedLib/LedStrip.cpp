#include "../../include/LedLib/LedStrip.h"
CLEDController *CreateController(uint8_t dataPin)
{
    CLEDController *ptr;
    switch (dataPin)
    {
    case 1:
        ptr = new NEOPIXEL<1>();
        break;
    case 2:
        ptr = new NEOPIXEL<2>();
        break;
    case 3:
        ptr = new NEOPIXEL<3>();
        break;
    case 4:
        ptr = new NEOPIXEL<4>();
        break;
    case 5:
        ptr = new NEOPIXEL<5>();
        break;
    case 6:
        ptr = new NEOPIXEL<6>();
        break;
    case 7:
        ptr = new NEOPIXEL<7>();
        break;
    case 8:
        ptr = new NEOPIXEL<8>();
        break;
    case 9:
        ptr = new NEOPIXEL<9>();
        break;
    case 10:
        ptr = new NEOPIXEL<10>();
        break;
    case 11:
        ptr = new NEOPIXEL<11>();
        break;
    case 12:
        ptr = new NEOPIXEL<12>();
        break;
    case 13:
        ptr = new NEOPIXEL<13>();
        break;
    case 14:
        ptr = new NEOPIXEL<14>();
        break;
    case 15:
        ptr = new NEOPIXEL<15>();
        break;
    case 16:
        ptr = new NEOPIXEL<16>();
        break;
    case 17:
        ptr = new NEOPIXEL<17>();
        break;
    case 18:
        ptr = new NEOPIXEL<18>();
        break;
    case 19:
        ptr = new NEOPIXEL<19>();
        break;
    case 20:
        ptr = new NEOPIXEL<20>();
        break;
    case 21:
        ptr = new NEOPIXEL<21>();
        break;
    case 22:
        ptr = new NEOPIXEL<22>();
        break;
    case 23:
        ptr = new NEOPIXEL<23>();
        break;
    case 24:
        ptr = new NEOPIXEL<24>();
        break;
    case 25:
        ptr = new NEOPIXEL<25>();
        break;
    case 26:
        ptr = new NEOPIXEL<26>();
        break;
    case 27:
        ptr = new NEOPIXEL<27>();
        break;
    case 28:
        ptr = new NEOPIXEL<28>();
        break;
    case 29:
        ptr = new NEOPIXEL<29>();
        break;
    case 30:
        ptr = new NEOPIXEL<30>();
        break;
    case 31:
        ptr = new NEOPIXEL<31>();
        break;
    default:
        ptr = new NEOPIXEL<5>();
        break;
    }
    return ptr;
}

LedStrip::LedStrip(uint8_t dataPin)
{
    controller = CreateController(dataPin);
    FastLED.addLeds(controller, pixels.data(), pixels.size());
}
LedStrip::LedStrip(uint8_t dataPin, int numOfLeds){
    controller = CreateController(dataPin);
    pixels = std::vector<CRGB>(numOfLeds, CRGB::Black);
    FastLED.addLeds(controller, pixels.data(), pixels.size());
}
LedStrip::LedStrip(uint8_t dataPin, std::vector<CRGB> data)
{
    pixels = data;
    controller = CreateController(dataPin);
    FastLED.addLeds(controller, pixels.data(), pixels.size());
}
LedStrip::LedStrip(uint8_t dataPin, CRGB *data, int numOfLeds)
{
    pixels = std::vector<CRGB>(dataPin, numOfLeds);
    controller = CreateController(dataPin);
    FastLED.addLeds(controller, pixels.data(), pixels.size());   
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