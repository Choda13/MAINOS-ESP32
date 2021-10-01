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
        default: return api::APIResponse(codes::NotFound, command);break;
    }
    return api::APIResponse(codes::NotFound, command);
}

api::APIResponse LedAPI::LedAPI::addStrip(Command command)
{
    //Argument parsing
    //Leds.addStrip(parsedArgs);
}
api::APIResponse LedAPI::LedAPI::listStrips(Command command)
{
    api::APIResponse response(command);
    std::string msg="";
    int count=0;
    for (auto &&i : this->Leds.strips)
    {
        msg+="\nIndex: " + count;
        msg+=i.toString();
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
    std::string msg="";
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

}
api::APIResponse LedAPI::LedAPI::removePixel(Command command)
{

}
api::APIResponse LedAPI::LedAPI::changePixel(Command command)
{

}
api::APIResponse LedAPI::LedAPI::show(Command command)
{
    auto arguments = command.Arguments;
    api::APIResponse response(command);
    
    if(arguments.size() < sizeof(uint8_t))
    {
        response.statusCode = codes::NotEnoughArguments;
        return response;
    }

    uint8_t stripIndex = TypeConversions::bytes_to_type<uint8_t>(arguments);
    if(Leds.strips.size() <= stripIndex)
    {
        response.statusCode = codes::OutOfRange;
        return response;
    }

    Leds.strips.at(stripIndex).show();
    return response;
}