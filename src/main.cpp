#include "../include/LedLib/LedStrip.h"
#include "../include/MAINOS.h"
#include <WebServer.h>
#include <Arduino.h>
#include <iostream>
#include <WiFi.h>

/*Put your SSID & Password*/
const char *ssid = "ZTE_H168N87DF8C"; // Enter SSID here
const char *password = "mojnet021";   //Enter Password here

WebServer server(80);
LedStrip strip(5, 60);

void onPost();
void WebServerInit();

void setup()
{
    Serial.begin(115200);
    strip.show();
    mainos_init();
    WebServerInit();
    std::vector<uint8_t> bytes{0,1,5,0,0,0, 10, 255, 126, 128, 8};
    auto command = CommandService.ParseBytes(bytes)[0];
    Serial.println(command.toString().c_str());
}

void loop()
{
    //server.handleClient();
    delay(10);
}

void onPost(){
    
}

void WebServerInit(){
//     Serial.println("Connecting to ");
//     Serial.println(ssid);

//     //connect to your local wi-fi network
//     WiFi.begin(ssid, password);

//     //check wi-fi is connected to wi-fi network
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(1000);
//         Serial.print(".");
//     }
//     Serial.println("");
//     Serial.println("WiFi connected..!");
//     Serial.print("Got IP: ");
//     Serial.println(WiFi.localIP());

//     server.on("/post", HTTP_POST, onPost);
//     server.begin();
//     Serial.println("HTTP server started");
}