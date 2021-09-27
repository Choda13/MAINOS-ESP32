#include "../../include/API/API.h"

api::API::API(){
}

api::API::API(std::string APIName) {
	this->APIName = APIName;
}

api::APIResponse api::API::ExecuteCommand(Command command)
{
	std::string msg = "Not implementend";
	std::vector<uint8_t> response(msg.begin(), msg.end());
	return APIResponse(command, std::vector<uint8_t>(), response);
}

api::APIResponse::APIResponse(Command command) : command(command) {
	this->statusCode = codes::Success;
}

api::APIResponse::APIResponse(Command command, std::vector<uint8_t>systemData) : command(command) {
	this->systemData = systemData;
}

api::APIResponse::APIResponse(Command command, std::vector<uint8_t>systemData, std::vector<uint8_t>responseData) : command(command) {
	this->systemData = systemData;
	this->responseData = responseData;
}

api::APIResponse::APIResponse(int statusCode, Command command) : command(command){
	this->statusCode = statusCode;
}

api::APIResponse::APIResponse(int statusCode, Command command, std::vector<uint8_t>systemData) : command(command){
	this->statusCode = statusCode;
	this->systemData = systemData;
}

api::APIResponse::APIResponse(int statusCode, Command command, std::vector<uint8_t>systemData, std::vector<uint8_t>responseData) : command(command){
	this->statusCode = statusCode;
	this->systemData = systemData;
	this->responseData = responseData;
}