#pragma once
#include <string>
#include <iostream>
#include "../CommandHandler/Command.h"
#include "../StatusCodes.h"

namespace api {

	class APIResponse;
	class API;

	//TODO: Expand API base class
	//Abstract class
	class API {
	public:
		//static virtual enum CommandCode {};
		std::string APIName;

		API();
		API(std::string APIName);
		virtual APIResponse ExecuteCommand(Command command);
	};

	//Expand APIResponse class to include uint8_t api_code and uint8_t command_code
	class APIResponse {
	public:
		int statusCode;
		std::vector<uint8_t>systemData; //system specifi return data
		std::vector<uint8_t>responseData; //data to be returned to client aka caller
		Command command;

		APIResponse(Command command);
		APIResponse(Command command, std::vector<uint8_t>systemData);
		APIResponse(Command command, std::vector<uint8_t>systemData, std::vector<uint8_t>responseData);
		APIResponse(int statusCode, Command command);
		APIResponse(int statusCode, Command command, std::vector<uint8_t>systemData);
		APIResponse(int statusCode, Command command, std::vector<uint8_t>systemData, std::vector<uint8_t>responseData);

		std::string toString();
	};
}