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
        listCommands=0,
        explainCommand, 
        //Api functionality
        addStrip,
        removeStrip,
        listStrips,
        changeDefault,
        addPixel,
        removePixel,
        changePixel,
        show
    };

    class LedAPI : public api::API
    {
    public:
        LedLib::Led Leds;
        LedStrip defaultStrip;

        LedAPI();
        api::APIResponse ExecuteCommand(Command command);

        //TODO: Decide how will argument parsing be done (in ExecuteCommand or in command function, or maybe some mixture of both)
        //For now argument parsing will be done inside function

        api::APIResponse listCommands(Command command);    //TODO: add arguments
        api::APIResponse explainCommand(Command command);  //TODO: add arguments

        api::APIResponse addStrip(Command command);        //TODO: add arguments
        api::APIResponse listStrips(Command command);
        api::APIResponse removeStrip(Command command);     //TODO: add arguments
        api::APIResponse changeDefault(Command command);   //TODO: add arguments

        api::APIResponse addPixel(Command command);        //TODO: add arguments
        api::APIResponse removePixel(Command command);     //TODO: add arguments
        api::APIResponse changePixel(Command command);     //TODO: add arguments
        api::APIResponse show(Command command);            //TODO: add arguments
    };
}