#include <Arduino.h>
#include <iostream>
#include "MAINOS.h"
#include "LedAPI/LedAPI.h"
#include "LedLib/LedStrip.h"

LedAPI::LedAPI ledApi = LedAPI::LedAPI();

void setup()
{
    Serial.begin(115200);
    mainos_init();
    CommandService.RegisterAPI(ledApi);
}

void loop()
{
    auto msg = ledApi.listStrips();
    std::vector<uint8_t> bytes={1,0,0,0,0,0};
    auto res = CommandService.HandleCommands(bytes);
    std::string logg = "Status code: " + TypeConversions::int_to_string(res[0].statusCode);
    Serial.println(logg.c_str());
    delay(10000);
}
