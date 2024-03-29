#include "CommandHandler/CommandHandler.h"
#include <Arduino.h>

commserv::CommandHandler::CommandHandler() {
	this->APIList = std::vector<api::API*>();
}

commserv::CommandHandler::CommandHandler(std::vector<api::API*>APIList) {
	this->APIList = APIList;
}

std::vector<Command> commserv::CommandHandler::ParseBytes(std::vector<uint8_t>data) {
	std::vector<Command> result;
	int dataSize = data.size();
	int i = 0;
	while (i != dataSize) {
		Command com = Command::Decode(data);
		if (!com.isCommandValid) {
			Serial.println("Command is not valid");
			return result;
		}
		result.push_back(com);
		i += com.size();
		if (i >= dataSize)
			break;
		data = std::vector<uint8_t>(data.begin() + com.size(), data.end());
	}
	return result;
}

std::vector<api::APIResponse> commserv::CommandHandler::HandleCommands(std::vector<uint8_t>data) {
	std::vector<Command> commands = CommandHandler::ParseBytes(data);
	return this->HandleCommands(commands);
}

std::vector<api::APIResponse> commserv::CommandHandler::HandleCommands(std::vector<Command> commands) {
	ResponseList.clear();
	std::vector<Command>::iterator it = commands.begin();
	for (; it != commands.end(); it++) {
		uint8_t id = it->ApiID;
		if (id >= APIList.size()) {
			std::string msg = "API not found";
			std::vector<uint8_t> response(msg.begin(), msg.end());
			ResponseList.push_back(api::APIResponse(codes::NotFound, *it, std::vector<uint8_t>(), response));
		}
		else
			ResponseList.push_back(APIList.at(id)->ExecuteCommand(*it));
	}
	return ResponseList;
}

int commserv::CommandHandler::RegisterAPI(api::API* api) {
	for (auto it = APIList.begin(); it != APIList.end(); it++)
		if ((*it)->APIName == api->APIName){
			Serial.println((*it)->APIName.c_str());
			Serial.println(api->APIName.c_str());
			return codes::StatusCodes::AlreadyExist;
		}
	Serial.println("Success");
	APIList.push_back(api);
	return codes::StatusCodes::Success;
}

int commserv::CommandHandler::UnregisterAPI(api::API* api) {
	for (auto it = APIList.begin(); it != APIList.end(); it++)
		if ((*it)->APIName == api->APIName) {
			APIList.erase(it);
			return codes::StatusCodes::Success;
		}
	return codes::StatusCodes::NotFound;
}

int commserv::CommandHandler::UnregisterAPI(unsigned int index) {
	if (APIList.size() <= index)
		return codes::StatusCodes::OutOfRange;
	APIList.erase(APIList.begin() + index);
	return codes::StatusCodes::Success;
}