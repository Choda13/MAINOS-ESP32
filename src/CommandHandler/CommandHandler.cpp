#include "../../include/CommandHandler/CommandHandler.h"

commserv::CommandHandler::CommandHandler() {
	this->APIList = std::vector<api::API>();
}

commserv::CommandHandler::CommandHandler(std::vector<api::API>APIList) {
	this->APIList = APIList;
}

std::vector<Command> commserv::CommandHandler::ParseBytes(std::vector<uint8_t>data) {
	int argsSize;
	uint8_t ApiID;
	uint8_t CommandID;
	std::vector<uint8_t> Arguments;

	std::vector<Command> result;
	int dataSize = data.size();
	int i = 0;
	while (i != dataSize) {
		Command com = Command::Decode(data);
		if (!com.isCommandValid) {
			//REPLACE: SerialPrint;
			//std::cout << e1.what() << std::endl;
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
	for (it; it != commands.end(); it++) {
		uint8_t id = it->ApiID;
		if (id >= APIList.size()) {
			std::string msg = "API not found";
			std::vector<uint8_t> response(msg.begin(), msg.end());
			ResponseList.push_back(api::APIResponse(codes::NotFound, *it, std::vector<uint8_t>(), response));
		}
		else
			ResponseList.push_back(APIList.at(id).ExecuteCommand(*it));
	}
	return ResponseList;
}

int commserv::CommandHandler::RegisterAPI(api::API api) {
	for (auto it = APIList.begin(); it != APIList.end(); it++)
		if (it->APIName == api.APIName)
			return codes::StatusCodes::AlreadyExist;
	APIList.push_back(api);
	return codes::StatusCodes::Success;
}

int commserv::CommandHandler::UnregisterAPI(api::API api) {
	for (auto it = APIList.begin(); it != APIList.end(); it++)
		if (it->APIName == api.APIName) {
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

//OLD
//std::vector<Command> commserv::CommandHandler::ParseBytes(std::vector<uint8_t>data) {
//	int argsSize;
//	uint8_t ApiID;
//	uint8_t CommandID;
//	std::vector<uint8_t> Arguments;
//
//	std::vector<Command> result;
//	uint8_t* dataPtr = data.data();
//	int dataSize = data.size();
//	int i = 0;
//
//	//ApiID, CommandID, and argsSize are actually headers
//	while (i < dataSize) {
//		if (i + Command::HEADER_SIZE >= dataSize) {
//			std::cout << "Nedovoljno podataka za sledecu komandu" << std::endl;
//			break;
//		}
//		i += Command::HEADER_SIZE;
//		//Extract ApiID
//		std::copy(dataPtr, dataPtr + Command::API_ID_SIZE, reinterpret_cast<uint8_t*>(&ApiID));
//		dataPtr += Command::API_ID_SIZE;
//
//		//Extract CommandID
//		std::copy(dataPtr, dataPtr + Command::COMMAND_ID_SIZE, reinterpret_cast<uint8_t*>(&CommandID));
//		dataPtr += Command::COMMAND_ID_SIZE;
//
//		//Extract argsSize
//		std::copy(dataPtr, dataPtr + Command::ARGS_SIZE, reinterpret_cast<uint8_t*>(&argsSize));
//		dataPtr += Command::ARGS_SIZE;
//
//		if (i + argsSize > dataSize) {
//			std::cout << "Nedovoljno podataka za argumente ove komande" << std::endl;
//			break;
//		}
//		i += argsSize;
//		//Extract Arguments
//		Arguments = std::vector<uint8_t>(argsSize);
//		std::copy(dataPtr, dataPtr + argsSize, reinterpret_cast<uint8_t*>(Arguments.data()));
//		dataPtr += argsSize;
//
//		result.push_back(Command{ ApiID, CommandID, Arguments });
//		Arguments.clear();
//	}
//	return result;
//}