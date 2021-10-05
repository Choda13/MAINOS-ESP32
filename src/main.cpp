#include <WiFi.h>
#include <vector>
#include <iostream>
#include <Arduino.h>
#include <WebServer.h>
#include "MAINOS.h"
#include "LedAPI/LedAPI.h"
#include "LedLib/LedStrip.h"
#include "ArduinoJson.h"

WebServer server(80);

const char *SSID = "ZTE_H168N87DF8C";
const char *PASS = "mojnet021";

void post_page();

std::vector<Command> ParseUrlEncoded();
std::vector<Command> ParseJSONEncoded();

uint8_t connectToWifi(const char *ssid, const char *pass);

int char2int(char input);
void hex2bin(const char *src, uint8_t *target);
bool validateHex(const char *data);

void setup()
{
    Serial.begin(115200);
    Serial.println("Begin");
    mainos_init();
    Serial.println(CommandService.APIList.size());
    CommandService.RegisterAPI(new LedAPI::LedAPI());
    Serial.println((CommandService.APIList.at(0)->APIName).c_str());
    Serial.println(CommandService.APIList.size());
    uint8_t status = WL_DISCONNECTED;
    while (status != WL_CONNECTED)
    {
        status = connectToWifi(SSID, PASS);
        delay(5000);
    }

    server.begin();
    server.on("/api", HTTP_POST, post_page);
}

void loop()
{
    server.handleClient();
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
    std::string contentType;
    std::vector<Command> commands;

    contentType = server.header("Content-Type").c_str();
    if(contentType == "application/json")
        commands = commands = ParseJSONEncoded();
    else if(contentType == "application/x-www-form-urlencoded")
        commands = ParseUrlEncoded();
    else
        commands = ParseUrlEncoded();

    auto result = CommandService.HandleCommands(commands);

    std::string response = "";
    for (auto &&i : result)
        response += i.toString();

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
    while (*data)
    {
        if (char2int(data[0]) == -1)
            return false;
        data++;
    }
    return true;
}

std::vector<Command> ParseUrlEncoded()
{
    uint8_t API_ID;
    uint8_t COMM_ID;
    unsigned int arg_size;
    String args;
    std::vector<Command> commands;

    if (!server.hasArg("API_ID") || !server.hasArg("COMM_ID"))
        server.send(400, "text/plain", "Moras poslati bar dva parametra, API_ID i COMM_ID");

    API_ID = server.arg("API_ID").toInt();
    COMM_ID = server.arg("COMM_ID").toInt();
    arg_size = server.arg("ARGS_SIZE").toInt();

    if (arg_size != server.arg("ARGS").length())
    {
        Serial.println("ParseUrlEncoded: Velicina argumenta ne odgovara datoj velicini argumenata.");
        server.send(400, "ParseUrlEncoded: Velicina argumenta ne odgovara datoj velicini argumenata.");
        return commands;
    }

    args = server.arg("ARGS");

    if (args.length() % 2 || !validateHex(args.c_str()))
        server.send(400, "text/plain", "Vrednost parametara mora biti u hex formati majmune glupi");

    //Convert arguments from hex format to its repsective value
    std::vector<uint8_t> bytes(arg_size);
    hex2bin(args.c_str(), bytes.data());

    commands.push_back(Command(API_ID, COMM_ID, bytes));
    return commands;
}
std::vector<Command> ParseJSONEncoded()
{
    StaticJsonDocument<4096> doc;
    std::vector<Command> commands;
    String json = server.arg("plain");

    if (json.length() > 4096)
    {
        server.send(400, "Preveliki JSON, salji JSON dokument koji nije veci od 4096 bajtova");
        return commands;
    }

    auto error = deserializeJson(doc, json);
    // Test if parsing succeeds.
    if (error)
    {
        std::string msg = "deserializeJson() failed: ";
        msg+=error.c_str();
        Serial.println(msg.c_str());
        server.send(500, msg.c_str());
        return commands;
    }

    return commands;

}