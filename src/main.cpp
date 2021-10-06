#include <WiFi.h>
#include <vector>
#include <iostream>
#include <Arduino.h>
#include <WebServer.h>
#include "MAINOS.h"
#include "LedAPI/LedAPI.h"
#include "LedLib/LedStrip.h"
#include "ArduinoJson.h"

using namespace TypeConversions;

WebServer server(80);

const char *SSID = "ZTE_H168N87DF8C";
const char *PASS = "mojnet021";

void post_page();

std::vector<Command> ParseUrlEncoded();
std::vector<Command> ParseJSONEncoded();
uint8_t connectToWifi(const char *ssid, const char *pass);
void webserver_init();

//Entry point
void setup()
{
    Serial.begin(115200);
    Serial.print(__PRETTY_FUNCTION__);
    Serial.print(": ");
    Serial.println("Begin");

    mainos_init();
    webserver_init();
    CommandService.RegisterAPI(new LedAPI::LedAPI());

    uint8_t status = WL_DISCONNECTED;
    while (status != WL_CONNECTED)
    {
        status = connectToWifi(SSID, PASS);
        delay(5000);
    }
}
void loop()
{
    server.handleClient();
}

void webserver_init()
{
    server.begin();
    server.on("/api", HTTP_POST, post_page);
    server.on("/api", HTTP_GET, post_page);
    const char *headerkeys[] = {"User-Agent", "Cookie", "Content-Type"};
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
    //ask server to track these headers
    server.collectHeaders(headerkeys, headerkeyssize);
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
    Serial.print("Num of headers: ");
    Serial.println(server.headers());
    Serial.println(server.hostHeader());

    for (int i = 0; i < server.headers(); i++)
        Serial.println(server.header(i).c_str());

    if (contentType == "application/json")
        commands = commands = ParseJSONEncoded();
    else if (contentType == "application/x-www-form-urlencoded")
        commands = ParseUrlEncoded();
    else
        commands = ParseUrlEncoded();

    auto result = CommandService.HandleCommands(commands);
    Serial.print("Number of commands: ");
    Serial.println(commands.size());

    Serial.print("Number of responses: ");
    Serial.println(result.size());

    std::string response = "";
    for (auto &&i : result)
        response += i.toString();

    server.send(200, "text/plain", response.c_str());
    Serial.println(response.c_str());
}

std::vector<Command> ParseUrlEncoded()
{
    uint8_t API_ID;
    uint8_t COMM_ID;
    unsigned int arg_size;
    String args;
    std::vector<Command> commands;

    Serial.println("Parsing url encoded data");

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
    DynamicJsonDocument doc(4096);
    std::vector<Command> commands;
    String json = server.arg("plain");
    std::string msg;

    std::vector<std::string> objectKeys = {"api", "command"};

    Serial.println("Parsing JSON data");

    if (json.length() > 4096)
    {
        Serial.println("JSON je malo velik ;)");
        return commands;
    }

    auto error = deserializeJson(doc, json);
    // Test if parsing succeeds.
    if (error)
    {
        msg = "deserializeJson() failed: ";
        msg += error.c_str();
        Serial.println(msg.c_str());
        return commands;
    }

    if (doc.is<JsonArray>())
    {
        msg = "JSON document contains list of commands";
        Serial.println(msg.c_str());
        JsonObject jsonObject;

        for (int i = 0; i < doc.size(); i++)
        {
            jsonObject = doc[i];
            if (!validateObject(jsonObject, objectKeys))
            {
                msg = "Objekat u json fajlu nije validan\n";
                Serial.println(msg.c_str());
                continue;
            }

            auto command = jsonObject2Command(jsonObject);
            commands.push_back(command);
        }
    }
    else
    {
        msg = "JSOC document contains only object";
        Serial.println(msg.c_str());

        auto jsonObject = doc.as<JsonObject>();

        if (!validateObject(jsonObject, objectKeys))
        {
            msg = "Objekat u json fajlu nije validan\n";
            Serial.println(msg.c_str());
        }
        commands.push_back(jsonObject2Command(jsonObject));
    }
    return commands;
}