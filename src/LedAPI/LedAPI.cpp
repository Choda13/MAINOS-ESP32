#include "LedAPI/LedAPI.h"

LedAPI::LedAPI::LedAPI()
{
    Leds = LedLib::Led();
}

api::APIResponse LedAPI::LedAPI::ExecuteCommand(Command command)
{
    api::APIResponse response(codes::NotFound, command);
    switch (command.CommandID)
    {
    case CommandCodes::listCommands:
        break;
    case CommandCodes::explainCommand:
        break;
    case CommandCodes::addStrip:
        break;
    case CommandCodes::removeStrip:
        break;
    case CommandCodes::listStrips:
        break;
    case CommandCodes::changeDefault:
        break;
    case CommandCodes::addPixel:
    response = LedAPI::addPixel(command);
        break;
    case CommandCodes::removePixel:
        response = LedAPI::removePixel(command);
        break;
    case CommandCodes::changePixel:
        response = LedAPI::changePixel(command);
        break;
    case CommandCodes::show:
        response = LedAPI::show(command);
        break;
    default:
        return api::APIResponse(codes::NotFound, command);
        break;
    }
    return response;
}

api::APIResponse LedAPI::LedAPI::addStrip(Command command)
{
    //Argument parsing
    //Leds.addStrip(parsedArgs);
}
api::APIResponse LedAPI::LedAPI::listStrips(Command command)
{
    api::APIResponse response(command);
    std::string msg = "";
    int count = 0;
    for (auto &&i : this->Leds.strips)
    {
        msg += "\nIndex: " + count;
        msg += i.toString();
        count++;
    }
    response.responseData = std::vector<uint8_t>(msg.begin(), msg.end());
    return response;
}
api::APIResponse LedAPI::LedAPI::removeStrip(Command command)
{
}
api::APIResponse LedAPI::LedAPI::showStripData(Command command)
{
    std::string msg = "";
    api::APIResponse response(command);
    response.statusCode = codes::NotFound;
    //Parse arguments
    //Check if args are valid
    //Retreive strip data
    //return response
    return response;
}

api::APIResponse LedAPI::LedAPI::changeDefault(Command command)
{
}

api::APIResponse LedAPI::LedAPI::addPixel(Command command)
{
    auto arguments = command.Arguments;
    api::APIResponse response(command);

    uint8_t stripIndex;

    int argSize = sizeof(stripIndex);
    if(arguments.size() < argSize)
    {
        response.statusCode = codes::NotEnoughArguments;
        return response;
    }
    stripIndex = TypeConversions::bytes_to_type<uint8_t>(arguments);
    arguments = std::vector<uint8_t>(arguments.begin()+sizeof(stripIndex), arguments.end());

    if(Leds.strips.size() <= stripIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }
    Leds.strips.at(stripIndex).addPixel();
    return response;
}
api::APIResponse LedAPI::LedAPI::removePixel(Command command)
{
    auto arguments = command.Arguments;
    api::APIResponse response(command);

    uint8_t stripIndex;
    unsigned int pixelIndex;

    int argSize = sizeof(stripIndex) + sizeof(pixelIndex);

    if(arguments.size() < argSize)
    {
        response.statusCode = codes::NotEnoughArguments;
        return response;
    }
    stripIndex = TypeConversions::bytes_to_type<uint8_t>(arguments);
    arguments = std::vector<uint8_t>(arguments.begin()+sizeof(stripIndex), arguments.end());

    pixelIndex = TypeConversions::bytes_to_type<unsigned int>(arguments);
    arguments = std::vector<uint8_t>(arguments.begin()+sizeof(stripIndex), arguments.end());

    if(Leds.strips.size() <= stripIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }
    if(Leds.strips.at(stripIndex).size() <= pixelIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }
    Leds.strips.at(stripIndex).removePixel(pixelIndex);
    return response;
}
api::APIResponse LedAPI::LedAPI::changePixel(Command command)
{
    auto arguments = command.Arguments;
    api::APIResponse response(command);

    uint8_t stripIndex;
    unsigned int pixelIndex;
    CRGB color;

    int argSize = sizeof(stripIndex) + sizeof(pixelIndex) + sizeof(CRGB);

    if(arguments.size() < argSize)
    {
        response.statusCode = codes::NotEnoughArguments;
        return response;
    }
    stripIndex = TypeConversions::bytes_to_type<uint8_t>(arguments);
    arguments = std::vector<uint8_t>(arguments.begin()+sizeof(stripIndex), arguments.end());

    pixelIndex = TypeConversions::bytes_to_type<unsigned int>(arguments);
    arguments = std::vector<uint8_t>(arguments.begin()+sizeof(stripIndex), arguments.end());

    color = TypeConversions::bytes_to_type<CRGB>(arguments);
    arguments = std::vector<uint8_t>(arguments.begin()+sizeof(stripIndex), arguments.end());

    if(Leds.strips.size() <= stripIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }
    if(Leds.strips.at(stripIndex).size() <= pixelIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }
    Leds.strips.at(stripIndex).pixels.at(pixelIndex) = color;
    return response;
}
api::APIResponse LedAPI::LedAPI::show(Command command)
{
    auto arguments = command.Arguments;
    api::APIResponse response(command);

    //check if strip index is specified, if not, prefrom show method on default strip if possible
    if (arguments.size() < sizeof(uint8_t))
    {
        if (defaultStrip == NULL)
            defaultStrip->show();
        else
            response.statusCode = codes::NotEnoughArguments;
        return response;
    }

    uint8_t stripIndex = TypeConversions::bytes_to_type<uint8_t>(arguments);
    if (Leds.strips.size() <= stripIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }

    Leds.strips.at(stripIndex).show();
    return response;
}