#pragma once
#include "API/API.h"
#include "FastLED.h"
#include "LedLib/LedLib.h"
#include <vector>

class LedAPI : public api::API{
public:
    LedLib::Led Leds;
    LedStrip defaultStrip;

    LedAPI();
    api::APIResponse ExecuteCommand(Command command);
};