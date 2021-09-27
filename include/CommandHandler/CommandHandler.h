#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include "Command.h"
#include "../API/API.h"
#include "../StatusCodes.h"

namespace commserv {
	class CommandHandler {
	public:
		std::vector<api::API> APIList;
		std::vector<api::APIResponse>ResponseList;

		CommandHandler();
		CommandHandler(std::vector<api::API> APIList);

		std::vector<api::APIResponse> HandleCommands(std::vector<uint8_t> data);
		std::vector<api::APIResponse> HandleCommands(std::vector<Command> commands);
		int RegisterAPI(api::API api);
		int UnregisterAPI(api::API api);
		int UnregisterAPI(unsigned int apiIndex);
		static std::vector<Command> ParseBytes(std::vector<uint8_t> data);
	};
}