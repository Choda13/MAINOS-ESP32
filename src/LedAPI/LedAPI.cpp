#include "LedAPI/LedAPI.h"
#include <Arduino.h>
#include "TypeConversions/TypeConversions.h"

LedAPI::LedAPI::LedAPI(std::string APIName):API(APIName)
{
    Leds = LedLib::Led();
}
api::APIResponse LedAPI::LedAPI::ExecuteCommand(Command command)
{
    auto response = api::APIResponse(codes::NotFound, command);
    switch (command.CommandID)
    {
    case CommandCodes::listCommands:
        //response = listCommands(command);
        break;
    case CommandCodes::explainCommand:
        // response = explainCommand(command);
        break;
    case CommandCodes::addStrip:
        response = addStrip(command);
        break;
    case CommandCodes::removeStrip:
        response = removeStrip(command);
        break;
    case CommandCodes::listStrips:
        response = listStrips(command);
        break;
    case CommandCodes::changeDefault:
        response = changeDefault(command);
        break;
    case CommandCodes::addPixel:
        response = addPixel(command);
        break;
    case CommandCodes::removePixel:
        response = removePixel(command);
        break;
    case CommandCodes::changePixel:
        response = changePixel(command);
        break;
    case CommandCodes::show:
        response = show(command);
        break;
    case CommandCodes::showAll:
        response = showAll(command);
        break;
    default:
        response.statusCode = codes::NotFound;
        break;
    }
    return response;
}

api::APIResponse LedAPI::LedAPI::addStrip(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch (args.size())
    {
    case sizeof(uint8_t):
        res.statusCode = addStrip(TypeConversions::ExtractType<uint8_t>(args));
        break;
    case sizeof(uint8_t) + sizeof(int):
        res.statusCode = addStrip(TypeConversions::ExtractType<uint8_t>(args), TypeConversions::ExtractType<int>(args));
        break;
    case sizeof(uint8_t) + sizeof(CRGB):
        break;
        res.statusCode = addStrip(TypeConversions::ExtractType<uint8_t>(args), TypeConversions::ExtractType<CRGB>(args));
        break;
    case sizeof(uint8_t) + sizeof(int) + sizeof(CRGB):
        res.statusCode = addStrip(TypeConversions::ExtractType<uint8_t>(args), TypeConversions::ExtractType<int>(args), TypeConversions::ExtractType<CRGB>(args));
        Serial.println(res.statusCode);
        break;
    }
    return res;
}
api::APIResponse LedAPI::LedAPI::listStrips(Command command)
{
    auto res = api::APIResponse(codes::Success, command);
    auto msg = listStrips();
    res.responseData = std::vector<uint8_t>(msg.begin(), msg.end());
    return res;
}
api::APIResponse LedAPI::LedAPI::removeStrip(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch (args.size())
    {
    case sizeof(uint8_t):
        res.statusCode = removeStrip(TypeConversions::ExtractType<uint8_t>(args));
        break;
    default:
        res.statusCode = removeStrip();
    }
    return res;
}
api::APIResponse LedAPI::LedAPI::showStripData(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    std::string value;
    switch (args.size())
    {
    case sizeof(uint8_t):
        value = showStripData(TypeConversions::ExtractType<uint8_t>(args));
        res.responseData = std::vector<uint8_t>(value.begin(), value.end());
        break;
    default:
        value = showStripData();
        res.responseData = std::vector<uint8_t>(value.begin(), value.end());
        break;
    }
    return res;
}

api::APIResponse LedAPI::LedAPI::changeDefault(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch (args.size())
    {
    case sizeof(uint8_t):
        res.statusCode = changeDefault(TypeConversions::ExtractType<uint8_t>(args));
        break;
    default:
        break;
    }
    return res;
}

api::APIResponse LedAPI::LedAPI::addPixel(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch (args.size())
    {
    case 0:
        res.statusCode = addPixel();
        break;
    case sizeof(uint8_t):
        res.statusCode = addPixel(TypeConversions::ExtractType<uint8_t>(args));
        break;
    case sizeof(unsigned int):
        res.statusCode = addPixel(TypeConversions::ExtractType<unsigned int>(args));
        break;
    case sizeof(uint8_t) + sizeof(unsigned int):
        res.statusCode = addPixel(TypeConversions::ExtractType<uint8_t>(args),
                                TypeConversions::ExtractType<unsigned int>(args));
        break;
    case sizeof(unsigned int) + sizeof(CRGB):
        res.statusCode = addPixel(TypeConversions::ExtractType<unsigned int>(args),
                                TypeConversions::ExtractType<CRGB>(args));
        break;
    case sizeof(uint8_t) + sizeof(unsigned int) + sizeof(CRGB):
        res.statusCode = addPixel(TypeConversions::ExtractType<uint8_t>(args),
                                TypeConversions::ExtractType<unsigned int>(args),
                                TypeConversions::ExtractType<CRGB>(args));
        break;
    }
    return res;
}
api::APIResponse LedAPI::LedAPI::removePixel(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch (args.size())
    {
        case 0:
            res.statusCode = removePixel();
            break;
        case sizeof(uint8_t):
            res.statusCode = removePixel(TypeConversions::ExtractType<uint8_t>(args));
            break;
        case sizeof(unsigned int):
            res.statusCode = removePixel(TypeConversions::ExtractType<unsigned int>(args));
            break;
        case sizeof(unsigned int) + sizeof(uint8_t):
            res.statusCode = removePixel(TypeConversions::ExtractType<unsigned int>(args),
                                        TypeConversions::ExtractType<uint8_t>(args));
            break;
    }
    return res;
}
api::APIResponse LedAPI::LedAPI::changePixel(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch (args.size())
    {
        case sizeof(CRGB) + sizeof(int):
            res.statusCode = changePixel(TypeConversions::ExtractType<CRGB>(args),
                                        TypeConversions::ExtractType<int>(args));
            break;
        case sizeof(CRGB) + sizeof(int) + sizeof(uint8_t):
        res.statusCode = changePixel(TypeConversions::ExtractType<CRGB>(args),
                                    TypeConversions::ExtractType<int>(args),
                                    TypeConversions::ExtractType<uint8_t>(args));
            break;
    }
    return res;
}
api::APIResponse LedAPI::LedAPI::show(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args = command.Arguments;
    switch(args.size())
    {
        case 0:
            res.statusCode = show();
            break;
        case sizeof(CRGB):
            res.statusCode = show(TypeConversions::ExtractType<CRGB>(args));
            break;
        case sizeof(uint8_t):
            res.statusCode = show(TypeConversions::ExtractType<uint8_t>(args));
            break;
        case sizeof(uint8_t) + sizeof(CRGB):
            res.statusCode = show(TypeConversions::ExtractType<uint8_t>(args),
                                  TypeConversions::ExtractType<CRGB>(args));
            break;
    }
    return res;
}
api::APIResponse LedAPI::LedAPI::showAll(Command command)
{
    auto res = api::APIResponse(codes::NonMatchungArguments, command);
    auto args=command.Arguments;
    switch (args.size())
    {
        case 0:
            res.statusCode = showAll();
            break;
        case sizeof(CRGB):
            res.statusCode = showAll(TypeConversions::ExtractType<CRGB>(args));
            break;
    }
    return res;
}

std::string LedAPI::LedAPI::listStrips()
{
    std::string result = "Total number of strips: " + Leds.size();
    uint8_t count = 0;

    result += "\nStrips: \n";
    for (auto &&i : Leds.strips)
    {
        result += "\nStrip at index: " + count;
        result += i.toString();
        count++;
    }
    return result;
}

int LedAPI::LedAPI::addStrip(uint8_t dataPin, unsigned int numOfPixels, CRGB color)
{
    if (Leds.size() >= std::numeric_limits<uint8_t>::max() - 1)
        return codes::LimitReached;
    Leds.addStrip(dataPin, numOfPixels, color);
    return codes::Success;
}

int LedAPI::LedAPI::removeStrip()
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    Leds.strips.erase(Leds.strips.begin() + defaultIndex);
    defaultStrip = NULL;
    defaultIndex = 255;
    return codes::Success;
}
int LedAPI::LedAPI::removeStrip(uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex || stripIndex == 255)
        return codes::NotFound;
    if (stripIndex == defaultIndex)
        return removeStrip();
    Leds.strips.erase(Leds.strips.begin() + stripIndex);
    return codes::Success;
}

std::string LedAPI::LedAPI::showStripData()
{
    if (defaultStrip == NULL)
        return std::string();
    return defaultStrip->toString();
}
std::string LedAPI::LedAPI::showStripData(uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex)
        return std::string();
    return Leds.at(stripIndex).toString();
}

int LedAPI::LedAPI::changeDefault(uint8_t index)
{
    if (Leds.size() <= index || index == 255)
        return codes::NotFound;
    defaultStrip = &Leds.at(index);
    defaultIndex = index;
    return codes::Success;
}

int LedAPI::LedAPI::addPixel(unsigned int numOfPixel, CRGB color)
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    for (int i = 0; i < numOfPixel; i++)
        defaultStrip->addPixel(color);
    return codes::Success;
}
int LedAPI::LedAPI::addPixel(uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    Leds.at(stripIndex).addPixel();
    return codes::Success;
}
int LedAPI::LedAPI::addPixel(uint8_t stripIndex, unsigned int numOfPixel, CRGB color)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    for (int i = 0; i < numOfPixel; i++)
        Leds.at(stripIndex).addPixel(color);
    return codes::Success;
}

int LedAPI::LedAPI::removePixel()
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    defaultStrip->removePixel();
    return codes::Success;
}
int LedAPI::LedAPI::removePixel(uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    Leds.at(stripIndex).removePixel();
    return codes::Success;
}
int LedAPI::LedAPI::removePixel(unsigned int pixelIndex)
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    if (defaultStrip->size() <= pixelIndex)
        return codes::OutOfRange;
    defaultStrip->removePixel(pixelIndex);

    return codes::Success;
}
int LedAPI::LedAPI::removePixel(unsigned int pixelIndex, uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    if (Leds.at(stripIndex).size() <= pixelIndex)
        return codes::OutOfRange;
    Leds.at(stripIndex).removePixel(pixelIndex);
    return codes::Success;
}

int LedAPI::LedAPI::changePixel(CRGB color, int pixelIndex)
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    if (defaultStrip->size() <= pixelIndex)
        return codes::OutOfRange;
    defaultStrip->at(pixelIndex) = color;

    return codes::Success;
}
int LedAPI::LedAPI::changePixel(CRGB color, int pixelIndex, uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    if (Leds.at(stripIndex).size() <= pixelIndex)
        return codes::OutOfRange;
    Leds.at(stripIndex).at(pixelIndex) = color;
    return codes::Success;
}

int LedAPI::LedAPI::show()
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    defaultStrip->show();
    return codes::Success;
}
int LedAPI::LedAPI::show(CRGB color)
{
    if (defaultStrip == NULL)
        return codes::NotDefined;
    defaultStrip->show(color);
    return codes::Success;
}
int LedAPI::LedAPI::show(uint8_t stripIndex)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    Leds.at(stripIndex).show();
    return codes::Success;
}
int LedAPI::LedAPI::show(uint8_t stripIndex, CRGB color)
{
    if (Leds.size() <= stripIndex)
        return codes::NotFound;
    Leds.at(stripIndex).show(color);
    return codes::Success;
}

int LedAPI::LedAPI::showAll()
{
    for (int i = 0; i < Leds.size(); i++)
        show(i);
    return codes::Success;
}
int LedAPI::LedAPI::showAll(CRGB color)
{
    for (int i = 0; i < Leds.size(); i++)
        show(i, color);
    return codes::Success;
}
