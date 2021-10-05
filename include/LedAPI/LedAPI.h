#pragma once
#include "API/API.h"
#include "FastLED.h"
#include "LedLib/LedLib.h"
#include <vector>

namespace LedAPI
{
    
    //exlapinCommand should contain brief description of function, number of arguments its types and possible overloads of the function
    //Command overloading can be done in two ways:
    //  1) diffrent command code for each overload,
    //  2) diffrent number of bytes of arguments every overloaded command recives
    enum CommandCodes
    {
        //Api specific commands
        listCommands = 0,
        explainCommand,
        //Api functionality
        addStrip,
        removeStrip,
        listStrips,
        showStripData,
        changeDefault,
        addPixel,
        removePixel,
        changePixel,
        show,
        showAll
    };

    class LedAPI : public api::API
    {
    public:
        LedLib::Led Leds;
        LedStrip *defaultStrip = NULL;
        uint8_t defaultIndex = 255;

        LedAPI(std::string APIName="LedAPI");
        api::APIResponse ExecuteCommand(Command command);

        //TODO: Argument parser

        api::APIResponse listCommands(Command command);   //TODO: Implement
        api::APIResponse explainCommand(Command command); //TODO: Implement

        api::APIResponse listStrips(Command command);
        api::APIResponse addStrip(Command command); 
        api::APIResponse removeStrip(Command command); 
        api::APIResponse showStripData(Command command);
        api::APIResponse changeDefault(Command command); 

        api::APIResponse addPixel(Command command);    
        api::APIResponse removePixel(Command command); 
        api::APIResponse changePixel(Command command); 
        api::APIResponse show(Command command);        
        api::APIResponse showAll(Command command);
        std::string listStrips();

        int addStrip(uint8_t dataPin ,unsigned int numOfPixels=1, CRGB color=CRGB::Black);

        int removeStrip();
        int removeStrip(uint8_t stripIndex);

        std::string showStripData();
        std::string showStripData(uint8_t stripIndex);

        int changeDefault(uint8_t index);

        int addPixel(unsigned int numOfPixel=1, CRGB color=CRGB::Black);
        int addPixel(uint8_t stripIndex);
        int addPixel(uint8_t stripIndex, unsigned int numOfPixel, CRGB color = CRGB::Black);
        
        int removePixel();
        int removePixel(uint8_t stripIndex);
        int removePixel(unsigned int pixelIndex);
        int removePixel(unsigned int pixelIndex, uint8_t stripIndex);

        int changePixel(CRGB color, int pixelIndex);
        int changePixel(CRGB color, int pixelIndex, uint8_t stripIndex);

        int show();
        int show(CRGB color);
        int show(uint8_t stripIndex);
        int show(uint8_t stripIndex, CRGB color);

        int showAll();
        int showAll(CRGB color);
    };
}