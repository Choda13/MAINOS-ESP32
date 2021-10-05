#include <Arduino.h>
#include <iostream>
#include <WiFi.h>
#include <WebServer.h>
#include "MAINOS.h"
#include "LedAPI/LedAPI.h"
#include "LedLib/LedStrip.h"

WebServer server(80);

LedAPI::LedAPI ledApi = LedAPI::LedAPI();
LedStrip *strip;
const char *SSID = "ZTE_H168N87DF8C";
const char *PASS = "mojnet021";

void post_page();
uint8_t connectToWifi(const char *ssid, const char *pass);

int char2int(char input);
void hex2bin(const char *src, uint8_t *target);
bool validateHex(const char *data);

void setup()
{
    // Serial.begin(115200);

    // mainos_init();
    // Serial.println(CommandService.APIList.size());
    // CommandService.RegisterAPI(new LedAPI::LedAPI());
    // Serial.println((CommandService.APIList.at(0)->APIName).c_str());
    // Serial.println(CommandService.APIList.size());
    // uint8_t status = WL_DISCONNECTED;
    // while (status != WL_CONNECTED)
    // {
    //     status = connectToWifi(SSID, PASS);
    //     delay(5000);
    // }

    // server.begin();
    // server.on("/api", HTTP_POST, post_page);
    ledApi.addStrip(5, 30, CRGB::DarkGreen);
    strip=&ledApi.Leds.strips.at(0);
    delay(150);
}

void loop()
{
    // server.handleClient();
    // delay(1);
    
    strip->show(CRGB::CadetBlue);
    delay(150);
    strip->show(CRGB::Black);
    delay(150);
}

uint8_t connectToWifi(const char *ssid, const char *pass)
{
    Serial.print("\nAttempting to connect to: ");
    Serial.println(ssid);
    auto status = WiFi.begin(ssid, pass);
    if (status != WL_CONNECTED)
    {
        Serial.print("Can't connect to ");
        Serial.println(ssid);
        return status;
    }
    Serial.print("\nSuccessfully connected to ");
    Serial.println(ssid);
    return status;
}

void post_page()
{
    if(!server.hasArg("API_ID") ||
       !server.hasArg("COMM_ID") ||
       !server.hasArg("ARGS_SIZE") ||
       !server.hasArg("args")){
        server.send(400, "text/plain", "Moras poslati sve parametre idiote");
        return;
       }
    String hexData="";
    hexData+=server.arg("API_ID");
    hexData+=server.arg("COMM_ID");
    hexData+=server.arg("ARGS_SIZE");
    hexData+=server.arg("args");

    if(hexData.length() % 2 || !validateHex(hexData.c_str()))
        server.send(400, "text/plain", "Vrednost parametara mora biti u hex formati majmune glupi");

    std::vector<uint8_t> bytes(hexData.length()/2);
    hex2bin(hexData.c_str(), bytes.data());

    auto result = CommandService.HandleCommands(bytes);

    std::string response="";
    for(auto &&i : result)
        response+= i.toString();
    
    server.send(200, "text/plain", response.c_str());
}

int char2int(char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    return -1;
}

void hex2bin(const char *src, uint8_t *target)
{
    while (*src && src[1])
    {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
    }
}

bool validateHex(const char *data)
{
    while(*data){
        if(char2int(data[0]) == -1)
            return false;
        data++;
    }
    return true;
}