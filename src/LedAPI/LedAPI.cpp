#include "LedAPI/LedAPI.h"

LedAPI::LedAPI::LedAPI()
{
    Leds = LedLib::Led();
}

api::APIResponse LedAPI::LedAPI::ExecuteCommand(Command command)
{
    switch (command.CommandID)
    {
        case CommandCodes::listCommands:break;
        case CommandCodes::explainCommand:break;
        case CommandCodes::addStrip:break;
        case CommandCodes::removeStrip:break;
        case CommandCodes::listStrips:break;
        case CommandCodes::changeDefault:break;
        case CommandCodes::addPixel:break;
        case CommandCodes::removePixel:break;
        case CommandCodes::changePixel:break;
        case CommandCodes::show:break;
        default: return api::APIResponse(codes::NotFound, command);
    }
}