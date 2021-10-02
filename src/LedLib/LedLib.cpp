#include "../include/LedLib/LedLib.h"

LedLib::Led::Led()
{
}
LedLib::Led::Led(uint8_t dataPin)
{
    strips.push_back(LedStrip(dataPin));
}
LedLib::Led::Led(LedStrip strip)
{
    strips.push_back(strip);
}
LedLib::Led::Led(std::vector<LedStrip> strips)
{
    this->strips.insert(this->strips.end(), strips.begin(), strips.end());
}
LedLib::Led::Led(LedStrip* strips, unsigned int numOfStrips)
{
    for(auto i=0; i< numOfStrips; i++)
        this->strips.push_back(strips[i]);
}

LedStrip& LedLib::Led::at(unsigned int index)
{
    return strips.at(index);
}
unsigned int LedLib::Led::size()
{
    return strips.size();
}

void LedLib::Led::addStrip(uint8_t dataPin)
{
    strips.push_back(LedStrip(dataPin));
}
void LedLib::Led::addStrip(uint8_t dataPin, std::vector<CRGB> leds)
{
    strips.push_back(LedStrip(dataPin, leds));
}
void LedLib::Led::addStrip(uint8_t dataPin, CRGB *leds, unsigned int numOfLeds)
{
    strips.push_back(LedStrip(dataPin, leds, numOfLeds));
}
void LedLib::Led::addStrip(uint8_t dataPin, unsigned int numOfLeds, CRGB color)
{
    strips.push_back(LedStrip(dataPin, std::vector<CRGB>(color, numOfLeds)));
}

void LedLib::Led::removeStrip()
{
    if (strips.size() == 0)
        return;
    strips.pop_back();
}
void LedLib::Led::removeStrip(unsigned int index)
{
    if (strips.size() <= index)
        return;
    strips.erase(strips.begin() + index);
}

void LedLib::Led::show()
{
    for (auto &&i : strips)
        i.show();
}
void LedLib::Led::show(CRGB color)
{
    for(auto &&i : strips)
        i.show(color);
}
void LedLib::Led::show(unsigned int index)
{
    if(strips.size() <= index)return;
    strips.at(index).show();
}
void LedLib::Led::show(unsigned int index, CRGB color)
{
    if(strips.size() <= index)return;
    strips.at(index).show(color);
}

CLEDController *LedLib::CreateController(uint8_t dataPin)
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